#pragma once

#ifndef IMAGESALIGNER_IMAGE_H
#define IMAGESALIGNER_IMAGE_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

/**
 * Image object.
 */
class Image {
public:
    Mat image;  ///< OpenCV Mat object - represents image.

    /**
     * Constructor.
     * @param filename Image filename.
     */
    explicit Image(const string& filename) {
        image = imread(filename);
    }

    /**
     * Constructor.
     * @param image OpenCV Mat object - represent image.
     */
    explicit Image(Mat image) {
        this->image = image;
    }

    /**
     * Copy constructor.
     * @param image Image object.
     */
    Image(Image const &image) {
        this->image = image.image;
    }

    void saveFile(const string& filename) const {
        imwrite(filename, image);
    }
};


#endif //IMAGESALIGNER_IMAGE_H
