#ifndef ARDUINOMGR_H
#define ARDUINOMGR_H

#include <QObject>
#include <QSerialPort>
class ArduinoMgr : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 brightness READ brightness NOTIFY brightnessChanged)
    Q_PROPERTY(qint32 volume READ volume NOTIFY volumeChanged)
public:
    ArduinoMgr(QObject *parent);
public slots:

    qint32 brightness();
    qint32 volume();

    void turnOn(qint32 id);
    void turnOff(qint32 id);

signals:
    void brightnessChanged();
    void volumeChanged();
private:
    QSerialPort serial;
    QString databuf;

    QString m_author;
    qint32 m_brightness;
    qint32 m_volume;
};

#endif // ARDUINOMGR_H
