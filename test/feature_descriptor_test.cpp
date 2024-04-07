#include "../include/feature_descriptor.h"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

TEST(FeatureDescriptorTest, SiftDescriptor) {

    cv::Mat image = cv::imread(R"(../../inputs/river/1.jpg)");

    SiftFeatureDescriptor siftFeatureDescriptor;
    std::cout << siftFeatureDescriptor.detectFeatures(image).descriptors->size << std::endl;
}