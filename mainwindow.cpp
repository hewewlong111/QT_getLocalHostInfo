#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getHostIdAndName_clicked()
{
    QString strLocalHostName=QHostInfo::localHostName();
    ui->lineEdit_hostName->setText(strLocalHostName);

    QString strLocalHostIPAddress="";
    QHostInfo hostInfo=QHostInfo::fromName(strLocalHostName);
    QList<QHostAddress> IDAdressList=hostInfo.addresses();
    if(!IDAdressList.isEmpty()){
        for(int i=0;i<IDAdressList.size();i++){
            QHostAddress hostAddress=IDAdressList.at(i);
            if(hostAddress.protocol()==QAbstractSocket::IPv4Protocol){
                strLocalHostIPAddress=hostAddress.toString();
                break;
            }
        }
        ui->lineEdit_HostID->setText(strLocalHostIPAddress);
    }
}


void MainWindow::on_getHostInfo_clicked()
{
    QString strTemp="";
    QList<QNetworkInterface> netlist=QNetworkInterface::allInterfaces();
    for(int i=0;i<netlist.size();i++){
        QNetworkInterface interfaces=netlist.at(i);
        strTemp=strTemp+"设备名称："+interfaces.name()+"\n";
        strTemp=strTemp+"硬件地址："+interfaces.hardwareAddress()+"\n";

        QList<QNetworkAddressEntry> entrylist=interfaces.addressEntries();
        for(int k=0;k<entrylist.size();k++){
            QNetworkAddressEntry entry=entrylist.at(k);
            strTemp=strTemp+"IP地址："+entry.ip().toString()+"\n";
            strTemp=strTemp+"子网掩码："+entry.netmask().toString()+"\n";
            strTemp=strTemp+"广播地址："+entry.broadcast().toString()+"\n";
        }
    }
    QMessageBox::information(this,"主机所有信息",strTemp,QMessageBox::Yes);
}









