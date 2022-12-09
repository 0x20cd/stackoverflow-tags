#ifndef STACKOVERFLOWAPI_H
#define STACKOVERFLOWAPI_H
#include <QObject>
#include <QEventLoop>
#include <QDate>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>

class StackOverflowApi : public QObject
{
    Q_OBJECT
public slots:
    void questions_tagged_count(QString tag, QDate startdate, int points, int period);
signals:
    // Сигнал finished вызывается, когда получен ответ на запрос.
    // Если произошла ошибка, то data.isEmpty().
    void finished(QVector<int> data);
};

#endif // STACKOVERFLOWAPI_H
