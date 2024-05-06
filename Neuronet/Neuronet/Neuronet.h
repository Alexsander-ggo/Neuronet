#ifndef NEURONET_H
#define NEURONET_H

#include "LayerNN.h"

class Neuronet
{
public:
    Neuronet(int* neuronsInLayers, int countLayers,
             float (*activation) (float), float learnRate = 0.1);

    ~Neuronet();

    LayerNN* getLayer(int index);

    void train(float* inputs, float* targers);

    float* query(float* inputs);

private:
    int mCountLayers;
    LayerNN* mLayers;
};

#endif // NEURONET_H
