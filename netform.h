#ifndef NETFORM_H
#define NETFORM_H

#include "qtextcursor.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QSyntaxHighlighter>
#include <QFont>
#include <QScrollBar>

#include <QFileDialog>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class NetFrom;
}
QT_END_NAMESPACE

class NetForm : public QWidget
{
    Q_OBJECT
public:
    NetForm(QWidget *parent = nullptr);
    ~NetForm();

protected:
    Ui::NetFrom *ui;

private:
    QTcpServer *tcpServer = new QTcpServer();
    QList<QTcpSocket*> clientList;
    QTcpSocket *currentClient= new QTcpSocket();
    QTimer *timer;
    QTextCursor cursor;
    QTextCharFormat highlight;
    QTextCharFormat textdefault;
    QScrollBar *scrollbar;



private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void NewConnectionSlot();
    void timerOperation();
    void on_checkBox_stateChanged(int arg1);
    void on_textEdit_cursorPositionChanged();
};

// QString updateRealTimeData()
// {
//     QDateTime dateTime= QDateTime::currentDateTime();
//     return dateTime.toString("[ hh:mm:ss:z ]");
// }

#endif // NETFORM_H
