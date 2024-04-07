#include <opencv2/opencv.hpp>
#include "feature_descriptor.h"

SiftFeatureDescriptor::SiftFeatureDescriptor() {
    *featureDescriptor_ = SIFT::create();
}

OrbFeatureDescriptor::OrbFeatureDescriptor() {
    *featureDescriptor_ = ORB::create();
}

KazeFeatureDescriptor::KazeFeatureDescriptor() {
    *featureDescriptor_ = KAZE::create();
}

AkazeFeatureDescriptor::AkazeFeatureDescriptor() {
    *featureDescriptor_ = AKAZE::create();
}


Features FeatureDescriptor::detectFeatures(cv::Mat& image) const {
    vector<KeyPoint> keyPoints;
    Mat descriptors;
    (*featureDescriptor_)->detectAndCompute(image, noArray(), keyPoints, descriptors);

    Features features(descriptors, keyPoints);
    return features;
}

FeatureDescriptor::FeatureDescriptor() {
    featureDescriptor_ = new Ptr<Feature2D>();
}

FeatureDescriptor::~FeatureDescriptor() {
    delete featureDescriptor_;
}


Features::Features(Mat& descriptors, vector<KeyPoint> &keyPoints)
    : descriptors(new Mat(descriptors)), keyPoints(keyPoints) {}

Features::~Features() {
    delete descriptors;
}
