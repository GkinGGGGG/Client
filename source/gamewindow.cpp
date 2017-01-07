#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gui.h"
#include<QVector>
#include <QDesktopServices>
#include <QUrl>
#include <QPalette>
#include <QColorDialog>
#include <QMessageBox>
#include<QEvent>
#include<QKeyEvent>
#include"warning.h"
#include<QFileDialog>
#include<QDragEnterEvent>
#include<QFile>
#include<QTextStream>
#include<QMimeData>
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{

    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    color=Qt::red;
    ui->textEdit->setTextColor(Qt::red);
    ui->statusBar->showMessage(tr("欢迎加入游戏！"),10000);
    ui->statusBar->addPermanentWidget(preparation);
    ui->textEdit_2->setTextColor(Qt::red);
    label[0]=ui->label_1;
    label[1]=ui->label_2;
    label[2]=ui->label_3;
    label[3]=ui->label_4;
    label[4]=ui->label_5;
    label[5]=ui->label_6;
    label[6]=ui->label_7;
    label[7]=ui->label_8;
    label[8]=ui->label_9;
    label[9]=ui->label_10;
    label[10]=ui->label_11;
    label[11]=ui->label_12;
    pushbutton[0]=ui->pushButton_1;
    pushbutton[1]=ui->pushButton_2;
    pushbutton[2]=ui->pushButton_3;
    pushbutton[3]=ui->pushButton_4;
    pushbutton[4]=ui->pushButton_5;
    pushbutton[5]=ui->pushButton_6;
    pushbutton[6]=ui->pushButton_7;
    pushbutton[7]=ui->pushButton_8;
    pushbutton[8]=ui->pushButton_9;
    pushbutton[9]=ui->pushButton_10;
    pushbutton[10]=ui->pushButton_11;
    pushbutton[11]=ui->pushButton_12;
    frame[0]=ui->frame_1;
    frame[1]=ui->frame_2;
    frame[2]=ui->frame_3;
    frame[3]=ui->frame_4;
    frame[4]=ui->frame_5;
    frame[5]=ui->frame_6;
    frame[6]=ui->frame_7;
    frame[7]=ui->frame_8;
    frame[8]=ui->frame_9;
    frame[9]=ui->frame_10;
    frame[10]=ui->frame_11;
    frame[11]=ui->frame_12;
    //   QSound::play ("../source/01.wav");
    bgm=new QSound("../source/01.wav",this);
    bgm->setLoops(-1);
    bgm->play();
    for(int i=0;i<=11;i++)
    {
        label[i]->setVisible(false);
        pushbutton[i]->setVisible(false);
        live[i]=false;
    }
    ui->pushButton_20->setVisible(false);
    ui->pushButton_23->setVisible(false);
    ui->pushButton_24->setVisible(false);
    ui->pushButton_19->setVisible(false);
    ui->textEdit->installEventFilter(this);
    connect(ui->actionChakan,&QAction::triggered,this,&GameWindow::on_actionChakan_triggered);
    connect(ui->actionQingchu,&QAction::triggered,ui->textEdit_2,&QTextEdit::clear);
    connect(ui->actionSousuo,&QAction::triggered,this,&GameWindow::searchfor);
    connect(ui->actionChangecolor,&QAction::triggered,this,&GameWindow::setcolor);
    connect(ui->pushButton,&QPushButton::clicked,this,&GameWindow::on_pushButton_clicked);
    connect(ui->pushButton_13,&QPushButton::clicked,this,&GameWindow::on_pushButton_13_clicked);
    connect(ui->pushButton_15,&QPushButton::clicked,this,&GameWindow::on_pushButton_15_clicked);
    connect(ui->pushButton_17,&QPushButton::clicked,this,&GameWindow::endturn);
    connect(ui->pushButton_23,&QPushButton::clicked,this,&GameWindow::chooseyes);
    connect(ui->pushButton_24,&QPushButton::clicked,this,&GameWindow::chooseno);
    connect(ui->pushButton_20,&QPushButton::clicked,this,&GameWindow::exploded);
    connect(ui->pushButton_14,&QPushButton::clicked,this,&GameWindow::on_actionJilu_triggered);
    connect(ui->pushButton_22,&QPushButton::clicked,this,&GameWindow::setcolor);
    connect(ui->pushButton_21,&QPushButton::clicked,this,&GameWindow::searchfor);
    connect(&s,&search::findfor,this,&GameWindow::show_text);
    QSignalMapper *mapper=new QSignalMapper(this);
    for(int i=0;i<=11;i++)
    {
        connect(pushbutton[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(pushbutton[i],i+1);
    }
    connect(ui->pushButton_19,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->pushButton_19,0);
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(choice(int)));
    color0=QColor( 0, 85, 255);
    ui->textEdit->setAcceptDrops(false);
    setAcceptDrops(true);
    /*QPalette editpalette=ui->textEdit_2->palette();
    editpalette.setColor(QPalette::HighlightedText,Qt::yellow);
    editpalette.setColor(QPalette::HighlightedText,Qt::white);
    ui->textEdit_2->setPalette(editpalette);*/
}


void GameWindow::show_text(QString findtext)
{
    /*QTextCursor cursor=this->ui->textEdit_2->textCursor();
    cursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
    ui->textEdit_2->append(findtext);*/
    if(ui->textEdit_2->find(findtext))
        {
            QPalette palette = ui->textEdit->palette();
            palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
            ui->textEdit_2->setPalette(palette);
        }
        else
        {
            QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
            s.hide();
        }
}

bool GameWindow::eventFilter(QObject *obj, QEvent *e)
{
    Q_ASSERT(obj == ui->textEdit);
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        if (event->key() == Qt::Key_Return)
        {
            on_pushButton_clicked();
            return true;
        }
    }
    return false;
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setcolor()
{
    color=QColorDialog::getColor(Qt::red,this,tr("文字颜色"));
    ui->textEdit->setTextColor(color);
    ui->textEdit_2->setTextColor(color);
}

void GameWindow::myplayer(int seat,int id)
{
    myseat=seat;
    identity=id;
    ui->label_13->setText(tr("ID:%1").arg(identity));
    ui->label_14->setText(tr("%1号").arg(seat+1));
    frame[seat]->setStyleSheet("background-color: rgb(0, 85, 255)");

}

void GameWindow::flush(QVector<QPair<int, int> > vect, int prepared,int sum)
{
    QVector<QPair<int,int>>::iterator i;
    for(int j=0;j<=11;j++)
    {
        label[j]->setVisible(false);
        pushbutton[j]->setVisible(false);
    }
    for(i=vect.begin();i!=vect.end();i++){
    addplayer(i->first,i->second);}
    showprepared(prepared,sum);
}

void GameWindow::addplayer(int seat,int id)
{
    label[seat]->setVisible(true);
    pushbutton[seat]->setVisible(true);
    label[seat]->setText(tr("%1号 ID:%2").arg(seat+1).arg(id));
    live[seat]=true;
}

void GameWindow::on_actionChakan_triggered()
{
    QDesktopServices::openUrl(QUrl("http://baike.baidu.com/link?url=NIp1tudVwrioy0g3GF4QEles_ctV6TEpD_-sQ21huAlzyu7m-g4l1WrnQzhSovRjZpaJ1Zf3hMsrjejzpOESFludN9CZfCfA2F4PPDvXEdYTww_NCJP6unzDD6DiNGGd"));
}

void GameWindow::exploded()
{
    emit explode();
}
void GameWindow::explodepermitted(bool p)
{
    if(p==true)
        ui->pushButton_20->setEnabled(false);
    else
        emit warning();
}

void GameWindow::on_pushButton_clicked()
{
    QString str=ui->textEdit->toPlainText();
    emit speak(str);
    ui->textEdit->clear();
}

void GameWindow::on_pushButton_13_clicked()
{
    if(ui->pushButton_13->text()==tr("准备"))
    {
        emit prepared();
        ui->pushButton_13->setText("取消准备");
        ui->pushButton_15->setVisible(false);

    }
    else
    {
        emit unprepared();
        ui->pushButton_13->setText("准备");
        ui->pushButton_15->setVisible(true);
    }
}


void GameWindow::on_pushButton_15_clicked()
{
    emit goback();

}
void GameWindow::back(bool permission)
{
    if(permission==true)
        close();
    else
        emit warning();
}

void GameWindow::start(int role)
{
    ui->pushButton_13->setVisible(false);
    ui->pushButton_15->setVisible(false);
    ui->pushButton_19->setVisible(true);
    ui->pushButton_22->setVisible(false);

    if(role==5)
    {
        ui->pushButton_19->setText(tr("弃票"));
        ui->label_15->setText(tr("平民"));
        ui->label_16->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/icon/farmer.ico")));
    }
    else if(role==3)

    {
        ui->pushButton_19->setText(tr("弃票"));
        ui->label_15->setText(tr("预言家"));
        ui->label_16->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/icon/crystal_ball.ico")));
    }
    else if(role==2)
    {
        ui->pushButton_19->setText(tr("不毒/弃票"));
        ui->label_15->setText(tr("女巫"));
        ui->label_16->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/icon/witch.ico")));
    }
    else if(role==4)
    {
        ui->pushButton_19->setText(tr("空枪/弃票"));
        ui->label_15->setText(tr("猎人"));
        ui->label_16->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/icon/gun.ico")));
    }
    else
    {
        ui->pushButton_19->setText(tr("弃票"));
        ui->pushButton_20->setVisible(true);
        ui->label_15->setText(tr("狼人"));
        ui->label_16->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/icon/myico.ico")));
    }
     ui->pushButton_19->setEnabled(false);
}

void GameWindow::getmessage(int seat,QString str)
{

    if(seat!=-1)
        ui->textEdit_2->append(tr("%1号玩家：").arg(seat+1));
    else
        ui->textEdit_2->setTextColor(color0);
    ui->textEdit_2->append(str);
    ui->textEdit_2->setTextColor(color);
}

void GameWindow::myturn()
{
    ui->textEdit->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_17->setEnabled(true);
    ui->textEdit_2->setTextColor(color0);
    ui->textEdit_2->append(tr("轮到你了："));
    ui->textEdit_2->setTextColor(color0);
}

void GameWindow::endturn()
{
    ui->textEdit->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_17->setEnabled(false);
    ui->textEdit_2->append(tr("发言结束。"));
    emit end();
}

void GameWindow::choice(int seat)
{
    for(int i=0;i<=11;i++){
        pushbutton[i]->setEnabled(false);
        live[i]=false;
    }
    ui->textEdit->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_19->setEnabled(false);
    e.exit(seat);
}

void GameWindow::chooseyes()
{
    ui->pushButton_23->setVisible(false);
    ui->pushButton_24->setVisible(false);
    e.exit(true);
}

void GameWindow::chooseno()
{
    ui->pushButton_23->setVisible(false);
    ui->pushButton_24->setVisible(false);
    e.exit(false);
}

bool GameWindow::officercandidate()
{
   ui->pushButton_23->setVisible(true);
   ui->pushButton_24->setVisible(true);
   return e.exec();
}


int GameWindow::vote(QVector<int> player, bool c)
{
    if(c==true)
        ui->pushButton_19->setEnabled(true);
    QVector<int>::iterator i;
    for(i=player.begin();i!=player.end();i++)
    {
        pushbutton[*i]->setEnabled(true);
        live[*i]=true;
    }
    return e.exec()-1;
}

void GameWindow::showprepared(int prepared, int sum)
{
    preparation->setText(tr("已有%1/%2人准备了").arg(prepared).arg(sum));
    for(int i=sum;i<=11;i++)
    {
        frame[i]->setStyleSheet("background-color: rgb(90, 90, 90);");
    }
}

void GameWindow::searchfor()
{
    s.show();
}

void GameWindow::gameover()
{
    ui->pushButton_15->setVisible(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_17->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->pushButton_20->setVisible(false);
    ui->pushButton_14->setVisible(false);
    if(e.isRunning())
        e.exit(0);
}
void GameWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText()=="")
        ui->textEdit->setTextColor(color);

}

