#include "appengine.h"

AppEngine::AppEngine(QObject *qmlObject, QObject *parent)
    : QObject(parent)
    , qmlObject(qmlObject)
    , calendar(qmlObject->findChild<QObject*>("calendar"))
    , comboBoxPeriod(qmlObject->findChild<QObject*>("comboBoxPeriod"))
    , comboBoxTag(qmlObject->findChild<QObject*>("comboBoxTag"))
    , labelDateInterval(qmlObject->findChild<QObject*>("labelDateInterval"))
    , chartView(qmlObject->findChild<QObject*>("chartView"))
    , windowTitle(qmlObject->property("title").toString())
{
    this->api.moveToThread(&this->thread);
    QObject::connect(this, &AppEngine::dataRequested, &this->api, &StackOverflowApi::questions_tagged_count);
    QObject::connect(&this->api, &StackOverflowApi::finished, this, &AppEngine::onDataReceived);

    QtCharts::QAbstractSeries *series_ptr;
    QMetaObject::invokeMethod(
        this->chartView,
        "series",
        Qt::AutoConnection,
        Q_RETURN_ARG(QtCharts::QAbstractSeries*, series_ptr),
        Q_ARG(int, 0)
    );
    this->chartSeries = static_cast<QtCharts::QXYSeries*>(series_ptr);
    this->axisX = static_cast<QtCharts::QValueAxis*>(this->chartSeries->property("axisX").value<QtCharts::QAbstractAxis*>());
    this->axisY = static_cast<QtCharts::QValueAxis*>(this->chartSeries->property("axisY").value<QtCharts::QAbstractAxis*>());
    this->axisX->setMin(0);
    this->axisX->setVisible(false);
}

void AppEngine::buttonSend_onClick()
{
    QString tag = this->comboBoxTag->property("currentText").toString();
    QDate date = this->calendar->property("selectedDate").toDate();
    int points = this->comboBoxPeriod->property("currentValue").toPoint().x();
    int period = this->comboBoxPeriod->property("currentValue").toPoint().y();

    this->labelDateInterval->setProperty("text", date.toString() + " - " + date.addDays(points*period).toString());

    this->thread.start();
    this->setEnabled(false);
    emit dataRequested(tag, date, points, period);
}

void AppEngine::onDataReceived(QVector<int> data)
{
    this->thread.exit();
    this->setEnabled(true);
    if (data.empty())
        return;

    this->chartSeries->clear();
    for (int i = 0; i < data.size(); ++i)
        this->chartSeries->append(i, data[i]);

    auto bounds = std::minmax_element(data.begin(), data.end());
    this->axisY->setMin(*bounds.first);
    this->axisY->setMax(std::max(1, *bounds.second));
    this->axisX->setMax(data.length()-1);
    this->axisY->applyNiceNumbers();
}

void AppEngine::setEnabled(bool value)
{
    qmlObject->setProperty("title", value ? windowTitle : windowTitle + " | Receiving data...");
    for (QObject *obj : this->qmlObject->children())
        obj->setProperty("enabled", value);
}
