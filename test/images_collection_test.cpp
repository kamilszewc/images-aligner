#include "../include/images_collection.h"
#include "../include/image.h"
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>

TEST(ImagesCollectionTest, ConstructorWithPaths) {

    vector<filesystem::path> filenames {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)"
    };

    ImagesCollection imagesCollection {filenames};
    imagesCollection.saveFiles(R"(../../results)");
}

TEST(ImagesCollectionTest, ContructorWithMats) {

    vector<string> filenames {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)"
    };

    vector<Image> images;
    for (auto& filename : filenames) {
        cv::Mat mat = cv::imread(filename);
        images.push_back(Image(mat));
    }

    ImagesCollection imagesCollection {images};
    imagesCollection.saveFiles(R"(../../results)");
}

TEST(ImagesCollectionTest, ContructorWithMatsNoPtr) {

    vector<string> filenames{
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)"
    };

    vector<Image> images;
    for (auto &filename: filenames) {
        cv::Mat mat = cv::imread(filename);
        images.push_back(Image(mat));
    }

    ImagesCollection imagesCollection {images};
    imagesCollection.saveFiles(R"(../../results)");
}
