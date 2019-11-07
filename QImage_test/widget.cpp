#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPicture>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //QImage
    //创建绘图设备 QImage::Format_ARGB32背景是透明
    QImage image(400,300,QImage::Format_ARGB32);
    QPainter p(&image);
    p.drawImage(0,0,QImage("://image/gameover.gif"));


    //对绘图设备前50个像素点进行操作
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<50;j++)
        {
            image.setPixel(QPoint(i,j),qRgb(0,255,0));
            //image.pixel(QPoint(i,j));//获取像素点
        }
    }
    //保存图片
    image.save("../image.png");

    //QPicture
    QPicture picture;  //创建画图设备
    QPainter painter;
    painter.begin(&picture);

    painter.drawPixmap(0,0,80,80,QPixmap("://image/gameover.gif"));
    painter.drawLine(50,50,150,50);
    painter.end();

    picture.save("../picture.png");
    //保存的png文件打不开，是一个二进制文件，通过paintevent函数把图片加载到窗口


}

Widget::~Widget()
{
    delete ui;
}

//通过paintevent函数把图片加载到窗口
void Widget::paintEvent(QPaintEvent *event)
{
    QPicture pic;
    pic.load("../picture.png");

    QPainter paint(this);
    paint.drawPicture(QPoint(0,0),pic);

}
