#pragma once

#ifndef IMAGESALIGNER_FEATURE_DESCRIPTOR_H
#define IMAGESALIGNER_FEATURE_DESCRIPTOR_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <vector>

namespace cv { // Forward declarations
    class Mat;
    class KeyPoint;
    class Feature2D;
    template <class T>
    class Ptr;
}
using namespace std;
using namespace cv;

/**
 * Features class.
 */
class Features {
public:
    Mat* descriptors;
    vector<KeyPoint> keyPoints;

    /**
     * Constructor.
     * Wrapper for storing together OpenCV Mat and vector<KeyPoints> objects.
     * @param descriptors OpenCV feature detection descriptors.
     * @param keyPoints OpenCV feature detection key points.
     */
    EXPORT Features(Mat& descriptors, vector<KeyPoint>& keyPoints);

    /**
     * Destructor.
     */
    EXPORT ~Features();
};

/**
 * FeatureDescriptor class.
 */
class FeatureDescriptor {
protected:
    Ptr<Feature2D> *featureDescriptor_;
public:
    /**
     * Constructor.
     */
    EXPORT FeatureDescriptor();

    /**
     * Destructor.
     */
    EXPORT ~FeatureDescriptor();

    /**
     * Method starts features detection procedure.
     * @param image Image (OpenCV Mat object)
     * @return Features object.
     */
    EXPORT Features detectFeatures(Mat& image) const;
};

/**
 * SiftFeatureDescriptor class.
 */
class SiftFeatureDescriptor : public FeatureDescriptor {
public:
    /**
     * Constructor.
     */
    EXPORT SiftFeatureDescriptor();

    /**
     * Default destructor.
     */
    EXPORT ~SiftFeatureDescriptor() = default;
};

/**
 * OrbFeatureDescriptor class.
 */
class OrbFeatureDescriptor : public FeatureDescriptor {
public:
    /**
     * Constructor.
     */
    EXPORT OrbFeatureDescriptor();

    /**
     * Default destructor.
     */
    EXPORT ~OrbFeatureDescriptor() = default;
};

/**
 * KazeFeatureDescriptor class.
 */
class KazeFeatureDescriptor : public FeatureDescriptor {
public:
    /**
     * Constructor.
     */
    EXPORT KazeFeatureDescriptor();

    /**
     * Default destructor.
     */
    EXPORT ~KazeFeatureDescriptor() = default;
};

/**
 * AkazeFeatureDescriptor class.
 */
class AkazeFeatureDescriptor : public FeatureDescriptor {
public:
    /**
     * Constructor.
     */
    EXPORT AkazeFeatureDescriptor();

    /**
     * Default destructor.
     */
    EXPORT ~AkazeFeatureDescriptor() = default;
};

#endif //IMAGESALIGNER_FEATURE_DESCRIPTOR_H
