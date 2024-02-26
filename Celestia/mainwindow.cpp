#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), CONTINUE(new QIcon("Icons/Continue.bmp")), STOP(new QIcon("Icons/Pause.bmp")), RESET(new QIcon("Icons/Reset.bmp"))
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect({0, 0, 621, 521});

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    m_timer = new QTimer;
    m_timer->connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->connect(m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    m_timer->connect(m_timer, SIGNAL(timeout()), m_scene, SLOT(advance()));
    m_timer->start(REFRESH_RATE);


    ui->toolButton->setIcon(*STOP);
    ui->toolButton->setIconSize(QSize(25, 25));
    ui->toolButton_2->setIcon(*RESET);
    ui->toolButton_2->setIconSize(QSize(25, 25));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable(const QString& name, bool isReset)
{
    if(!m_bm.isEmpty())
    {
        const auto&& item = m_bm.getItem(name);

        if(isReset)
        {
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(*item->get_name(), QTableWidgetItem::Type));
            ui->tableWidget->setItem(1, 0, new QTableWidgetItem(QString::number(item->get_mass()), QTableWidgetItem::Type));
            ui->tableWidget->setItem(2, 0, new QTableWidgetItem(QString::number(item->get_radius()), QTableWidgetItem::Type));
            ui->tableWidget->setPalette(QPalette(QPalette::Highlight, item->get_color()));
        }

        ui->tableWidget->setItem(3, 0, new QTableWidgetItem("(" + QString::number(item->get_position().getX()) + ";" + QString::number(item->get_position().getY()) + ")", QTableWidgetItem::Type));
        ui->tableWidget->setItem(4, 0, new QTableWidgetItem("(" + QString::number(item->get_velocity().getX()) + ";" + QString::number(item->get_velocity().getY()) + ")", QTableWidgetItem::Type));
        ui->tableWidget->setItem(5, 0, new QTableWidgetItem("(" + QString::number(item->get_acceleration().getX()) + ";" + QString::number(item->get_acceleration().getY()) + ")", QTableWidgetItem::Type));
    }
    else
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setPalette(QPalette(QPalette::Highlight, Qt::white));
    }
}

void MainWindow::deleteItem()
{
    m_scene->removeItem(m_bm.getItem(ui->comboBox->currentText()));
    m_bm.deleteBody(ui->comboBox->currentText());
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
}

void MainWindow::update()
{
    updateTable(ui->comboBox->currentText(), false);
    m_bm.updateBodies();
}

void MainWindow::refresh()
{
    m_scene->setBackgroundBrush(QBrush(QColor(180,180,180)));
}


void MainWindow::on_pushButton_clicked()
{
    m_bm.createBody(ui->comboBox);
    if(!m_bm.isEmpty())
    {
        m_scene->addItem(m_bm.getLast());
        updateTable(ui->comboBox->currentText(), true);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(!m_bm.isEmpty()) deleteItem();
}

void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    updateTable(arg1, true);
}


void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    int amountOfBodies = QInputDialog::getInt(this, "Cluster editer", "The amount of planets", 2, 2, 25, 1, &ok);
    if(ok)
    {
        while(amountOfBodies--)
        {
            m_bm.randomCreate(ui->comboBox);
            m_scene->addItem(m_bm.getLast());
        }
        updateTable(ui->comboBox->currentText(), true);
    }

}

void MainWindow::on_toolButton_clicked()
{
    static bool isRunning = true;
    if(isRunning)
    {
        ui->toolButton->setIcon(*CONTINUE);
        m_timer->stop();
    }
    else
    {
        ui->toolButton->setIcon(*STOP);
        m_timer->start(REFRESH_RATE);
    }

    isRunning = !isRunning;
}


void MainWindow::on_toolButton_2_clicked()
{
    while(!m_bm.isEmpty()) deleteItem();
    updateTable("", true);
}



void MainWindow::on_checkBox_stateChanged(int arg1)
{
    Body::setTrace(ui->checkBox->isChecked());
}


