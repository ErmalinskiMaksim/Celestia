#include "bodymanager.h"
#include <QRandomGenerator>
#define EULER
BodyManager::BodyManager() : m_bodies(0)
{

}

bool BodyManager::createBody(QComboBox *box)
{
    m_bodies.push_back(m_dialog.getBody(nullptr));

    return updateComboBox(box, m_bodies.back()->get_name());
}

bool BodyManager::randomCreate(QComboBox *box)
{
    const QString name = QString::number(QRandomGenerator::global()->generate());

    const int radius = QRandomGenerator::global()->bounded(5, 20);
    const qreal mass = -1;//QRandomGenerator::global()->bounded(0, 1);

    const qreal posX = QRandomGenerator::global()->bounded(radius, 621 - radius);
    const qreal posY = QRandomGenerator::global()->bounded(radius, 521 - radius);
    const FreeVector position = {posX, posY};

    const qreal velX = QRandomGenerator::global()->bounded(-1000, 1000) / 1000;
    const qreal velY = QRandomGenerator::global()->bounded(-1000, 1000) / 1000;
    const FreeVector velocity = {velX, velY};

    const qreal accX = QRandomGenerator::global()->bounded(-1000, 1000) / 5000;
    const qreal accY = QRandomGenerator::global()->bounded(-1000, 1000) / 5000;
    const FreeVector acceleration = {accX, accY};

    const int red = QRandomGenerator::global()->bounded(0, 255);
    const int green = QRandomGenerator::global()->bounded(0, 255);
    const int blue = QRandomGenerator::global()->bounded(0, 255);

    m_bodies.push_back(new Body(QColor(red, green, blue), name, radius, qPow(10, mass), position, velocity, acceleration));
    return updateComboBox(box, &name);
}

void BodyManager::deleteBody(const QString &&name)
{
    int item;
    for(item = 0; (item < m_bodies.size()) && (*m_bodies[item]->get_name() != name); ){++item;}
    m_bodies.erase(m_bodies.begin() + item);
}
\
    void BodyManager::updateBodies()
{
#ifdef EULER
    MovementAlgorithm::eulersMethod(m_bodies);
#endif

#ifdef RUNGE_KUTTA
    MovementAlgorithm::rungeKutta4(m_bodies);
#endif
}

Body* const BodyManager::getItem(const QString &name) const
{
    int item;
    for(item = 0; (item < m_bodies.size()) && (*m_bodies[item]->get_name() != name);){++item;}
    return m_bodies[item];
}

Body* const BodyManager::getLast() const
{
    return m_bodies.back();
}

bool BodyManager::isEmpty() const
{
    return m_bodies.empty();
}

const std::size_t BodyManager::getAmount() const
{
    return m_bodies.size();
}

void BodyManager::setTraceMode(bool isAllowed)
{

}

bool BodyManager::updateComboBox(QComboBox *box, const QString * const name)
{
    if(*name != "")
    {
        if(box->findText(*name) == -1)
        {
            box->addItem(*name);
        }
        else
        {
            int i;
            for(i = 1; box->findText(*name + QString::number(i)) != -1; i++){}
            auto&& newName = *name + QString::number(i);
            m_bodies.back()->set_name(newName);
            box->addItem(newName);
        }
        return true;
    }
    else
    {
        m_bodies.pop_back();
        return false;
    }
}

BodyManager::~BodyManager()
{
    for(auto&& a : m_bodies)
        delete a;
}


