#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPen>

#include <QBrush>  //设置填充
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
    x = 0;
}

void Widget::paintEvent(QPaintEvent *)//参数不用可以不写
{
   //QPainter p(this);//在哪画 device 当前设备this
    QPainter p; //创建画家对象
    p.begin(this);  //指定当前窗口为绘图设备
    //绘图
    //画背景图
    p.drawPixmap(0,0,width(),height(),QPixmap("://image/bk.jpg"));
    //窗口的起始坐标0,0,窗口的大小width(),height()即图片的大小  显示和窗口一样大小的图片
    //p.drawPixmap(rect(),QPixmap("://image/bk.jpg"));
    //QPixmap pixmap;
    //pixmap.load("://image/bk.jpg");
    //p.drawPixmap(0,0,pixmap);//默认画图片的大小

    //定义画笔
    QPen pen;

    pen.setWidth(5); //设置线宽
    //pen.setColor(Qt::green);
    pen.setColor(QColor(14,9,234));//通过rgb设置颜色
    pen.setStyle(Qt::DashDotLine); //设置笔的风格

    //把画笔交给画家
    p.setPen(pen);
    //创建画刷对象
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);

    //把画刷交给画家
    p.setBrush(brush);

    p.drawLine(50,50,200,50);//起始坐标，终止坐标
    p.drawLine(50,50,50,200);
    p.drawEllipse(QPoint(100,100),50,25);//画圆和椭圆  参数：圆心、水平半径、垂直半径

    p.drawPixmap(x,200,50,50,QPixmap(":/image/grass.jpg"));
    p.end();
}

void Widget::on_pushButton_clicked()
{
    x+=20;
    if(x>width())
    {
        x = 0;
    }
    //刷新窗口让窗口重绘
    update(); //间接调用paintEvent
}
