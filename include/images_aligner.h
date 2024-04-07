#pragma once

#ifndef IMAGESALIGNER_IMAGES_ALIGNER_H
#define IMAGESALIGNER_IMAGES_ALIGNER_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "images_collection.h"

class FeatureDescriptor;    // Forward declarations
class FeatureMatcher;

/**
 * ImagesAligner class.
 */
class ImagesAligner {
private:
    FeatureDescriptor* featureDescriptor_;
    FeatureMatcher* featureMatcher_;
    bool isInClassInitialized_ = false;
    bool showMatches_ = false;

public:
    /**
     * Default constructor.
     * It uses AKAZE feature descriptor and FLANN feature matcher.
     */
    EXPORT ImagesAligner();

    /**
     * Constructor.
     * It allows to choose a feature descriptor and feature matcher.
     * @param featureDescriptor FeatureDescriptor object.
     * @param featureMatcher FeatureMatcher object.
     */
    EXPORT ImagesAligner(FeatureDescriptor& featureDescriptor, FeatureMatcher& featureMatcher);

    /**
     * Destructor.
     */
    EXPORT ~ImagesAligner();

    /**
     * Method starts the process of images aligning.
     * @param filePaths Vector of file paths.
     * @param blurSize Optional blur (median) - can make aligning faster (must be odd number)
     * @return ImagesCollection object.
     */
    EXPORT ImagesCollection align(const vector<filesystem::path>& filePaths, int blurSize = 0) const;

    /**
     * Setter to turn on displaying best matches matches during aligning.
     * @param showMatches If true, the best matches will be displayed.
     */
    EXPORT void setShowMatches(bool showMatches) {
        showMatches_ = showMatches;
    }
};

#endif //IMAGESALIGNER_IMAGES_ALIGNER_H
