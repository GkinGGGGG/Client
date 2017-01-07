#include "gui.h"
#include "createroom.h"
#include "hall.h"
#include "warning.h"
#include "login.h"
#include <QtCore>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>

gui::gui(QObject *parent)
    :QObject(parent)
{
    QObject::connect(&w,&hall::createbutton_clicked,this,&gui::showcreateroom);
    QObject::connect(&c,&createroom::newroom,this,&gui::onenewroom);
    QObject::connect(&w,&hall::enterroom,this,&gui::enterroom);
    QObject::connect(&w,&hall::openlogin,this,&gui::openlogin);
    QObject::connect(&w,&hall::openweb,this,&gui::openweb);
    QObject::connect(&w,&hall::warning,this,&gui::WArning);

    QObject::connect(&g,&GameWindow::prepared,this,&gui::gprepared);
    QObject::connect(&g,&GameWindow::unprepared,this,&gui::gunprepared);
    QObject::connect(&g,&GameWindow::goback,this,&gui::ggoback);
    QObject::connect(&g,&GameWindow::end,this,&gui::gendturn);
    QObject::connect(&g,&GameWindow::explode,this,&gui::gexplode);
    QObject::connect(&g,&GameWindow::speak,this,&gui::gspeak);
    QObject::connect(&g,&GameWindow::warning,this,&gui::WArning);
}

void gui::closehall(){
    w.closehall();
}

QPair<QString,int> gui::acquireServer(){
    l.exec();
    return l.getpair();
}

void gui::showHall(){
    w.setup(l.getpair().first,QString::number(l.getpair().second,10));
    w.showhall();
}

void gui::showlogin(){
    l.showlogin();
}

void gui::showcreateroom(){
    c.showcreateroom();
}

void gui::onenewroom(const int number){
    emit Newroom(number);
    c.hidewindow();
}

void gui::warning(){
    Warning warning;
    warning.exec();
}

void gui::flushroom(QVector<QVector<int> > vect){
    removeroom();
    int i=vect.size();
    for(int j=0;j<i;j++){
        QString a=QString::number(vect[j][0],10);
        QString b=QString::number(vect[j][2],10)+"/"+QString::number(vect[j][1],10)+"人";
        w.addroom(a,b);
    }
}

void gui::removeroom(){
    w.removeall();
}

void gui::enterroom(const int id){
    emit enterRoom(id);
}

void gui::enterroomok(){
    w.hide();
    g.show();
}

void gui::openlogin(){
    w.hide();
    l.reset();
    l.show();
}

void gui::openweb(){
    QDesktopServices::openUrl(QUrl("http://baike.baidu.com/link?url=NIp1tudVwrioy0g3GF4QEles_ctV6TEpD_-sQ21huAlzyu7m-g4l1WrnQzhSovRjZpaJ1Zf3hMsrjejzpOESFludN9CZfCfA2F4PPDvXEdYTww_NCJP6unzDD6DiNGGd"));
}

void gui::hidehall(){
    w.hide();
}

void gui::WArning(){
    warning();
}


void gui::showgame()
{
    g.show();
}
void gui::back(bool permission)
{
    g.back(permission);
}
void gui::flush(QVector<QPair<int, int> > vect, int prepared,int sum)
{
    g.flush(vect,prepared,sum);
}
void gui::myplayer(int seat, int id)
{
    g.myplayer(seat,id);
}

void gui::gprepared()
{
    emit ready();
}
void gui::gunprepared()
{
    emit cancel();
}
void gui::ggoback()
{
    emit quit();
}

void gui::role(int role)
{
    g.start(role);
}
void gui::showmessage(int seat, QString str)
{
    g.getmessage(seat,str);
}
void gui::gspeak(QString str)
{
    emit speak(str);
}
void gui::myturn()
{
    g.myturn();
}
void gui::gendturn()
{
    emit endspeaking();
}

int gui::decide(QVector<int> player,bool choose0)
{
    return g.vote(player,choose0);
}

bool gui::choose()
{
    return g.officercandidate();
}

void gui::gexplode()
{
    emit explode();
}
void gui::endturn()
{
    g.endturn();
}
void gui::gameover()
{
    g.gameover();
}
void gui::explodepermitted(bool p)
{
    g.explodepermitted(p);
}
void gui::dead()
{
    g.gameover();
}
