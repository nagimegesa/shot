#ifndef IMG_LABEL_H
#define IMG_LABEL_H

#include <QLabel>

class QMenu;

class Img_Label : public QLabel
{
public:
    Img_Label(QWidget* parent = nullptr);

    void init_menu();

protected:
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
//    virtual void wheelEvent(QWheelEvent* e) override;

private:
    bool is_left_press;
    QPointF last_pos;
    QMenu* menu;
};

#endif // IMG_LABEL_H
