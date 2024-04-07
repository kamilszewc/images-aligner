#pragma once

#ifndef IMAGESALIGNER_FEATURE_MATCHER_H
#define IMAGESALIGNER_FEATURE_MATCHER_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

namespace cv {  // Forward declarations
    class DMatch;
    class Mat;
};
using namespace cv;
using namespace std;

/**
 * FeatureMatcher abstract class.
 */
class FeatureMatcher {
public:
    EXPORT virtual vector<DMatch> findMatches(Mat descriptorsA, Mat descriptorsB) const = 0;
    EXPORT virtual ~FeatureMatcher() = default;
};

/**
 * BruteForceFeatureMarcher class.
 */
class BruteForceFeatureMatcher : public FeatureMatcher {
public:
    EXPORT BruteForceFeatureMatcher();
    EXPORT ~BruteForceFeatureMatcher() override = default;

    EXPORT vector<DMatch> findMatches(Mat descriptorsA, Mat descriptorsB) const override;
};

/**
 * FlannFeatureMarcher class.
 */
class FlannFeatureMatcher : public FeatureMatcher {
private:
    float nnMatchRatio;
public:
    EXPORT FlannFeatureMatcher();
    EXPORT explicit FlannFeatureMatcher(float nnMatchRatio);
    EXPORT ~FlannFeatureMatcher() override = default;

    EXPORT vector<DMatch> findMatches(Mat descriptorsA, Mat descriptorsB) const override;
};

#endif //IMAGESALIGNER_FEATURE_MATCHER_H
