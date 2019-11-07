#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonRead_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"open","../");
    //可以设置打开的文件格式"TXT(*.txt)"
    if(path.isEmpty()==false)
    {
        //文件对象
        QFile file(path);
        //打开文件
        bool isok=file.open(QIODevice::ReadOnly);
        if(isok==true)
        {
            #if 0
            //读文件  默认只识别utf8编码
            //一次性读完
            QByteArray array=file.readAll();
            ui->textEdit->setText(QString(array));
            #endif

            QByteArray array;
            while(file.atEnd()==false)
            {
                //读一行
                array+=file.readLine();
            }
            ui->textEdit->setText(array);

        }
        //关闭文件
        file.close();

        //获取文件信息
        QFileInfo info(path);
        qDebug()<<"文件名字:"<<info.fileName();
        qDebug()<<"文件的后缀:"<<info.suffix();//文件的后缀
        qDebug()<<"文件的大小:"<<info.size();
        qDebug()<<"文件创建时间"<<info.created().toString("yyyy-MM-dd hh:mm:ss");
        //2019-11-02 03:39:45
    }
}

void Widget::on_buttonWrite_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,"save","../");
    //,"TXT(*.txt)"
    if(path.isEmpty()==false)
    {
        QFile file;
        //关联文件名字
        file.setFileName(path);
        //打开文件，只写方式
        bool isok=file.open(QIODevice::WriteOnly);
        if(isok==true)
        {
            QString str=ui->textEdit->toPlainText();//获取编辑框内的内容
            //写文件
            //把QString->QByteArray
            //file.write(str.toUtf8());

            //QString->QByteArray->char *
            //str.toUtf8().data();

            //char * ->QString   char *buf="123";QString str=QString(buf);


            //file.write(str.toLocal8Bit());//转化为本地默认的编码格式

            //QString->string->char *
            file.write(str.toStdString().data());
        }
        file.close();
    }
}
