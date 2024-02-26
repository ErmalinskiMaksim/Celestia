#include "body.h"

bool Body::isTrace = false;

Body::Body(const QColor& c, const QString &n, const qreal &r, const qreal &m, const FreeVector &p, const FreeVector &v, const FreeVector &a)
    : m_name(n), m_radius(r), m_mass(m), m_position(p), m_velocity(v), m_acceleration(a), m_color(c), m_trace(0)
{

}

QRectF Body::boundingRect() const
{
    return {m_position.getX() - m_radius, m_position.getY() - m_radius, m_radius * 2, m_radius * 2};
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(m_color));
    painter->setBrush(QBrush(m_color));

    painter->drawEllipse(boundingRect());

    if(isTrace) for(auto&& a : m_trace)
            painter->drawPoint(QPoint(m_position.getX(), m_position.getY()));
}

FreeVector Body::get_position() const
{
    return m_position;
}

FreeVector Body::get_velocity() const
{
    return m_velocity;
}

FreeVector Body::get_acceleration() const
{
    return m_acceleration;
}

const QString* Body::get_name() const
{
    return &m_name;
}

const qreal Body::get_radius() const
{
    return m_radius;
}

const qreal Body::get_mass() const
{
    return m_mass;
}

const QColor Body::get_color() const
{
    return m_color;
}

void Body::set_name(QString &name)
{
    m_name = name;
}

void Body::set_position(const FreeVector& v)
{
    m_position = v;
}

void Body::set_velocity(const FreeVector& v)
{
    m_velocity = v;
}

void Body::set_acceleration(const FreeVector& v)
{
    m_acceleration = v;
}

void Body::setTrace(bool isOn)
{
    isTrace = isOn;
}

void Body::advance(int phase)
{
    if(isTrace)
    {
        if(m_trace.size() > 500)
            m_trace.pop_back();
        m_trace.push_front(m_position);
    }

    update();
}
