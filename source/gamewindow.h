#ifndef GameWindow_H
#define GameWindow_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include<QPair>
#include<QSignalMapper>
#include"search.h"
#include<QSound>
#include<QEventLoop>
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    void flush(QVector<QPair<int,int> >,int,int);
    void myplayer(int,int);//信息初始化：玩家本人的id与座位号
    void start(int role);//role:1：狼人 2：女巫 3：预言家 4：猎人 5：平民
    void getmessage(int seat,QString str);//0表示上帝
    void myturn();
    void endturn();//可以内部执行，但考虑到倒计时等扩展，写为公有。
    int vote(QVector<int>,bool);
    bool officercandidate();//传递警徽也用vote（），点击自己头像即为撕毁
    void back(bool);
    void showprepared(int,int);
    void explodepermitted(bool);
    ~GameWindow();
    void gameover();

signals:
    void speak(QString);//回车发送信息待实现
    void prepared();
    void unprepared();
    void warning();
    void goback();
    void explode();//自爆
    void end();//结束发言    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    QEventLoop e;
    void addplayer(int,int);
    void setcolor();
    bool eventFilter(QObject *obj, QEvent *e);
    void on_actionChakan_triggered();
    void on_pushButton_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_22_clicked();
    QLabel *preparation=new QLabel(this);
    Ui::GameWindow *ui;
    QLabel *label[12];
    QPushButton *pushbutton[12];
    QFrame *frame[12];
    int identity,myseat;
    bool live[12];
    void chooseyes();
    void chooseno();
    void exploded();
    void searchfor();
    QColor color;
    QColor color0;
    search s;
    void show_text(QString findtext);
    QSound *bgm;

private slots:
    void choice(int);
    void on_textEdit_textChanged();
    void on_stop_clicked();
    void on_continue_2_clicked();
    void on_pushButton_16_clicked();
    void on_actionJilu_triggered();
};

#endif // GameWindow_H
