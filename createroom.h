#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QDialog>

namespace Ui {
class createroom;
}

class createroom : public QDialog
{
    Q_OBJECT

public:

    explicit createroom(QWidget *parent = 0);

    ~createroom();

//    int getnumber();

signals:

    void newroom(const int number);

private:

    void on_pushButton_clicked();

    Ui::createroom *ui;

    int Number;
};

#endif // CREATEROOM_H
