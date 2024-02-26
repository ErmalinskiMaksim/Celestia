#ifndef BODY_H
#define BODY_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <vector>
#include <list>
#include "freevector.h"

class Body : public QGraphicsEllipseItem
{
public:
    Body(const QColor& c, const QString& n, const qreal& r, const qreal& m, const FreeVector& p, const FreeVector& v, const FreeVector& a);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // getters
    FreeVector get_position() const;
    FreeVector get_velocity() const;
    FreeVector get_acceleration() const;
    const QString* get_name() const;
    const qreal get_radius() const;
    const qreal get_mass() const;
    const QColor get_color() const;

    // setters
    void set_name(QString& name);
    void set_position(const FreeVector& v);
    void set_velocity(const FreeVector& v);
    void set_acceleration(const FreeVector& v);

    // static
    static void setTrace(bool isOn);
protected:
    void advance(int phase) override;
private:
    static bool isTrace; // is trace mode on

    FreeVector m_position;
    FreeVector m_velocity;
    FreeVector m_acceleration;

    const qreal m_radius;
    const QColor m_color;
    qreal m_mass;
    QString m_name;
    std::list<FreeVector> m_trace;
};

#endif // BODY_H
