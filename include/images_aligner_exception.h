#ifndef IMAGESALIGNER_IMAGES_ALIGNER_EXCEPTION_H
#define IMAGESALIGNER_IMAGES_ALIGNER_EXCEPTION_H

#include <exception>

class ImagesAlignerException : public std::exception {
public:
    explicit ImagesAlignerException(const char*  message) : std::exception(message) {}
};

#endif //IMAGESALIGNER_IMAGES_ALIGNER_EXCEPTION_H
