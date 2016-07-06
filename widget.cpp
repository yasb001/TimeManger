#include "widget.h"
#include "ui_widget.h"
#include <QSystemTrayIcon>
#include <QMenu>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    ui->setupUi(this);
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber->display(100);

    trayMenu = new QMenu("Menu", this);
    creatActions();

    // 创建托盘
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/resource/icon_128px.ico"));


    //显示系统托盘图标
    // trayIcon->show();
    // trayIcon->showMessage("TrayInfo", "this is TrayIcon");
    trayIcon->setContextMenu(trayMenu);

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
                SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(trayIconMsgClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::creatActions()
{
    QAction *actShow = new QAction(this);
    actShow->setText("显示");
    actShow->setToolTip("Show MainWindow");
    connect(actShow, SIGNAL(triggered(bool)), this, SLOT(show()));

    QAction *actQuit = new QAction("Exit", this);
    connect(actQuit, SIGNAL(triggered(bool)), this, SLOT(close()));

    QMenu *subMenu = new QMenu("abc", this);
    subMenu->addAction(actShow);
    subMenu->addAction(actQuit);

    trayMenu->addMenu(subMenu);
    trayMenu->addSeparator();
    trayMenu->addAction(actShow);
    trayMenu->addAction(actQuit);
}

void Widget::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showMaximized();
        break;
    default:
        ;
    }
}

void Widget::trayIconMsgClicked()
{
    showNormal();
}

void Widget::showMinimized()
{
    this->hide();
    trayIcon->show();
    trayIcon->showMessage("TrayInfo", "this is TrayIcon");
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    showMinimized();
}
