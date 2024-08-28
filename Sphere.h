#ifndef SPHERE_H
#define SPHERE_H

#include "Atom.h"
#include <vector>
#include <random>

class Sphere {
public:
    Atom center;
    double radius;

    Sphere(const Atom& center, double radius);
    static Atom generateRandomCenter(const Atom& baseCenter, double maxRadius, double sphereRadius, const std::vector<Atom>& atoms);
    static std::vector<std::vector<Atom>> countAtomsInSpheres(const std::vector<Atom>& atoms, const std::vector<Sphere>& spheres);
};

#endif // SPHERE_H

