#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bodymanager.h"
#include <QTimer>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void updateTable(const QString& name, bool isReset);
    void deleteItem();
protected slots:
    void update();
    void refresh();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_textActivated(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    BodyManager m_bm;
    QTimer* m_timer;
    QGraphicsScene* m_scene;
    const QIcon* const CONTINUE;
    const QIcon* const STOP;
    const QIcon* const RESET;

    const int REFRESH_RATE = 17;
};
#endif // MAINWINDOW_H
