#include "img_label.h"

#include <QMouseEvent>
#include <QMenu>
#include <QWheelEvent>

Img_Label::Img_Label(QWidget* parent) : QLabel(parent) {
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setCursor(Qt::SizeAllCursor);

    this->is_left_press = false;
    this->menu = nullptr;
}

void Img_Label::init_menu() {
    this->menu = new QMenu(this);
    auto close_actoin = menu->addAction("close");
    connect(close_actoin, &QAction::triggered, this, &Img_Label::close);
}

void Img_Label::mousePressEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        is_left_press = true;
        last_pos = e->globalPosition();
    } else if(e->button() == Qt::RightButton) {
        if(menu != nullptr) {
            auto pos = e->globalPosition();
            menu->move(pos.x(), pos.y());
            menu->show();
        }
    }
}

void Img_Label::mouseReleaseEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        is_left_press = false;
    } else if(e->button() == Qt::RightButton) {
        if(menu != nullptr) {
            menu->hide();
        }
    }
}

void Img_Label::mouseMoveEvent(QMouseEvent* e) {
    if(is_left_press) {
        auto pos = e->globalPosition();
        if(pos != last_pos) {
            int x = this->x();
            int y = this->y();
            int offset_x = pos.x() - last_pos.x();
            int offset_y = pos.y() - last_pos.y();
            x += offset_x;
            y += offset_y;
            this->move(x, y);
            last_pos = pos;
            // qDebug() << x << ' ' << y;
        }
    }
}

//void Img_Label::wheelEvent(QWheelEvent* e) {
//    auto angle = e->angleDelta();

//    if(!angle.isNull()) {
//        int step = angle.y() / 8;

//        int w = this->width();
//        int h = this->height();

//        int h_new = h + step * (h / (1.0 * w + h));
//        auto pixmap = this->pixmap()
//                .scaled(w, h_new, Qt::KeepAspectRatio);
//        int w_new = pixmap.width();

//        this->setPixmap(pixmap);
//        this->resize(w_new, h_new);
//    }
//}
