#include "Atom.h"
#include <cmath>

Atom::Atom(double x, double y, double z) : x(x), y(y), z(z) {}

double Atom::distanceTo(const Atom& other) const {
    return std::sqrt(std::pow(x - other.x, 2) +
                     std::pow(y - other.y, 2) +
                     std::pow(z - other.z, 2));
}

