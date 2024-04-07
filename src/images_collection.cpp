#include "../include/images_collection.h"
#include "../include/image.h"
#include <filesystem>

using namespace cv;

ImagesCollection::ImagesCollection(const vector<filesystem::path>& filePaths) {
    for (const auto& filename : filePaths) {
        auto* image = new Image(filename.generic_u8string());
        images_.push_back(image);
    }
}

ImagesCollection::ImagesCollection(const vector<string> &filenames) {
    for (const auto& filename : filenames) {
        auto* image = new Image(filename);
        images_.push_back(image);
    }
}

ImagesCollection::ImagesCollection(const vector<Image> &images) {
    for (const auto& image : images) {
        images_.push_back(new Image(image));
    }
}

ImagesCollection::~ImagesCollection() {
    for (auto& image : images_) {
        delete image;
    }
}

void ImagesCollection::saveFiles(const filesystem::path& directoryPath) {
    if (!filesystem::exists(directoryPath)) {
        throw exception("Directory does not exist");
    }

    if (!filesystem::is_directory(directoryPath)) {
        throw exception("It is not directory");
    }

    for (int i=0; i<images_.size(); ++i) {
        string filename = to_string(i+1) + ".jpg";
        filesystem::path filePath = directoryPath / filesystem::path(filename);
        images_.at(i)->saveFile(filePath.generic_u8string());
    }
}








