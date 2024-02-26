#include "bodycreationdialog.h"
BodyCreationDialog::BodyCreationDialog(QWidget* parent) : QDialog(parent)
{
    m_edits.resize(LABELS.size());
    m_labels.resize(LABELS.size() + 1);

    m_layout = new QFormLayout(this);

    m_labels[0] = new QLabel(this);
    m_colorButton = new QPushButton("Select a color");
    connect(m_colorButton, &QAbstractButton::clicked, this, &BodyCreationDialog::setColor);
    m_layout->addRow(m_labels[0], m_colorButton);

    for (int i = 0; i < LABELS.size(); ++i)
    {
        m_edits[i] = new QLineEdit(this);
        m_labels[i + 1] = new QLabel(QString(LABELS[i]), this);
        m_layout->addRow(m_labels[i+1], m_edits[i]);
    }

    for(int i = 1; i < m_edits.size(); ++i)
    {
        //m_edits[i-1]->connect(m_edits[i-1]->returnPressed, m_edits[i]->setFocus);
    }

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    m_layout->addWidget(m_buttonBox);

    bool isConnected = connect(m_buttonBox, &QDialogButtonBox::accepted, this, &BodyCreationDialog::accept);
    Q_ASSERT(isConnected);
    isConnected = connect(m_buttonBox, &QDialogButtonBox::rejected, this, &BodyCreationDialog::reject);
    Q_ASSERT(isConnected);

    setLayout(m_layout);
}

Body* BodyCreationDialog::getBody(QWidget *parent, bool *ok)
{
    BodyCreationDialog *dialog = new BodyCreationDialog(parent);

    std::vector<qreal> data(LABELS.size() - 1);

    if (dialog->exec() == QDialog::Accepted)
    {
        for(int i = 0; i < LABELS.size() - 1; ++i)
            data[i] = dialog->m_edits[i + 1]->text().toDouble();

        dialog->deleteLater();

        return new Body(dialog->m_color, dialog->m_edits[0]->text(), data[0], data[1], {data[2], data[3]}, {data[4], data[5]}, {data[6], data[7]});
    }
    return new Body(Qt::white, "", 0, 0, {0, 0}, {0, 0}, {0, 0});
}

bool BodyCreationDialog::eventFilter(QObject *object, QEvent *event)
{
    ////////////////////////// not working
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            qDebug() << "eventFilter Enter pressed-1";
            for(int i = 0; i < m_edits.size(); ++i)
                if(m_edits[i]->hasFocus())
                    m_edits[i]->setFocus();
            return true;
        }
    }
    return false;
}

BodyCreationDialog::~BodyCreationDialog()
{
    for(auto&& a : m_edits)
        delete a;
    for(auto&& a : m_labels)
        delete a;

    delete m_layout;
    delete m_colorButton;
    delete m_buttonBox;
}

void BodyCreationDialog::setColor()
{
    m_color = QColorDialog::getColor(Qt::green, this, "Select Color");
    m_labels[0]->setPalette(QPalette(m_color));
    m_labels[0]->setAutoFillBackground(true);
}
