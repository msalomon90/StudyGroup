#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTimer>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    void connect_server();
    // Account Functions
    bool login(QString& username, QString& password, QString& email);
    bool create_account(QString& username, QString& password, QString& email);
    bool recover_user(QString& email);
    bool recover_password(QString& username, QString& email);
    bool logout();
    // Group Functions
    bool create_group(QString& group_name, QString& group_id);
    bool join_group(QString& group_id);
    bool leave_group(QString& group_id);

signals:
    void disconnected();
    // Group Signals
    void new_chat(QString,QString,QString);
    void users_changed();
    void user_joined(QString);
    void user_left(QString);
    // Whiteboard
    void whiteboard_draw_line(const QPoint&, const QPoint&, const QColor&, const int&);
    void get_whiteboard(QString);
    void update_whiteboard(QByteArray*);

public slots:
    // Socket helper functions
    void reconnect_socket(QAbstractSocket::SocketState);
    void read_socket_send_signal();
    // Group Slots
    void send_chat(QString& groupID, QString& message);
    // Whiteboard Slots
    void send_whiteboard_line(const QString& groupID, const QPoint& point1, const QPoint& point2, const QColor& pen_color, const int& pen_size);
    void send_whiteboard(QString& ip, QByteArray* whiteboard);
    void save_whiteboard(QString& group_id, QByteArray* whiteboard);
    void error(QAbstractSocket::SocketError);
    void send_card(QString&, QString&, int&, int&);

private:
    QTcpSocket* my_socket;
    bool reconnecting;

    QString username;
    bool success_flag; // ***Always set this to 0 before checking, ONLY to be set to 1 by the read_socket_send_signal() function.
    bool fail_flag;    // ***Always set this to 0 before checking, ONLY to be set to 1 by the read_socket_send_signal() function.
    QString success_message; // ***Always set this to nullptr before checking, ONLY to be set by the read_socket_send_signal() function.

    QByteArray format_socket_request(const QString& request_code, QString request_arg);
    QByteArray format_socket_request(const QString &request_code, const QByteArray& request_arg);
    bool read_socket_helper(QString& out_message);
};

#endif // SERVER_H
