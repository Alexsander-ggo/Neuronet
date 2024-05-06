#include "Neuronet.h"

#include <cmath>

#include <QDebug>
#include <QTime>

float Sigmoida(float value) {
    return 1.0 / (1.0 + std::exp(-value));
}

float Line(float value) {
    return value;
}

void Print(float* data, int size) {
    for (int i = 0; i < size; ++i) {
        qDebug() << "DATA[" << i << "] = " << data[i];
    }
}

int main()
{
    int neuronsInLayers[5] = {100, 20, 6, 3, 2};
    Neuronet nn(neuronsInLayers, 4, Line, 0.1);
    nn.getLayer(3)->setActivation(Sigmoida);

    const int INPUTS = 100;
    const int OUTPUTS = 2;
    qsrand((QTime::currentTime().second()));

    float* input1 = new float[INPUTS];
    for(int i = 0; i < INPUTS; i++) {
        input1[i] =(qrand() % 98) * 0.01 + 0.01;
    }

    float* input2 = new float[INPUTS];
    for(int i = 0; i < INPUTS; i++) {
        input2[i] =(qrand() % 98) * 0.01 + 0.01;
    }

    float* target1 = new float[OUTPUTS];
    target1[0] = 0.01;
    target1[1] = 0.99;

    float* target2 = new float[OUTPUTS];
    target2[0] = 0.99;
    target2[1] = 0.01;

    qDebug() << "ABC";
    Print(nn.query(input1), OUTPUTS);
    qDebug() << "CBA";
    Print(nn.query(input2), OUTPUTS);

    for (int i = 0; i < 100000; ++i) {
        nn.train(input1,target1);
        nn.train(input2,target2);
    }

    qDebug() << "ABC";
    Print(nn.query(input1), OUTPUTS);
    qDebug() << "CBA";
    Print(nn.query(input2), OUTPUTS);

    return 0;
}
