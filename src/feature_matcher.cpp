
#include <opencv2/opencv.hpp>
#include "feature_matcher.h"

BruteForceFeatureMatcher::BruteForceFeatureMatcher() {
}

vector<DMatch> BruteForceFeatureMatcher::findMatches(Mat descriptorsA, Mat descriptorsB) const {
    // Constructing BruteForce matcher
    BFMatcher matcher(NORM_HAMMING);

    // Matching
    vector<vector<DMatch>> matches;
    matcher.knnMatch(descriptorsA, descriptorsB, matches, 2);

    // Selecting only good matches
    vector<DMatch> goodMatches;
    for (auto& match : matches) {
        if (match[0].distance > 0.8 * match[1].distance) continue;
        goodMatches.push_back(match[0]);
    }

    return goodMatches;
}

FlannFeatureMatcher::FlannFeatureMatcher() : nnMatchRatio(0.8) {
}

FlannFeatureMatcher::FlannFeatureMatcher(float nnMatchRatio) : nnMatchRatio(nnMatchRatio) {
}

vector<DMatch> FlannFeatureMatcher::findMatches(Mat descriptorsA, Mat descriptorsB) const {
    // Constructing FLANN matcher
    FlannBasedMatcher matcher(cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2));

    // Matching
    vector<vector<DMatch>> matches;
    matcher.knnMatch(descriptorsA, descriptorsB, matches, 2);

    // Selecting only good matches
    vector<DMatch> goodMatches;
    for (auto& match : matches) {
        if (match[0].distance / match[1].distance > nnMatchRatio) continue;
        goodMatches.push_back(match[0]);
    }

    // Sorting good matches based on distance
//    std::sort(goodMatches.begin(), goodMatches.end(), [](DMatch a, DMatch b) { return a.distance > b.distance; });

    return goodMatches;
}