#ifndef BODYCREATIONDIALOG_H
#define BODYCREATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include "body.h"

const int EDITS = 9;
const std::vector<QString> LABELS = {"Name", "Radius", "Mass", "Position X", "Position Y", "Velocity X", "Velocity Y", "Acceleration X", "Acceleration Y"};

class BodyCreationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BodyCreationDialog(QWidget* parent = nullptr);
    Body* getBody(QWidget* parent, bool* ok = nullptr);
    bool eventFilter(QObject* object, QEvent* event) override;
    ~BodyCreationDialog();
protected:
    void setColor();
private:
    std::vector<QLineEdit*> m_edits;
    std::vector<QLabel*> m_labels;
    QColor m_color;
    QFormLayout* m_layout;
    QPushButton* m_colorButton;
    QDialogButtonBox* m_buttonBox;
};
#endif // BODYCREATIONDIALOG_H
