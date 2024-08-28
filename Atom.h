#ifndef ATOM_H
#define ATOM_H

class Atom {
public:
    double x, y, z;

    Atom(double x = 0, double y = 0, double z = 0);
    double distanceTo(const Atom& other) const;
};

#endif // ATOM_H

