#include "widget.h"
#include "ui_widget.h"
#include <QDataStream> //二进制文件的读写操作


#include <QFile>

#include <QDebug>

#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
//显示当前在哪个文件中第几行

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    writeData();

    readData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    //创建文件对象
    QFile file("../test.txt");
    bool isok=file.open(QIODevice::WriteOnly);
    if(isok==true)
    {
        //创建数据流 和file文件关联
        //往数据流中输入数据，相当于向文件中写数据
        QDataStream stream(&file);
        QString str="写数据::";
        stream<<str<<123;
        file.close();
    }
}

void Widget::readData()
{
    QFile file("../test.txt");
    bool isok=file.open(QIODevice::ReadOnly);
    if(isok==true)
    {
        QDataStream stream(&file);
        //读的时候，按照写的顺序取数据
        QString str;
        int a;
        stream>>str>>a;
        cout<<str.toUtf8().data()<<a;
        file.close();
    }
}
