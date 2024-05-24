#include "Form.h"
#include "ui_Form.h"

#include <cmath>

float Sigmoida(float value) {
    return (1 - 2.0 / (1.0 + std::exp(2 * value)));
}

float Line(float value) {
    return value;
}

Form::Form(QWidget* parent)
    : QWidget(parent)
    , mUI(new Ui::Form())
{
    mUI->setupUi(this);

    int neuronsInLayers[4] = {1, 100, 10, 1};
    mNN = new Neuronet(neuronsInLayers, 3, Sigmoida, 0.1);
    mNN->getLayer(1)->setActivation(Line);

    mUI->customPlot->addGraph();
    mUI->customPlot->graph(0)->setPen(QPen(Qt::red));
    mUI->customPlot->addGraph();
    mUI->customPlot->graph(1)->setPen(QPen(Qt::black));
    mUI->customPlot->addGraph();
    mUI->customPlot->graph(2)->setPen(QPen(Qt::green));
    mUI->customPlot->addGraph();
    mUI->customPlot->graph(3)->setPen(QPen(Qt::blue));
    mUI->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    clearPlot(mUI->customPlot);

    qsrand((QTime::currentTime().second()));
    for (float t = 0; t <= 10; t += 0.01) {
        float out = 1 - std::exp(-t);
        float in =  t;
        float noise = out + std::pow(-1, (qrand() % 2)) * (qrand() % 100) * 0.005;
        mTimes.push_back(t);
        mInputs.push_back(in);
        mOutputs.push_back(out);
        mNoises.push_back(noise);
        addPoint(mUI->customPlot, 0, t, noise);
        addPoint(mUI->customPlot, 1, t, out);
    }
}

Form::~Form()
{
    delete mUI;
    delete mNN;
}

void Form::addPoint(QCustomPlot* plot, int number, double x, double y)
{
    plot->graph(number)->addData(x, y);
    double minX = plot->xAxis->range().lower;
    double maxX = plot->xAxis->range().upper;
    double minY = plot->yAxis->range().lower;
    double maxY = plot->yAxis->range().upper;
    plot->xAxis->setRange(std::min(x, minX), std::max(x, maxX));
    plot->yAxis->setRange(std::min(y, minY), std::max(y, maxY));
    plot->replot();
}

void Form::clearPlot(QCustomPlot* plot)
{
    for (int i = 0; i < plot->graphCount(); ++i) {
        plot->graph(i)->clearData();
    }
    plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(0, 1);
}

void Form::updateGraph()
{
    clearPlot(mUI->customPlot);
    for (int k = 0; k < 100; ++k) {
        for (int i = 0; i < mInputs.size(); ++i) {
            mNN->train(&mInputs[i], &mNoises[i]);
        }
    }
    for (int i = 0; i < mTimes.size(); ++i) {
        float out = *mNN->query(&mTimes[i]);
        float error = out - mOutputs[i];
        addPoint(mUI->customPlot, 0, mTimes[i], mNoises[i]);
        addPoint(mUI->customPlot, 1, mTimes[i], mOutputs[i]);
        addPoint(mUI->customPlot, 2, mTimes[i], out);
        addPoint(mUI->customPlot, 3, mTimes[i], error);
    }
}

void Form::on_pushButtonStart_clicked()
{
    updateGraph();
}