void GameWindow::on_stop_clicked()
{
    bgm->stop();
    ui->stop->setVisible(false);
}

void GameWindow::on_continue_2_clicked()
{
    bgm->play();
    ui->stop->setVisible(true);
}

void GameWindow::on_pushButton_16_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),".",tr("文本文件(*txt)"));
        if(fileName.isEmpty())
        {
            QMessageBox::information(this,tr("错误信息"),("请输入文件名！"));
            return;
        }
        QFile *file=new QFile;
        file->setFileName(fileName+".txt");
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit_2->toPlainText();
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this,"Error Messaage","File Save Error"+file->errorString());
            return;
        }
}

void GameWindow::on_actionJilu_triggered()
{


    QString path = QFileDialog::getOpenFileName(this,tr("查看记录"),".","Text Files(*.txt)");
            if(!path.isEmpty()) {
                QFile file(path);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QMessageBox::warning(this, tr("Read File"),tr("不能打开文件:\n%1").arg(path));
                    return;
                }
                QTextStream in(&file);
                    ui->textEdit_2->setTextColor(Qt::yellow);
                    ui->textEdit_2->append(in.readAll());
                    ui->textEdit_2->setTextColor(color);

                file.close();
            } else {
                QMessageBox::warning(this, tr("路径"),tr("未选取文件！"));
            }

}

void GameWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else event->ignore();
}

void GameWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimedata=event->mimeData();
    if(mimedata->hasUrls())
    {
        QList<QUrl> urlList=mimedata->urls();
        QString fileName=urlList.at(0).toLocalFile();
        if(! fileName.isEmpty())
        {
            QFile file(fileName);
            if(! file.open(QIODevice::ReadOnly)) return;

            QTextStream in(&file);
            ui->textEdit_2->setTextColor(Qt::yellow);
            ui->textEdit_2->append(in.readAll());
            ui->textEdit_2->setTextColor(color0);
        }
    }
}
