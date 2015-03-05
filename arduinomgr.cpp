#include "arduinomgr.h"

#include <QDebug>
#include <QProcess>

ArduinoMgr::ArduinoMgr(QObject *parent) : QObject(parent)
{
    serial.setPortName("usbmodem1451");
    serial.open(QIODevice::ReadWrite);
    qDebug() << serial.portName();
    if(!serial.isOpen())
    {
        qDebug()<<"port is not open"<<endl;
    }

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(&serial, &QSerialPort::readyRead, [=]()
    {
        databuf += serial.readAll();

        QString strData = databuf;
        if (!strData.contains("B:") || !strData.contains("-"))
            return;

        databuf.remove(0, strData.indexOf("-") + 2);
        strData = strData.right(strData.length() - strData.indexOf("B:"));
        strData = strData.left(strData.indexOf(("-")));
        auto datalist = strData.split("\r\n");
        Q_FOREACH(QString data, datalist)
        {
            if (data.startsWith("B:"))
            {
                QString brightness = data.right(data.length() - 2);
                if (m_brightness != brightness.toInt())
                {
                    m_brightness = brightness.toInt();
                    emit brightnessChanged();
                }
            }

            if (data.startsWith("V:"))
            {
                QString volume = data.right(data.length() - 2);
                if (m_volume != volume.toInt())
                {
                    m_volume = volume.toInt();
                    QProcess exec;
                    QString setVolumeCmd = "osascript -e \"set Volume " + QString::number(m_volume/102) + "\"";
                    exec.start(setVolumeCmd);
                    exec.waitForFinished();
                    emit volumeChanged();
                }
            }
        }
    });

}


void ArduinoMgr::turnOn(qint32 id)
{
    QString cmd = "TURN_ON_";
    cmd.append(QString::number(id));
    cmd.append("\n");
    serial.write(cmd.toLocal8Bit());
    serial.flush();

}

void ArduinoMgr::turnOff(qint32 id)
{
    QString cmd = "TURN_OFF_";
    cmd.append(QString::number(id));
    cmd.append("\n");
    serial.write(cmd.toLocal8Bit());
    serial.flush();
}

qint32 ArduinoMgr::brightness()
{
    return m_brightness;
}

qint32 ArduinoMgr::volume()
{
    return m_volume;
}
