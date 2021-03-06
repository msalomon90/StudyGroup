#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "groupwidget.h"
#include "server.h"
#include "user_account_check.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_signin_button_clicked();

    void on_lineEdit_email_editingFinished();
    void on_lineEdit_email_cursorPositionChanged();
    void on_lineEdit_email_textEdited();

    void on_lineEdit_username_signup_editingFinished();
    void on_lineEdit_username_signup_cursorPositionChanged();
    void on_lineEdit_username_signup_textEdited();

    void on_lineEdit_password1_editingFinished();
    void on_lineEdit_password1_cursorPositionChanged();
    void on_lineEdit_password1_textEdited();

    void on_lineEdit_password2_editingFinished();

    void set_valid_icons(QLabel* this_label, QLineEdit* this_line, QString error_msg, bool valid);

    void on_singup_button_clicked();

    void on_settings_button_released();
    void exit_settings();

    void on_join_button_released();

    void on_lineEdit_password2_textEdited();

    void on_lineEdit_password2_cursorPositionChanged();

    void on_create_button_released();

    void on_create_group_button_released();

    void on_join_group_button_released();

    void on_back_to_group_button_released();

    void on_leave_button_released();

    void on_logout_button_released();

    void set_settings_btn_icon(int);

    void on_pushButton_recover_pass_clicked();

    void on_pushButton_recover_user_clicked();

    void on_stackedWidget_inner_currentChanged(int arg1);

    void on_settings_timestamps_currentIndexChanged(int index);

    void on_settings_remember_login_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    server *my_serv;
    UserAccount *user_info;
    bool auto_login;

    QWidget* exit_settings_to;
    GroupWidget* group_widget;

    void _initialize_group();
    void _activate_group(QString& group_id);
};

#endif // MAINWINDOW_H
