#include "createroom.h"
#include "ui_createroom.h"
#include <QPalette>

createroom::createroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createroom)
{
    ui->setupUi(this);

    QPalette pll=ui->number->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(10,10,40,200)));
    ui->number->setPalette(pll);

    ui->pushButton->setStyleSheet("QPushButton{color: rgb(222, 222, 222);font: 75 14pt;border-color: rgb(35, 35, 100);background-color: rgb(40, 40, 110);border-width: 3px;border-style: outset;}"
                                "QPushButton:hover{background-color: rgb(45,45,120);border-color: rgb(40,40,110);}"
                                "QPushButton:pressed{font: 75 14pt;border-style: inset;background-color: rgb(45,45,120);border-color: rgb(40,40,110);}");

    ui->pushButton_2->setStyleSheet("QPushButton{color: rgb(222, 222, 222);font: 75 14pt;border-color: rgb(35, 35, 100);background-color: rgb(40, 40, 110);border-width: 3px;border-style: outset;}"
                                    "QPushButton:hover{background-color: rgb(45,45,120);border-color: rgb(40,40,110);}"
                                    "QPushButton:pressed{font: 75 14pt;border-style: inset;background-color: rgb(45,45,120);border-color: rgb(40,40,110);}");

    this->setFixedSize(this->width(), this->height());

    ui->label_2->setAlignment(Qt::AlignCenter);

}

createroom::~createroom()
{
    delete ui;
}


void createroom::on_pushButton_clicked()
{
    Number=ui->number->text().toInt();

    if(ui->number->text().size()==0)
        ui->label_4->setText("房间人数不能为空");

    if((ui->number->text().size()!=0)){
    emit newroom(Number);
}
}

/*int createroom::getnumber(){
    return Number;
}*/
