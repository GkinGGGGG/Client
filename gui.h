#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include "hall.h"
#include "login.h"
#include "createroom.h"
#include "gamewindow.h"
#include<QVector>
#include<QPair>

class gui :public QObject
{
    Q_OBJECT

public:
    explicit gui(QObject *parent=0);

    void showlogin();

    QPair<QString,int> acquireServer();

    void showHall();

    void warning();

    void removeroom();

    void enterroomok();

    void hidehall();

    void flushroom(QVector<QVector<int>>);

    void showgame();//窗口出现
    void flush(QVector<QPair<int,int>>,int);//加入玩家:改为接受列表
    void myplayer(int seat, int id);//自身信息
    void role(int role);//开始游戏，告知身份
    void showmessage(int seat,QString str);//收取发言并显示
    void myturn();//开始发言

    int decide(QVector<int>,bool);//选警长和投票通用，本来这两个就没区别吧
    bool choose();
    void endturn();//自爆时强制结束对话


signals:

    void Newroom(const int number);

    void enterRoom(const int id);

    void ready();//准备
    void cancel();//取消准备
    void quit();//返回大厅
    void speak(QString);//发言
    void endspeaking();//结束发言
    void explode();//自爆

private:

    void openlogin();

    void showcreateroom();

    void onenewroom(const int number);

    void enterroom(const int id);

    void openweb();

    void WArning();

    hall w;

    login l;

    createroom c;

    GameWindow g;
    void gprepared();
    void gunprepared();
    void ggoback();

    void gspeak(QString);
    void gendturn();
    void gchoice(int);
    void gexplode();

};

#endif // GUI_H
