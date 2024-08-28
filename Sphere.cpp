#include "Sphere.h"

Sphere::Sphere(const Atom& center, double radius) : center(center), radius(radius) {}

Atom Sphere::generateRandomCenter(const Atom& baseCenter, double maxRadius, double sphereRadius, const std::vector<Atom>& atoms) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-maxRadius, maxRadius);
    Atom newCenter;

    bool hasAtoms = false;
    while (!hasAtoms) {
        newCenter = {baseCenter.x + dis(gen), baseCenter.y + dis(gen), baseCenter.z + dis(gen)};
        hasAtoms = false;
        if (baseCenter.distanceTo(newCenter) + sphereRadius <= maxRadius) {
            for (const auto& atom : atoms) {
                if (newCenter.distanceTo(atom) <= sphereRadius) {
                    hasAtoms = true;
                    break;
                }
            }
        }
    }
    return newCenter;
}

std::vector<std::vector<Atom>> Sphere::countAtomsInSpheres(const std::vector<Atom>& atoms, const std::vector<Sphere>& spheres) {
    std::vector<std::vector<Atom>> atomsInSpheres(spheres.size());

    for (size_t i = 0; i < spheres.size(); ++i) {
        for (const auto& atom : atoms) {
            if (spheres[i].center.distanceTo(atom) <= spheres[i].radius) {
                atomsInSpheres[i].push_back(atom);
            }
        }
    }

    return atomsInSpheres;
}

