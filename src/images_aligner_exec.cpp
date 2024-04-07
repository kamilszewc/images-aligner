#include "../include/images_aligner.h"
#include <filesystem>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    cout << "ImagesAligner - wrapper around OpenCV platform to align shifted images" << endl;
    cout << "Copyrights Kamil Szewc 2022-2024 (Apache 2 License)" << endl;

    if (argc < 3) {
        cout << "Usage: ImagesAligner file1.jpg file2.jpg ... fileN.jpg outputDirectory" << endl;
        return EXIT_FAILURE;
    }

    // Collecting all input files
    vector<filesystem::path> inputFiles;
    for (int i=1; i<argc-1; ++i) {
        inputFiles.push_back(argv[i]);
    }

    // Checking if input files exist and if it is file
    for (auto& inputFile : inputFiles) {
        if (!filesystem::exists(inputFile)) {
            cerr << "Input file: " << inputFile << ", does not exist" << endl;
            return EXIT_FAILURE;
        }

        if (!filesystem::is_regular_file(inputFile)) {
            cerr << "Input file: " << inputFile << ", is not a file" << endl;
            return EXIT_FAILURE;
        }
    }

    // Getting output directory
    filesystem::path outputDir = argv[argc-1];

    // Checking if output path points to directory that exist
    if (!filesystem::exists(outputDir)) {
        cerr << "Output directory: " << outputDir << ", does not exist" << endl;
        return EXIT_FAILURE;
    }
    if (!filesystem::is_directory(outputDir)) {
        cerr << "Provided output directory: " << outputDir << ", is not a directory" << endl;
        return EXIT_FAILURE;
    }

    ImagesAligner imagesAligner;
    ImagesCollection imagesCollection = imagesAligner.align(inputFiles);
    imagesCollection.saveFiles(outputDir);

    return EXIT_SUCCESS;
}
