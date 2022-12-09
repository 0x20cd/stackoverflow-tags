#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QDate>
#include <QVariant>
#include <QQmlContext>
#include <QThread>
#include <QPoint>
#include <QtCharts/QXYSeries>
#include <QtCharts/QValueAxis>
#include <algorithm>
#include "stackoverflowapi.h"

class AppEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppEngine(QObject *qmlObject, QObject *parent = nullptr);

public slots:
    void buttonSend_onClick();

private slots:
    void onDataReceived(QVector<int> data);

signals:
    void dataRequested(QString tag, QDate startdate, int points, int period);

private:
    void setEnabled(bool value);

    QObject *qmlObject, *calendar, *comboBoxPeriod, *comboBoxTag, *labelDateInterval, *chartView;
    QString windowTitle;
    QtCharts::QXYSeries *chartSeries;
    QtCharts::QValueAxis *axisX, *axisY;
    StackOverflowApi api;
    QThread thread;
};

#endif // APPENGINE_H
