#ifndef IMG_LABEL_H
#define IMG_LABEL_H

#include <QLabel>
#include <filesystem>

class QMenu;

class Img_Label : public QLabel
{
public:
    Img_Label(QWidget* parent = nullptr);

    void init_menu();
    void set_tmp_path(const QString& path);
    QString get_tmp_path();

    void save_file();
    void cp2clip();

private:
    void rotate_pixmap(int angle);
protected:
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void keyPressEvent(QKeyEvent* e) override;
//    virtual void paintEvent(QPaintEvent* e) override;
//    virtual void wheelEvent(QWheelEvent* e) override;

private:
    bool is_left_press;
    QPointF last_pos;
    QMenu* menu;
    QString tmp_path;

    int angle_now;
};

#endif // IMG_LABEL_H
