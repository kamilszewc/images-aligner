# ImagesAligner

## General
Simple to use C++ library for images aligning. It is wrapper around OpenCV library.
Currently, it supports two feature detectors:
 - AKAZE
 - ORB

and two feature matchers:

- BruteForce
- FLANN

Be careful when using, the project is in very early stage of development.

## Usage

Simple usage:
```c++
vector<filesystem::path> filenames = {
        R"(1.jpg)",
        R"(2.jpg)",
        R"(3.jpg)",
};

ImagesAligner imagesAligner;
auto imagesCollection = imagesAligner.align(filenames);
imagesCollection.saveFiles("resultsFolder");
```

More complex usage (custom feature matcher and descriptor):
```c++
vector<filesystem::path> filenames = {
        R"(1.jpg)",
        R"(2.jpg)",
        R"(3.jpg)",
};

AkazeFeatureDescriptor featureDescriptor;
FlannFeatureMatcher featureMatcher;
ImagesAligner imagesAligner(featureDescriptor, featureMatcher);
ImagesCollection imagesCollection = imagesAligner.align(filenames);
imagesCollection.saveFiles("resultsFolder");
```