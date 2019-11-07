#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);


    tcpSocket=NULL;
    tcpSocket=new QTcpSocket(this);

    setWindowTitle(QString("客户端  "));
    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
    {
        ui->textEditread->setText("成功和服务器建立连接");
    });
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
    {
        //获取对方发送的内容
        QByteArray array=tcpSocket->readAll();
        ui->textEditread->append(array);
    });

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    QString ip=ui->ip->text();
    qint16 port=ui->port->text().toInt();
    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_buttonsend_clicked()
{
    //获取编辑框内容
    QString str=ui->textEditwrite->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());

}

void ClientWidget::on_buttonclose_clicked()
{
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
