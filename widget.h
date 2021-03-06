#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void creatActions();
protected slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayIconMsgClicked();
    void showMinimized();
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
};

#endif // WIDGET_H
