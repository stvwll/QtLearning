#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>
#include <QMessageBox>
#include <QTime>
myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    //设置当前界面
    ui->stackedWidget->setCurrentWidget(ui->pageset);

    //给comboBox设置内容
    QStringList qlist;
    qlist.clear();
    qlist<<"20"<<"30"<<"60"<<"80"<<"120";
    ui->comboBox->clear();
    ui->comboBox->addItems(qlist);
    ui->comboBox->setCurrentIndex(1);//默认显示30
    //初始化数据
    //失败动画
    overMovie.setFileName(":/image/over.gif");
    ui->labelOver->setMovie(&overMovie); //给标签设置动画
    ui->labelOver->setScaledContents(true);  //让动画自动适应标签大小

    //胜利动画
    winMovie.setFileName(":/image/win.gif");
    ui->labelWin->setMovie(&winMovie); //给标签设置动画
    ui->labelWin->setScaledContents(true);  //让动画自动适应标签大小

    //结束游戏动画
    gameoverMovie.setFileName(":/image/gameover.gif");
    ui->label_3->setMovie(&gameoverMovie);
    ui->label_3->setScaledContents(true);


    //数字按钮
    connect(ui->pushButton_3,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_11,&QPushButton::clicked,this,&myWidget::dealNum);
    connect(ui->pushButton_12,&QPushButton::clicked,this,&myWidget::dealNum);

    connect(ui->pushButton_13,&QPushButton::clicked,this,&myWidget::on_pushButtonDel_clicked);
    connect(ui->pushButton_14,&QPushButton::clicked,this,&myWidget::on_pushButtonEnter_clicked);
    connect(ui->pushButton,&QPushButton::clicked,this,&myWidget::on_pushButtonStart_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&myWidget::on_pushButtonEnd_clicked);

}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::on_pushButtonStart_clicked()
{
    gameTime=ui->comboBox->currentText().toInt();//QStringList类型转换为int

    qDebug()<<"gameTime="<<gameTime<<"s";

    //切换到游戏界面
    ui->stackedWidget->setCurrentWidget(ui->pagegame);

    int num;
    //以0时0分0秒到现在的秒数为种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    while((num=qrand()%10000)<999);//产生四位的随机数，1000开始
    randStr=QString::number(num);
    qDebug()<<"randNum = "<<randStr;

    //设置进度条
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(gameTime);
    ui->progressBar->setValue(gameTime);

    gameTimerId = 0;
    //启动定时器
    gameTimerId=startTimer(1000);
    resultStr.clear();
    ui->textEdit->clear();
}

//退出游戏
void myWidget::on_pushButtonEnd_clicked()
{
    gameoverId=startTimer(3000);
    gameoverMovie.start();
    //显示静态的图片
    ui->label_4->setPixmap(QPixmap(":/image/bye.jpg"));
    ui->label_4->setScaledContents(true);

    ui->stackedWidget->setCurrentWidget(ui->page);

}
//退格按钮  <--
void myWidget::on_pushButtonDel_clicked()
{
    if(resultStr.size()==1)
    {
        resultStr.clear();
        ui->textEdit->clear();
    }
    else
    {
        resultStr.chop(1);//截断最后一位字符
        //resultStr[resultStr.size()-1='\0']
        ui->textEdit->setText(resultStr);
    }
}
//提示按钮  ENTER
void myWidget::on_pushButtonEnter_clicked()
{
    resultStr.clear();
    QString str="随机数为:" + randStr;
    ui->textEdit->setText(str);
}

//数字键处理的槽函数
void myWidget::dealNum()
{
    //获取信号接收者
    QObject * mySender=sender();
    //转换为按钮类型
    QPushButton *p=(QPushButton*)mySender;
    if(p!=NULL)
    {
        //获取按钮的内容
        QString  numStr=p->text();
        resultStr+=numStr;

        //数字不能以0开始
        if(resultStr.size()==1 && resultStr=="0")
        {
            resultStr.clear();
        }
        if(resultStr.size()<=4)//保证显示结果为4位
        {
            ui->textEdit->setText(resultStr);
            if(resultStr.size()==4)//数字到第四位时
            {
                if(resultStr>randStr)
                {
                    ui->textEdit->append("数字大了点！");
                }
                else if(resultStr<randStr)
                {
                    ui->textEdit->append("数字小了点！");
                }
                else
                {
                    ui->textEdit->append("恭喜你猜对了");

                    //停止定时器
                    killTimer(gameTimerId);
                    QMessageBox::information(this,"胜利","恭喜你猜对了");

                    //切换到成功动画
                    winMovie.start();
                    ui->stackedWidget->setCurrentWidget(ui->pagewin);
                    //启动定时器
                    winTimerId=startTimer(5000);
                }
                resultStr.clear();
            }
        }
    }
}

//定时器事件
void myWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId()==gameTimerId)
    {
        gameTime--;
        //设置进度条
        ui->progressBar->setValue(gameTime);
        if(gameTime==0)
        {
            //关闭定时器
            killTimer(gameTimerId);
            QMessageBox::warning(this,"失败","时间到了");
            overMovie.start();
            //切换失败动画页面
            ui->stackedWidget->setCurrentWidget(ui->pageover);
            overTimerId=startTimer(5000);
        }
    }
    else if(e->timerId()==overTimerId)
    {
        //停止动画，停止定时器，回到游戏设置页面
        overMovie.stop();
        killTimer(overTimerId);

        ui->stackedWidget->setCurrentWidget(ui->pageset);
    }
    else if(e->timerId()==winTimerId)
    {
        winMovie.stop();
        killTimer(winTimerId);

        ui->stackedWidget->setCurrentWidget(ui->pageset);
    }
    else if(e->timerId()==gameoverId)
    {
        gameoverMovie.stop();
        killTimer(gameoverId);
        this->close();
    }
}


