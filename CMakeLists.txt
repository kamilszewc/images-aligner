cmake_minimum_required(VERSION 3.12)
project(ImagesAligner)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

find_package(OpenCV CONFIG REQUIRED)

add_library(images_aligner STATIC
        src/images_aligner.cpp
        include/images_aligner.h

        include/feature_descriptor.h
        src/feature_descriptor.cpp

        include/feature_matcher.h
        src/feature_matcher.cpp

        include/images_collection.h
        src/images_collection.cpp

        include/image.h

        include/images_aligner_exception.h
)

target_include_directories(images_aligner PUBLIC include)
target_link_libraries(images_aligner PRIVATE ${OpenCV_LIBS})

add_executable(ImagesAligner src/images_aligner_exec.cpp)
target_link_libraries(ImagesAligner PRIVATE images_aligner)

add_subdirectory(test)