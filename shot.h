#ifndef SHOT_H
#define SHOT_H

#include <QWidget>
#include <QToolBar>
#include <QDir>

#include <QSystemTrayIcon>

class Shot : public QWidget
{
    Q_OBJECT

public:
    Shot(QWidget *parent = nullptr);
    ~Shot();

public:
    void register_tray(QSystemTrayIcon* tray);

    void register_tool_bar(QToolBar* tool_bar);

public slots:
    void tray_msg(QSystemTrayIcon::ActivationReason reason);

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
    QDir* tmp_dir;

private:
    struct Select_Info {
        int up_x;
        int up_y;
        int blow_x;
        int blow_y;
    };

    Select_Info get_select_info();

private:
#ifdef __linux__
    static constexpr const char* tmp_dir_path = "/tmp/shot/";
#elif _WIN32
    static constexpr const char* tmp_dir_path = "./tmp/";
#endif
};
#endif // SHOT_H
