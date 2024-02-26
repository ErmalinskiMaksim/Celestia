#ifndef FREEVECTOR_H
#define FREEVECTOR_H
#include <QtMath>

class FreeVector
{
public:
    FreeVector(){}
    FreeVector(qreal X, qreal Y) : x(X), y(Y){}

    const qreal getX() const;
    const qreal getY() const;
    const qreal getLength() const;
    const qreal dot(const FreeVector& v) const;

    const FreeVector operator+(const FreeVector& p) const;
    const FreeVector operator-(const FreeVector& p) const;
    const FreeVector operator*(const qreal& r) const;
    const FreeVector operator*(const FreeVector& v) const;
    const FreeVector operator/(const qreal& r) const;
private:
    qreal x;
    qreal y;
};

#endif // FREEVECTOR_H

