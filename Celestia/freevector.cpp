#include "freevector.h"


const qreal FreeVector::getX() const
{
    return x;
}

const qreal FreeVector::getY() const
{
    return y;
}

const qreal FreeVector::getLength() const
{
    return qSqrt(x * x + y * y);
}

const qreal FreeVector::dot(const FreeVector &v) const
{
    return x * v.x + y * v.y;
}

const FreeVector FreeVector::operator+(const FreeVector &p) const
{
    return {x + p.x, y + p.y};
}

const FreeVector FreeVector::operator-(const FreeVector &p) const
{
    return {x - p.x, y - p.y};
}

const FreeVector FreeVector::operator*(const qreal &r) const
{
    return {x * r, y * r};
}

const FreeVector FreeVector::operator*(const FreeVector& v) const
{
    return {x * v.x, y * v.y};
}

const FreeVector FreeVector::operator /(const qreal &r) const
{
    return {x / r, y / r};
}
