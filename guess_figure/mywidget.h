#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMovie>

#include <QString>

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();
    //自定义槽函数
    void dealNum();

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonEnd_clicked();
    void on_pushButtonDel_clicked();
    void on_pushButtonEnter_clicked();


protected:
    void timerEvent(QTimerEvent *e);

private:
    Ui::myWidget *ui;

    int gameTime;  //游戏时间
    QString randStr;  //随机数
    int gameTimerId;  //游戏时间定时器ID
    int overTimerId;  //失败动画定时器ID
    int winTimerId;  //成功动画定时器ID
    int gameoverId;  //结束动画ID
    QString resultStr;  //结果数
    QMovie overMovie;  //失败动画
    QMovie winMovie;   //胜利动画
    QMovie gameoverMovie; //结束动画
};

#endif // MYWIDGET_H
