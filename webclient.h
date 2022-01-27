#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);

private slots:
    void on_goButton_clicked();
    void on_hostnameInput_returnPressed();

public slots:
    void connected();
    void readyRead();

private:
    QTcpSocket *m_socket;
    QString m_hostname;
};

#endif // WEBCLIENT_H

