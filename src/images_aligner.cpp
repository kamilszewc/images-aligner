#include "../include/images_aligner.h"
#include "../include/feature_matcher.h"
#include "../include/feature_descriptor.h"
#include "../include/image.h"
#include "../include/images_aligner_exception.h"
#include <iostream>

ImagesAligner::ImagesAligner() {
    featureDescriptor_ = new AkazeFeatureDescriptor();
    featureMatcher_ = new FlannFeatureMatcher();
    isInClassInitialized_ = true;
}

ImagesAligner::ImagesAligner(FeatureDescriptor& featureDescriptor, FeatureMatcher& featureMatcher)
    : featureDescriptor_(&featureDescriptor), featureMatcher_(&featureMatcher)
{
}

ImagesAligner::~ImagesAligner() {
    if (isInClassInitialized_) {
        delete featureDescriptor_;
        delete featureMatcher_;
    }
}

ImagesCollection ImagesAligner::align(const vector<filesystem::path> &filePaths, int blurSize) const {

    if (blurSize > 0 && blurSize % 2 != 1) {
        throw ImagesAlignerException("Parameter blurSize must be an odd number");
    }

    ImagesCollection imagesCollection {filePaths};
    auto images = imagesCollection.getImages();

    vector<Image> outputImages;

    // Get first image
    auto firstImage = images.at(0);
    outputImages.push_back(Image(*firstImage));

    // Convert first image to grayscale
    cout << "Converting the first image to greyscale" << endl;
    Mat firstImageGrey;
    cvtColor(firstImage->image, firstImageGrey, COLOR_BGR2GRAY);

    // Optional blurring
    if (blurSize > 0) {
        cout << "Blurring image" << endl;
        //GaussianBlur(firstImageGrey, firstImageGrey, Size( 7, 7), 0, 0);
        medianBlur(firstImageGrey, firstImageGrey, blurSize);
    }

    // Detect features of first image
    cout << "Detecting features of the first image" << endl;
    Features features = featureDescriptor_->detectFeatures(firstImageGrey);
    vector<KeyPoint> keyPoints = features.keyPoints;
    Mat descriptors = *features.descriptors;
    cout << "Detected " << descriptors.size() << " features" << endl;

    cout << "Starting loop over all files:" << endl;
    for (int i=1; i<images.size(); ++i) {
        cout << "  * File " << i << endl;

        // Converting image to grayscale
        cout << "    Converting the image to greyscale" << endl;
        Mat imageGrey;
        cvtColor(images.at(i)->image, imageGrey, COLOR_BGR2GRAY);

        // Optional blurring
        if (blurSize > 0) {
            cout << "    Blurring image" << endl;
            //GaussianBlur(imageGrey, imageGrey, Size( 7, 7), 0, 0);
            medianBlur(imageGrey, imageGrey, blurSize);
        }

        // Getting features
        cout << "    Detecting features of file " << i << endl;
        Features imageFeatures = featureDescriptor_->detectFeatures(imageGrey);
        vector<KeyPoint> imageKeyPoints = imageFeatures.keyPoints;
        Mat imageDescriptors = *imageFeatures.descriptors;

        // Matching to the first image
        cout << "    Matching features of file " << i << " to the first image" << endl;
        vector<DMatch> goodMatches = featureMatcher_->findMatches(imageDescriptors, descriptors);
        cout << "    Found " << goodMatches.size() << " good matches" << endl;

//        cout << "    Limiting good matches to " << featuresLimit << endl;
//        if (featuresLimit > 0 && goodMatches.size() < featuresLimit) {
//            goodMatches.resize(featuresLimit);
//        }


        std::vector<KeyPoint> kpts;
        std::vector<Point2f> obj;
        std::vector<Point2f> scene;
        for (size_t j=0; j < goodMatches.size(); j++) {
            auto imageKeyPoint = imageKeyPoints[goodMatches[j].queryIdx];

            if (isMatchingFilterEnabled) {
                float x = imageKeyPoint.pt.x;
                float y = imageKeyPoint.pt.y;
                cout << x << " " << y << " " << p1_.x << " " << p2_.x << " " << p1_.y << " " << p2_.y << endl;
                if (x < p1_.x || x > p2_.x || y < p1_.y || y > p2_.y) {
                    continue;
                }
            }

            kpts.push_back(imageKeyPoint);
            obj.push_back(imageKeyPoint.pt);
            scene.push_back(keyPoints[goodMatches[j].trainIdx].pt);
        }
        cout << "    Using " << scene.size() << " matches" << endl;

        if (showMatches_) {
            cout << "    Showing matches of image " << i << endl;
            Mat showMatches;
            drawKeypoints(imageGrey, kpts, showMatches, Scalar(0, 255, 0));
            resize(showMatches, showMatches, Size(800, 600));
            imshow("Image", showMatches);
            waitKey();
        }

        Mat homography = findHomography(obj, scene, RANSAC);

        // Projecting the image
        cout << "    Projecting the image " << i << endl;

        Mat newImage;
        warpPerspective(images.at(i)->image, newImage, homography, images.at(i)->image.size(), INTER_CUBIC);

        outputImages.push_back(Image(newImage));
    }

    ImagesCollection outputImagesCollection {outputImages};

    return outputImagesCollection;
}

void ImagesAligner::setMatchingFilter(Position p1, Position p2) {
    this->p1_ = p1;
    this->p2_ = p2;
    this->isMatchingFilterEnabled = true;
}

void ImagesAligner::unsetMatchingFilter() {
    this->isMatchingFilterEnabled = false;
}

