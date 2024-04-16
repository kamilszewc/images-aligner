#pragma once

#ifndef IMAGESALIGNER_POSITION_H
#define IMAGESALIGNER_POSITION_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#include <string>

/**
 * Position object.
 */
class Position {
public:
    int x;
    int y;

    /**
     * Constructor.
     * @param filename Image filename.
     */
    Position() : x(0), y(0) {}

    /**
     * Constructor.
     * @param filename Image filename.
     */
    Position(int x, int y) : x(x), y(y) {}

    /**
     * Default destructor.
     */
     ~Position() = default;

     double getDistance(Position position) const {
         long dx = position.x - this->x;
         long dy = position.y - this->y;
         return sqrt( dx*dx + dy*dy);
     }
};


#endif //IMAGESALIGNER_IMAGE_H
