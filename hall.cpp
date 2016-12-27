#include "hall.h"
#include "ui_hall.h"
#include <QLabel>
#include <QDialog>
#include "warning.h"
#include "ui_warning.h"
#include "login.h"
#include <QObject>
#include <QPalette>

hall::hall(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hall)
{
    ui->setupUi(this);

    QLabel *permanent=new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("欢迎来到游戏大厅");
    ui->statusBar->addPermanentWidget(permanent);

    QObject::connect(ui->roomtableWidget,&QTableWidget::itemDoubleClicked,this,&hall::getitem);

    ui->notepad->setWidget(ui->textEdit);
    ui->notepad->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);

    QPalette pl=ui->notepad->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(10,10,40,250)));
    ui->notepad->setPalette(pl);

    QPalette pll=ui->roomtableWidget->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(0,0,0,200)));
    ui->roomtableWidget->setPalette(pll);

    ui->roomtableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:deepblue;color: white ;padding-left: 4px;border: 0px solid #6c6c6c;}");
    ui->roomtableWidget->horizontalHeader()->setFixedHeight(30);

    ui->pushButton->setStyleSheet("QPushButton{color: rgb(222, 222, 222);font: 75 14pt;border-color: rgba(15, 15, 80,130);background-color: rgba(20, 15, 135,130);border-width: 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color: rgba(25,20,140,180);border-color: rgba(17,18,85,180);}"
                                  "QPushButton:pressed{border-style: inset;font: 75 14pt;  background-color: rgba(25,20,140,180);border-color: rgba(17,18,85,180);}");
    ui->createButton->setStyleSheet("QPushButton{color: rgb(222, 222, 222);font: 75 14pt;border-color: rgba(90, 12, 13,130);background-color: rgba(150, 25, 40,130);border-width: 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color: rgba(155,30,45,180);border-color: rgba(95,15,15,180);}"
                                    "QPushButton:pressed{border-style: inset;font: 75 14pt;  background-color: rgba(155,30,45,180);border-color: rgba(95,15,15,180);}");

    ui->textEdit->setTextColor(QColor(255,255,255,200));

    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);

    this->setFixedSize(this->width(), this->height());

    ui->ip->setAlignment(Qt::AlignCenter);
    ui->port->setAlignment(Qt::AlignCenter);

}

void hall::addroom(QString ip,QString number){
    QTableWidgetItem*name=new QTableWidgetItem(ip);
    QTableWidgetItem*num=new QTableWidgetItem(number);

    name->setTextAlignment(Qt::AlignCenter);
    num->setTextAlignment(Qt::AlignCenter);

    ui->roomtableWidget->insertRow(0);
    ui->roomtableWidget->setItem(0,0,name);
    ui->roomtableWidget->setItem(0,1,num);
}

void hall::removeroom(QString ip){
    int rowNum = ui->roomtableWidget->findItems(ip,Qt::MatchExactly).first()->row();
    ui->roomtableWidget->removeRow(rowNum);
}

void hall::removeall(){
    ui->roomtableWidget->setRowCount(0);
}

hall::~hall()
{
    delete ui;
}

void hall::on_action_Q_triggered()
{
    close();
}

void hall::on_action_J_triggered()
{
    ui->notepad->show();
}

void hall::on_action_triggered()
{
    emit openlogin();

}

void hall::setup(QString a, QString b){
    ui->port->setText(b);
    ui->ip->setText(a);
}

void hall::on_createButton_clicked()
{
    emit createbutton_clicked();
}

void hall::on_action_2_triggered()
{
    emit openweb();
}

void hall::getitem(QTableWidgetItem *item){

    int row=item->row();
    QString ip=ui->roomtableWidget->item(row,0)->text();
    int id = ip.toInt();
    emit enterroom(id);
}

void hall::on_pushButton_clicked()
{
    int row=ui->roomtableWidget->rowCount();
    if(row==0){
        emit warning();
    }
    else{
    QString ip=ui->roomtableWidget->item(row-1,0)->text();
    int id = ip.toInt();
    emit enterroom(id);}
}
