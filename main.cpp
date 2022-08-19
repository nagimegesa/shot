#include "shot.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QToolBar>

QMenu* get_tray_menu(Shot* parent);
QToolBar* get_tool_bar(Shot* parent);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Shot w;
    QSystemTrayIcon* tray = new QSystemTrayIcon();
    tray->setIcon(QIcon(":/image/resource/tray_icon.jpg"));
    QMenu* tray_menu = get_tray_menu(&w);
    tray->setContextMenu(tray_menu);
    w.register_tray(tray);
    QToolBar* tool_bar = get_tool_bar(&w);
    w.register_tool_bar(tool_bar);
    return a.exec();
}


QMenu* get_tray_menu(Shot* parent) {
    QMenu* menu = new QMenu(parent);
    auto shot_action = menu->addAction(QString("截屏"));
    shot_action->connect(shot_action, &QAction::triggered, parent, &Shot::shot_screen);
    menu->addSeparator();
    auto close_action = menu->addAction(QString("关闭"));
    close_action->connect(close_action, &QAction::triggered, qApp, &QApplication::quit);
    return menu;
}

QToolBar* get_tool_bar(Shot* parent) {
    QToolBar* tool_bar = new QToolBar(parent);
    tool_bar->setWindowFlag(Qt::FramelessWindowHint);
    QAction* finsh_action = tool_bar->addAction("finsh");
    finsh_action->connect(finsh_action, &QAction::triggered, parent, &Shot::put_img);
    return tool_bar;
}
