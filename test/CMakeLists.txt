find_package(GTest CONFIG REQUIRED)

add_executable(ImagesAlignerTest images_aligner_test.cpp)
target_link_libraries(ImagesAlignerTest PRIVATE GTest::gtest GTest::gtest_main images_aligner)

add_executable(FeatureDescriptorTest feature_descriptor_test.cpp)
target_link_libraries(FeatureDescriptorTest PRIVATE GTest::gtest GTest::gtest_main images_aligner)

add_executable(ImagesCollectionTest images_collection_test.cpp)
target_link_libraries(ImagesCollectionTest PRIVATE GTest::gtest GTest::gtest_main images_aligner)

add_test(ImagesAlignerTests ImagesAlignerTest)
add_test(ImagesAlignerTests FeatureDescriptorTest)
add_test(ImagesAlignerTests ImagesCollectionTest)