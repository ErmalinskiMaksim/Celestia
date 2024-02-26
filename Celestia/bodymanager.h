#ifndef BODYMANAGER_H
#define BODYMANAGER_H
#include "bodycreationdialog.h"
#include <QComboBox>
#include "movementalgorithm.h"

class BodyManager
{
public:
    BodyManager();
    ~BodyManager();

    // creates a body through the BodyCreationDialog and updates the combobox
    bool createBody(QComboBox* box);

    // creates a random body without a dialog and updates the combobox
    bool randomCreate(QComboBox* box);

    // deletes a body with a given name
    void deleteBody(const QString&& name);

    // updates bodies upon a movement algorithm
    void updateBodies();

    // getters
    Body* const getItem(const QString& name) const;
    Body* const getLast() const;
    bool isEmpty() const;
    const std::size_t getAmount() const;

    // setters
    void setTraceMode(bool isAllowed);

private:
    // updates the combobox
    bool updateComboBox(QComboBox* box, const QString* const name);

private:
    // provides an ability to create bodies
    BodyCreationDialog m_dialog;
    // all bodies in the simulation
    std::vector<Body*> m_bodies;
};

#endif // BODYMANAGER_H
