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
    QObject::connect(&g,&GameWindow::endturn,this,&gui::gendturn);
    QObject::connect(&g,&GameWindow::explode,this,&gui::gexplode);
}

QPair<QString,int> gui::acquireServer(){
    return l.getpair();
}

void gui::showHall(){
    w.setup(l.getpair().first,QString::number(l.getpair().second,10));
    w.show();
}

void gui::showlogin(){
    l.exec();
}

void gui::showcreateroom(){
    c.exec();
}

void gui::onenewroom(const int number){
    emit Newroom(number);
    c.hide();
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

void gui::flush(QVector<QPair<int, int> > vect, int prepared)
{
    QVector<QPair<int,int>>::iterator i;
    for(i=vect.begin();i!=vect.end();i++){
    g.addplayer(i->first,i->second);}
    g.showprepared(prepared);
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

/*void gui::gameover()
{
    g.gameover();
}*/
/*int gui::wolfsturn(QVector<int> player)
{
    return g.wolfsturn(player);
}*/
int gui::decide(QVector<int> player,bool choose0)
{
    if(choose0==false)
    return g.vote(player);
    else
    return g.poison(player);
}


bool gui::choose()
{
    return g.officercandidate();
}
/*bool gui::medicine()
{
    return g.medicine();
}
int gui::poison(QVector<int> player)
{
    return g.poison(player);
}
int gui::prophet(QVector<int> player)
{
    return g.prophet(player);
}
int gui::hunter(QVector<int> player)
{
    return g.hunter(player);
}
bool gui::officerdecide()
{
    return g.officerdecide();
}*/
void gui::gexplode()
{
    emit explode();
}
void gui::endturn()
{
    g.endturn();
}
