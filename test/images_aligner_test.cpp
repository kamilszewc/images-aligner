#include "../include/images_aligner.h"
#include "../include/feature_matcher.h"
#include "../include/feature_descriptor.h"
#include <gtest/gtest.h>
#include <chrono>

TEST(ImagesAlignerTest, DefaultConstructor) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)",
            R"(../../inputs/river/5.jpg)",
            R"(../../inputs/river/6.jpg)"
    };

    ImagesAligner imagesAligner;
    imagesAligner.setShowMatches(true);
    auto imagesCollection = imagesAligner.align(filenames);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}

TEST(ImagesAlignerTest, DefaultConstructorWithBlur) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/forest/1.jpg)",
            R"(../../inputs/forest/2.jpg)",
            R"(../../inputs/forest/3.jpg)",
            R"(../../inputs/forest/4.jpg)",
    };

    ImagesAligner imagesAligner;
    imagesAligner.setShowMatches(true);
    auto imagesCollection = imagesAligner.align(filenames, 13);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}

TEST(ImagesAlignerTest, AkazeAndFlann) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)",
            R"(../../inputs/river/5.jpg)",
            R"(../../inputs/river/6.jpg)",
    };

    AkazeFeatureDescriptor featureDescriptor;
    FlannFeatureMatcher featureMatcher;
    ImagesAligner imagesAligner(featureDescriptor, featureMatcher);
    ImagesCollection imagesCollection = imagesAligner.align(filenames);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}


TEST(ImagesAlignerTest, AkazeAndBruteForce) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)",
            R"(../../inputs/river/5.jpg)",
            R"(../../inputs/river/6.jpg)",
    };

    AkazeFeatureDescriptor featureDescriptor;
    BruteForceFeatureMatcher featureMatcher;
    ImagesAligner imagesAligner(featureDescriptor, featureMatcher);
    ImagesCollection imagesCollection = imagesAligner.align(filenames);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}

TEST(ImagesAlignerTest, OrbAndBruteForce) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/river/1.jpg)",
            R"(../../inputs/river/2.jpg)",
            R"(../../inputs/river/3.jpg)",
            R"(../../inputs/river/4.jpg)",
            R"(../../inputs/river/5.jpg)",
            R"(../../inputs/river/6.jpg)",
    };

    OrbFeatureDescriptor featureDescriptor;
    BruteForceFeatureMatcher featureMatcher;
    ImagesAligner imagesAligner(featureDescriptor, featureMatcher);
    ImagesCollection imagesCollection = imagesAligner.align(filenames);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}

TEST(ImagesAlignerTest, DefaultConstructorForest) {
    auto start = chrono::steady_clock::now();

    vector<filesystem::path> filenames = {
            R"(../../inputs/forest/1.jpg)",
            R"(../../inputs/forest/2.jpg)",
            R"(../../inputs/forest/3.jpg)",
            R"(../../inputs/forest/4.jpg)",
    };

    ImagesAligner imagesAligner;
    auto imagesCollection = imagesAligner.align(filenames);
    imagesCollection.saveFiles("../../results");

    auto end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> elapsedTime = end - start;
    cout << "Elapsed time: " << elapsedTime.count() << "ms";
}