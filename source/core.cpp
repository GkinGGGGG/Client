#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    connectToServer();
    connect(&G,&gui::Newroom,this,&Core::Newroom);
    connect(&G,&gui::enterRoom,this,&Core::enterRoom);
    connect(&G,&gui::ready,this,&Core::ready);
    connect(&G,&gui::endspeaking,this,&Core::endspeaking);
    connect(&G,&gui::cancel,this,&Core::cancel);
    connect(&G,&gui::quit,this,&Core::quit);
    connect(&G,&gui::speak,this,&Core::speak);
    connect(&G,&gui::explode,this,&Core::explode);
}
void Core::connectToServer(){
    QPair<QString,int> server=G.acquireServer();
    if(server.second<=0){
        QApplication::exit();
    }
    else{
        socket=new TcpSock(0,server.first,server.second);
        connect(socket,&TcpSock::emitMessage,this,&Core::handleMessage);
        pos=HALL;
        G.showHall();
        thread=new QThread();
        socket->moveToThread(thread);
        thread->start();
        connect(socket,&TcpSock::destroyed,thread,&QThread::quit);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);
        connect(thread,&QThread::destroyed,this,&Core::onNetworkError);

    }
}
void Core::sendEmptyMessage(int t, int st, int rt, int ri){
    Message *msg=new Message(t,st,rt,ri,1,id);
    QCoreApplication::postEvent(socket,msg);
}
void Core::onNetworkError(){
    G.back(true);
    G.hidehall();
    G.warning();
    pos=LOGIN;
    connectToServer();
}
void Core::handleMessage(Message msg){
    if(msg.getType()==0){
        switch(msg.getSubtype()){
        case 2:
            if(msg.getArgument().isEmpty())
                return;
            flushRoom(msg.getArgument());
            break;
        case 3:
            if(msg.getArgument().isEmpty())
                return;
            id=msg.getArgument()[0];
            qDebug()<<"id:"<<id;
            break;
        }
    }
    else if(msg.getType()==1){
        G.showmessage(-1,msg.getDetail());
        switch(msg.getSubtype()){
        case 1:
            if(msg.getArgument().isEmpty())
                return;
            G.role(msg.getArgument()[0]);
            break;
        case 2:
        case 3:
        case 10:
            break;
        case 4:
        case 5:
        case 12:
            G.myturn();
            break;
        case 17:
            G.dead();
            break;
        case 19:
            if(msg.getArgument().isEmpty())
                return;
            if(msg.getArgument()[0])
                G.endturn();
            else
                G.showmessage(-1,"Self-explode failed!");
            break;
        default:
            genFeedback(msg);
        }
    }
    else if(msg.getType()==2){
        switch(msg.getSubtype()){
        case 0:
            if(msg.getArgument().isEmpty())
                return;
            if(msg.getArgument()[0]){
                roomid=msg.getSenderid();
                G.hidehall();
                G.showgame();
                sendEmptyMessage(2,6,2,roomid);
                pos=ROOM;
            }
            else
                G.warning();
            break;
        case 3:
            if(msg.getArgument().isEmpty())
                return;
            if(msg.getArgument()[0]){
                G.back(true);
                pos=HALL;
                G.showHall();
                sendEmptyMessage(0,2,0,0);
            }
            else
                G.warning();
            break;
        case 4:
            pos=GAME;
            break;
        case 5:
            G.gameover();
            pos=ROOM;
        case 6:
            if(msg.getArgument().isEmpty())
                return;
            flushPlayer(msg.getArgument());
            break;
        case 7:
            if(msg.getArgument().isEmpty())
                return;
            G.showmessage(msg.getArgument()[0],msg.getDetail());
            break;
        }
    }
}
void Core::genFeedback(Message msg){
    int st=msg.getSubtype();
    bool allowGiveup=false;
    if(st==7||st==8||st==14||st==18)
        allowGiveup=true;
    Message *feedback=new Message(1,msg.getSubtype(),2,roomid,1,id);
    if(st==11){
        feedback->addArgument(G.choose());
    }
    else if(st==15){
        feedback->addArgument(G.decide(msg.getArgument(),allowGiveup));
        feedback->addArgument(G.choose());
    }
    else{
        int ret=G.decide(msg.getArgument(),allowGiveup);
        feedback->addArgument(ret);
    }
    QCoreApplication::postEvent(socket,feedback);
}
void Core::Newroom(const int number){
    Message *msg=new Message(0,1,0,0,1,id);
    msg->addArgument(number);
    QCoreApplication::postEvent(socket,msg);
}
void Core::enterRoom(const int id){
    sendEmptyMessage(2,0,2,id);
}
void Core::ready(){
    sendEmptyMessage(2,1,2,roomid);
}
void Core::cancel(){
    sendEmptyMessage(2,2,2,roomid);
}
void Core::quit(){
    Message *msg=new Message(2,3,2,roomid,1,id);
    msg->addArgument(0);
    QCoreApplication::postEvent(socket,msg);
}
void Core::speak(QString content){
    Message *msg=new Message(2,7,2,roomid,1,id);
    msg->setDetail(content);
    msg->addArgument(0);
    QCoreApplication::postEvent(socket,msg);
}
void Core::endspeaking(){
    Message *msg=new Message(2,7,2,roomid,1,id);
    msg->addArgument(1);
    QCoreApplication::postEvent(socket,msg);
}
void Core::explode(){
    sendEmptyMessage(1,19,2,roomid);
}
void Core::flushPlayer(QVector<int> player){
    int cap=player[0],num=player[1],ready=player[2];
    QVector<QPair<int,int> >players;
    for(int i=0;i<num;i++){
        QPair<int,int> tmp;
        tmp.first=player[i*2+3];
        tmp.second=player[i*2+4];
        players.append(tmp);
        if(tmp.second==id)
            G.myplayer(tmp.first,tmp.second);
    }
    G.flush(players,ready,cap);
}
void Core::flushRoom(QVector<int> rooms){
    int num=rooms[0];
    QVector<QVector<int>> roominfo;
    for(int i=0;i<num;i++){
        QVector<int> tmp;
        tmp.append(rooms[i*3+1]);
        tmp.append(rooms[i*3+2]);
        tmp.append(rooms[i*3+3]);
        roominfo.append(tmp);
    }
    G.flushroom(roominfo);
}
