#pragma once

#include "vec3.hxx"

class ray {

public:
        ray() {}
        ray(const point3 &origin, const vec3 &direction) : orig(origin), direc(direction) {}

        point3 origin() const { return orig; }
        vec3 direction() const { return direc; }

        point3 at(double t) const { return orig + t * direc; }

public:
        point3 orig;
        vec3    direc;
};