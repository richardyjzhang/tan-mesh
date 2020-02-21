#include "tanvector.h"
#include <cmath>

double TanVector::_TOLERANCE_ = 0.001;

TanVector::TanVector()
    : x(0), y(0), z(0) { }

TanVector::TanVector(double x, double y, double z)
    : x(x), y(y), z(z) { }

void TanVector::setTolerance(double tolerance) { _TOLERANCE_ = tolerance; }

double TanVector::getX() const { return x; }

double TanVector::getY() const { return y; }

double TanVector::getZ() const { return z; }

void TanVector::setX(double x) { this->x = x; }

void TanVector::setY(double y) { this->y = y; }

void TanVector::setZ(double z) { this->z = z; }

double TanVector::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double TanVector::distanceTo(const TanVector & vec) const
{
    return std::sqrt((x - vec.x) * (x - vec.x) +
                     (y - vec.y) * (y - vec.y) +
                     (z - vec.z) * (z - vec.z));
}

TanVector TanVector::crossProduct(const TanVector & vec1, const TanVector & vec2)
{
    TanVector vecRe;

    vecRe.x = vec1.y * vec2.z - vec1.z * vec2.y;
    vecRe.y = vec1.z * vec2.x - vec1.x * vec2.z;
    vecRe.z = vec1.x * vec2.y - vec1.y * vec2.x;

    return vecRe;
}

bool TanVector::opposite(const TanVector & vec1, const TanVector & vec2)
{
    // 如果有零向量，则不应该认为是反向向量
    if (vec1.length() < _TOLERANCE_ || vec2.length() < _TOLERANCE_) return false;

    TanVector vec = vec1.normalize() + vec2.normalize();
    return vec.length() < _TOLERANCE_;
}

TanVector TanVector::normalize() const
{
    TanVector vec;
    double len = length();
    if (len > _TOLERANCE_)
    {
        vec.x = x / len;
        vec.y = y / len;
        vec.z = z / len;
    }

    return vec;
}

bool operator < (const TanVector & vec1, const TanVector & vec2)
{
    if (vec1.x < vec2.x) return true;
    if ((std::abs(vec1.x - vec2.x) < TanVector::_TOLERANCE_) && (vec1.y < vec2.y)) return true;
    if ((std::abs(vec1.y - vec2.y) < TanVector::_TOLERANCE_) && (vec1.z < vec2.z)) return true;
    return false;
}

TanVector operator + (const TanVector & vec1, const TanVector & vec2)
{
    TanVector vec(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
    return vec;
}

TanVector operator - (const TanVector & vec1, const TanVector & vec2)
{
    TanVector vec(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return vec;
}

TanVector operator * (double scale, const TanVector & vec)
{
    TanVector v(scale * vec.x, scale * vec.y, scale * vec.z);
    return v;
}
