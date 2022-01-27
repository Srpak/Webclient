#include "webclient.h"
#include <QtNetwork/QTcpSocket>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void Webclient::on_goButton_clicked() 
{
    m_hostname = hostnameInput->text();
    if (m_hostname != "") 
    {
        unsigned short port = 80;
        m_socket= new QTcpSocket(this);
        connect(m_socket, &QTcpSocket::connected, this, &Webclient::connected);
        connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::readyRead);
        m_socket->connectToHost(m_hostname, port);

        if (!m_socket->waitForConnected(5000)) 
        {
            outputTextbox->setText("Verbindung fehlgeschlagen!");
        }
    }
    else 
    {
        outputTextbox->setText("Hostname eingeben!");
    }
}

void Webclient::connected() 
{
    outputTextbox->setText("Verbunden\n");
    this->m_socket->write("GET / HTTP/1.1\r\nHost:" + m_hostname.toLocal8Bit());
}

void Webclient::readyRead() 
{
    QString output = QString(m_socket->readAll());
    while (output.at(output.length() - 1) == "\xa") 
    {
        output.resize(output.length() - 2);
    }
   
    outputTextbox->append(output);
    m_socket->disconnectFromHost();
    outputTextbox->append("\nVerbindung getrennt");
}


