#pragma once

#ifndef IMAGESALIGNER_IMAGES_COLLECTION_H
#define IMAGESALIGNER_IMAGES_COLLECTION_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <vector>
#include <string>
#include <filesystem>

class Image; // Forward declaration

using namespace std;

/**
 * ImagesCollection class.
 */
class ImagesCollection {
private:
    vector<Image*> images_;
public:
    /**
     * Constructor.
     * @param filePaths Vector of paths to images.
     */
    EXPORT explicit ImagesCollection(const vector<filesystem::path>& filePaths);

    /**
     * Constructor.
     * @param filePaths Vector of strings representing paths to images.
     */
    EXPORT explicit ImagesCollection(const vector<string>& filenames);

    /**
     * Constructor.
     * This variant of constructor requires Image object (forward declaration).
     * @param filePaths Vector of Images.
     */
    EXPORT explicit ImagesCollection(const vector<Image>& images);

    /**
     * Destructor.
     */
    EXPORT ~ImagesCollection();

    /**
     * Returns vector of Image objects.
     * @return vector of Image objects.
     */
    EXPORT vector<Image*> getImages() {return images_;}

    /**
     * Saves images to specified directory.
     * @param directoryPath Path to output directory.
     */
    EXPORT void saveFiles(const filesystem::path& directoryPath);
};

#endif //IMAGESALIGNER_IMAGES_COLLECTION_H
