#ifndef HALL_H
#define HALL_H

#include <QMainWindow>
#include <QString>
#include <QApplication>
#include <QTableWidgetItem>

namespace Ui {
class hall;
}

class hall : public QMainWindow
{
    Q_OBJECT

public:
    explicit hall(QWidget *parent = 0);

    ~hall();

    void addroom(QString, QString);

    void removeroom(QString);

    void setup(QString, QString);

    void removeall();

signals:

    void createbutton_clicked();

    void enterroom(const int id);

    void openlogin();

    void openweb();

    void warning();

private:
    void on_action_Q_triggered();

    void on_action_J_triggered();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_createButton_clicked();

    void getitem(QTableWidgetItem*item);

    void on_pushButton_clicked();

    Ui::hall *ui;
};

#endif // HALL_H
