#ifndef FRACTALDIMENSION3D_H
#define FRACTALDIMENSION3D_H

#include "Atom.h"
#include "Sphere.h"
#include <vector>
#include <string>

class FractalDimension3D {
private:
    std::vector<Atom> atoms;
    Atom geometricCenter;
    double maxDistance;
    Atom farthestAtom;

public:
    FractalDimension3D(const std::string& filename);
    void calculateGeometricCenter();
    void calculateMaxDistanceAndFarthestAtom();
    void generateSpheresAndCountAtoms(const std::vector<int>& radii, const std::string& spheres_filename);
    void savePDBCoordinates(const std::string& filename) const;
    void saveGeometricData(const std::string& filename) const;
};

#endif // FRACTALDIMENSION3D_H

