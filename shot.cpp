#include "shot.h"
#include <QSystemTrayIcon>
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QPixmap>
#include "img_label.h"

Shot::Shot(QWidget *parent)
    : QWidget(parent)
{
    this->system_tray = nullptr;
    this->tool_bar = nullptr;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->resize(QApplication::primaryScreen()->size());
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->is_left_press = false;
}


void Shot::register_tray(QSystemTrayIcon* tray) {
    this->system_tray = tray;
    tray->setParent(this);
    tray->show();
}

void Shot::register_tool_bar(QToolBar* tool_bar) {
    this->tool_bar = tool_bar;
    tool_bar->setParent(this);
}

void Shot::shot_screen() {
    qDebug() << __func__;
    this->show();
}

void Shot::keyPressEvent(QKeyEvent* e) {
    qDebug() << __func__;
    if(e->key() == Qt::Key_Escape) {
        this->hide();
    }
}

void Shot::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    QColor shadow_color = QColor(0, 0, 0, 100);
    painter.fillRect(0, 0, this->width(), this->height(), shadow_color);
    if(is_left_press) {
        const auto [up_x, up_y, blow_x, blow_y] = get_select_info();
        painter.setPen(Qt::blue);
        QRect rect(up_x, up_y, blow_x - up_x, blow_y - up_y);
        painter.drawRect(rect);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(rect, QColor(0, 0, 0, 0));
    }
}

void Shot::mousePressEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        is_left_press = true;
        start_point = e->pos();
        tool_bar->hide();


    }
}

void Shot::mouseReleaseEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        is_left_press = false;
        const auto [up_x, up_y, blow_x, blow_y] = get_select_info();
        tool_bar->move(blow_x - tool_bar->width(), blow_y);
        tool_bar->show();
    }
}

void Shot::mouseMoveEvent(QMouseEvent* e) {
    if(!is_left_press) return;
    end_point = e->pos();
    this->update();
}

void Shot::put_img() {
    qDebug() << __func__;

    const auto [up_x, up_y, blow_x, blow_y] = get_select_info();
    QPixmap pixmap = QApplication::primaryScreen()
            ->grabWindow(0, up_x - 1, up_y - 1, blow_x - up_x + 2, blow_y - up_y + 2);

    Img_Label* img_label = new Img_Label();
    img_label->init_menu();
    img_label->setPixmap(pixmap);
    img_label->move(up_x, up_y);
    img_label->show();

    tool_bar->hide();
    this->hide();
}

Shot::Select_Info Shot::get_select_info() {
    int up_x = std::min(start_point.x(), end_point.x());
    int up_y = std::min(start_point.y(), end_point.y());
    int blow_x = std::max(start_point.x(), end_point.x());
    int blow_y = std::max(start_point.y(), end_point.y());
    return { up_x, up_y, blow_x, blow_y };
}

Shot::~Shot() {

}
