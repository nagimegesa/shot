#ifndef SHOT_H
#define SHOT_H

#include <QWidget>
#include <QToolBar>

class QSystemTrayIcon;

class Shot : public QWidget
{
    Q_OBJECT

public:
    Shot(QWidget *parent = nullptr);
    ~Shot();

public:
    void register_tray(QSystemTrayIcon* tray);

    void register_tool_bar(QToolBar* tool_bar);

    void shot_screen();

    void put_img();

protected:
    virtual void keyPressEvent(QKeyEvent* e) override;

    virtual void paintEvent(QPaintEvent* e) override;

    virtual void mousePressEvent(QMouseEvent* e) override;

    virtual void mouseReleaseEvent(QMouseEvent* e) override;

    virtual void mouseMoveEvent(QMouseEvent* e) override;

private:
    QSystemTrayIcon* system_tray;
    QToolBar* tool_bar;
    bool is_left_press;
    QPoint start_point;
    QPoint end_point;

private:
    struct Select_Info {
        int up_x;
        int up_y;
        int blow_x;
        int blow_y;
    };

    Select_Info get_select_info();
};
#endif // SHOT_H
