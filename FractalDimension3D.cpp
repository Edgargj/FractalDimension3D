#include "FractalDimension3D.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

FractalDimension3D::FractalDimension3D(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.substr(0, 4) == "ATOM" || line.substr(0, 6) == "HETATM") {
            std::stringstream ss(line.substr(30, 24));
            Atom atom;
            ss >> atom.x >> atom.y >> atom.z;
            atoms.push_back(atom);
        }
    }
    calculateGeometricCenter();
    calculateMaxDistanceAndFarthestAtom();
}

void FractalDimension3D::calculateGeometricCenter() {
    double sumX = 0, sumY = 0, sumZ = 0;
    for (const auto& atom : atoms) {
        sumX += atom.x;
        sumY += atom.y;
        sumZ += atom.z;
    }
    int n = atoms.size();
    geometricCenter = {sumX / n, sumY / n, sumZ / n};
}

void FractalDimension3D::calculateMaxDistanceAndFarthestAtom() {
    maxDistance = 0;
    for (const auto& atom : atoms) {
        double distance = geometricCenter.distanceTo(atom);
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestAtom = atom;
        }
    }
}

void FractalDimension3D::generateSpheresAndCountAtoms(const std::vector<int>& radii, const std::string& spheres_filename) {
    int minSpheresPerRadius = 1;
    std::vector<Sphere> spheres;

    for (int radius : radii) {
        for (int i = 0; i < minSpheresPerRadius; ++i) {
            Atom newCenter = Sphere::generateRandomCenter(geometricCenter, maxDistance, radius, atoms);
            spheres.emplace_back(newCenter, radius);
        }
    }

    std::vector<std::vector<Atom>> atomsInSpheres = Sphere::countAtomsInSpheres(atoms, spheres);

    // Guardar los resultados de las esferas pequeñas en un archivo
    std::ofstream spheresFile(spheres_filename);
    spheresFile << std::fixed << std::setprecision(2);  // Establece formato fijo y precisión de dos decimales
    spheresFile << "Coor-X  Coor-Y  Coor-Z  rmax NumAt" << std::endl; // Eliminar setw y ajustar espaciado

    for (size_t i = 0; i < spheres.size(); ++i) {
        spheresFile << spheres[i].center.x << "  "
                    << spheres[i].center.y << "  "
                    << spheres[i].center.z << "  "
                    << spheres[i].radius << "  "
                    << atomsInSpheres[i].size() << std::endl;
    }
    spheresFile.close();
}

void FractalDimension3D::savePDBCoordinates(const std::string& filename) const {
    std::ofstream pdbFile(filename);
    pdbFile << std::fixed << std::setprecision(2);  // Establece formato fijo y precisión de dos decimales
    pdbFile << "     X       Y       Z" << std::endl;  // Eliminar setw y ajustar espaciado
    for (const auto& atom : atoms) {
        pdbFile << atom.x << "  " << atom.y << "  " << atom.z << std::endl;
    }
    pdbFile.close();
}

void FractalDimension3D::saveGeometricData(const std::string& filename) const {
    std::ofstream resultsFile(filename);
    resultsFile << std::fixed << std::setprecision(2);  // Establece formato fijo y precisión de dos decimales
    resultsFile << "CGeoX   CGeoY   CGeoZ   CMaxX   CMaxY   CMaxZ  Rmax" << std::endl;

    resultsFile << geometricCenter.x << "  "
                << geometricCenter.y << "  "
                << geometricCenter.z << "  "
                << farthestAtom.x << "  "
                << farthestAtom.y << "  "
                << farthestAtom.z << "  "
                << maxDistance << std::endl;

    resultsFile.close();
}

