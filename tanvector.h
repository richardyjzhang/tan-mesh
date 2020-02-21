#ifndef TANVECTOR_H
#define TANVECTOR_H

class TanVector
{
public:
    TanVector();
    TanVector(double x, double y, double z);

private:
    static double _TOLERANCE_;
    double x;
    double y;
    double z;

public:
    static void setTolerance(double tolerance);
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

public:
    double length() const;
    TanVector normalize() const;
    double distanceTo(const TanVector & vec) const;
    static TanVector crossProduct(const TanVector & vec1, const TanVector & vec2);
    static bool opposite(const TanVector & vec1, const TanVector & vec2);
    friend bool operator < (const TanVector & vec1, const TanVector & vec2);
    friend TanVector operator + (const TanVector & vec1, const TanVector & vec2);
    friend TanVector operator - (const TanVector & vec1, const TanVector & vec2);
    friend TanVector operator * (double scale, const TanVector & vec);
};

bool operator < (const TanVector & vec1, const TanVector & vec2);
TanVector operator + (const TanVector & vec1, const TanVector & vec2);
TanVector operator - (const TanVector & vec1, const TanVector & vec2);
TanVector operator * (double scale, const TanVector & vec);

#endif // TANVECTOR_H
