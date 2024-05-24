#ifndef FORM_H
#define FORM_H

#include "Neuronet.h"

#include "qcustomplot.h"

#include <vector>

#include <QWidget>

namespace Ui {
    class Form;
}

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(QWidget* parent = nullptr);

    ~Form();

private:
    void addPoint(QCustomPlot* plot, int number,
                  double x, double y);

    void clearPlot(QCustomPlot* plot);

public slots:
    void updateGraph();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::Form* mUI;
    Neuronet* mNN;
    std::vector<float> mTimes;
    std::vector<float> mInputs;
    std::vector<float> mOutputs;
    std::vector<float> mNoises;
};

#endif // FORM_H
