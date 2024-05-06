#include "Neuronet.h"

Neuronet::Neuronet(int* neuronsInLayers, int countLayers,
                   float (*activation)(float), float learnRate)
{
    mCountLayers = countLayers;
    mLayers = new LayerNN[mCountLayers];
    for (int i = 0; i < mCountLayers; ++i) {
        mLayers[i].setInputOutput(neuronsInLayers[i], neuronsInLayers[i + 1]);
        mLayers[i].setLearnRate(learnRate);
        mLayers[i].setActivation(activation);
    }
}

Neuronet::~Neuronet()
{
    delete[] mLayers;
}

LayerNN* Neuronet::getLayer(int index)
{
    return mLayers + index;
}

void Neuronet::train(float* inputs, float* targers)
{
    query(inputs);
    mLayers[mCountLayers - 1].calculateOutputError(targers);
    for (int i = mCountLayers - 2; i >= 0; --i) {
        mLayers[i].calculateHiddenError(&mLayers[i + 1]);
    }
    for (int i = mCountLayers - 1; i > 0; --i) {
        mLayers[i].updateWeights(mLayers[i - 1].getResults());
    }
    mLayers[0].updateWeights(inputs);
}

float* Neuronet::query(float* inputs)
{
    mLayers[0].calculateResults(inputs);
    for (int i = 1; i < mCountLayers; ++i) {
        mLayers[i].calculateResults(mLayers[i - 1].getResults());
    }
    return mLayers[mCountLayers - 1].getResults();
}
