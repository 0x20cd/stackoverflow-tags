#include "stackoverflowapi.h"

void StackOverflowApi::questions_tagged_count(QString tag, QDate startdate, int points, int period)
{
    QString url, turl;
    QEventLoop loop;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QJsonDocument json;
    QVector<int> data;

    turl = QString("https://api.stackexchange.com/2.3/questions?"
                   "site=stackoverflow&filter=total&tagged=%1&fromdate=%2&todate=%3").arg(tag);

    int i, delta;
    for (i = delta = 0; i < points; ++i)
    {
        url = turl.arg(startdate.addDays(delta).toString("yyyy-MM-dd"));
        url = url.arg(startdate.addDays((delta += period)).toString("yyyy-MM-dd"));
        reply = manager.get(QNetworkRequest(url));
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

        loop.exec();

        if (reply->error() != QNetworkReply::NetworkError::NoError)
            break;

        json = QJsonDocument::fromJson(reply->readAll());
        if (json.isNull() || !json.isObject())
            break;

        QJsonValue val = json.object().value("total");
        if (val.isUndefined() || !val.isDouble())
            break;

        data.push_back(val.toInt());
    }

    if (i < points)
        data.clear();

    emit finished(data);
}
