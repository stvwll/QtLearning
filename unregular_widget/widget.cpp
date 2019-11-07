#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QMouseEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //ba把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap("://image/bk.jpg"));
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)//注：这里用的是buttons,下面鼠标被按下的事件中用的是button
    {
        move(event->globalPos()-p);
    }
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton) //鼠标右键被按下，则关闭窗口
    {
        close();
    }
    else if(event->button()==Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p=event->globalPos()-this->frameGeometry().topLeft();
    }
}

