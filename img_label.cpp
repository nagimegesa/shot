#include "img_label.h"

#include <QMouseEvent>
#include <QMenu>
#include <QWheelEvent>
#include <QTransform>
#include <QPainter>
#include <QImage>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>

Img_Label::Img_Label(QWidget* parent) : QLabel(parent) {
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setCursor(Qt::SizeAllCursor);
    this->is_left_press = false;
    this->menu = nullptr;
    this->angle_now = 0;
    this->setScaledContents(false);
}

void Img_Label::init_menu() {
    this->menu = new QMenu(this);
    auto save_action = menu->addAction("另存为");
    connect(save_action, &QAction::triggered, this, &Img_Label::save_file);
    auto cp2clip_action = menu->addAction("复制到剪切板");
    connect(cp2clip_action, &QAction::triggered, this, &Img_Label::cp2clip);
    menu->addSeparator();
    auto close_actoin = menu->addAction("关闭");
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
        }
    }
}

void Img_Label::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Up) {
        rotate_pixmap(90);
    } else if(e->key() == Qt::Key_Down) {
        rotate_pixmap(-90);
    }
}

void Img_Label::set_tmp_path(const QString &path) {
    this->tmp_path = path;
}

void Img_Label::save_file() {

    auto file_name = QFileDialog::getSaveFileName(this, tr("保存图片")
                                                  , this->tmp_path,
                                                  tr("*.png"));
    if(!file_name.isNull())
        this->pixmap().save(file_name, "png");
}

void Img_Label::cp2clip() {
    QApplication::clipboard()->setPixmap(this->pixmap());
}

void Img_Label::rotate_pixmap(int angle) {
    QTransform transform;
    angle_now += angle;
    transform.rotate(angle_now);
    QImage img(this->tmp_path);
    img = img.transformed(transform);
    int w = this->width();
    int h = this->height();
    this->resize(h, w);
    this->setPixmap(QPixmap::fromImage(img));
}
