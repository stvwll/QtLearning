#include "widget.h"
#include "ui_widget.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>

#include <QFileDialog>

#include <QBuffer>  //内存文件

#include <QDataStream>

#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    writeData();

    QByteArray array;
    QBuffer memFile(&array);  //创建内存文件  内存中的内容放入字节数组
    bool isok=memFile.open(QIODevice::WriteOnly);
    if(isok==true)
    {
        memFile.write("123");
        memFile.close();
        cout<<memFile.buffer();//输出内存中的内容 123
        cout<<"array="<<array;

    }


    QBuffer memFile_new;
    memFile_new.open(QIODevice::WriteOnly);
    QDataStream stream(&memFile_new);
    stream<<QString("测试")<<234;
    memFile_new.close();
    cout<<memFile_new.buffer();

    memFile_new.open(QIODevice::ReadOnly);
    QDataStream out;
    out.setDevice(&memFile_new);
    QString str;
    int a;
    out>>str>>a;
    memFile_new.close();
    cout<<str.toUtf8().data()<<a;


}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    QFile file;
    file.setFileName("../demo.txt");
    bool isok=file.open(QIODevice::WriteOnly);
    if(isok==true)
    {
        QTextStream stream(&file);
        //指定编码
        stream.setCodec("UTF-8");
        stream << QString("主要看气质 ") << 123;
        file.close();
    }
}


//通过点击按钮读数据
void Widget::on_readButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"open","../");
    if(path.isEmpty()==false)
    {
        QFile file;
        file.setFileName(path);
        bool isok=file.open(QIODevice::ReadOnly);
        if(isok==true)
        {
            QTextStream stream(&file);
            //指定编码
            stream.setCodec("UTF-8");

            //QString str=stream.readAll();
            //ui->textEdit->setText(str);
            QString buf;
            while(stream.atEnd()==false)
            {
                buf+=stream.readLine();
            }
            ui->textEdit->setText(buf);

            file.close();
        }
    }
}
