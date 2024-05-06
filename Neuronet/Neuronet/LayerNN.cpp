#include "LayerNN.h"

LayerNN::LayerNN()
{
    mSignals = nullptr;
    mResults = nullptr;
    mErrors = nullptr;
    mWeights = nullptr;
}

LayerNN::~LayerNN()
{
    delete[] mSignals;
    delete[] mResults;
    delete[] mErrors;
    delete[] mWeights;
}

int LayerNN::getInputsCount() const
{
    return mInputsCount;
}

int LayerNN::getOutputsCount() const
{
    return mOutputsCount;
}

void LayerNN::setInputOutput(int inputsCount, int outputsCount)
{
    mInputsCount = inputsCount;
    mOutputsCount = outputsCount;
    delete[] mSignals;
    delete[] mResults;
    delete[] mErrors;
    delete[] mWeights;
    mSignals = new float[mOutputsCount];
    mResults = new float[mOutputsCount];
    mErrors = new float[mOutputsCount];
    mWeights = new float[mOutputsCount * (mInputsCount + 1)];
    for (int in = 0; in < mInputsCount + 1; ++in) {
        for (int out = 0; out < mOutputsCount; ++out) {
            *getWeight(in, out) = randomWeight(in, out);
        }
    }
}

void LayerNN::setLearnRate(float learnRate)
{
    mLearnRate = learnRate;
}

void LayerNN::setActivation(float (*activation)(float))
{
    mActivation = activation;
}

float* LayerNN::getSignals()
{
    return mSignals;
}

float* LayerNN::getResults()
{
    return mResults;
}

float* LayerNN::getErrors()
{
    return mErrors;
}

float* LayerNN::getWeights()
{
    return mWeights;
}

float LayerNN::randomWeight(float mult, float offset) const
{
    static int random = 0;
    random *= mult;
    random += offset;
    random %= 10;
    return random / 100.f;
}

float LayerNN::derivateActivation(float value) const
{
    static const float Step = 1e-6;
    return (mActivation(value + Step) - mActivation(value)) / Step;
}

float* LayerNN::getWeight(int indexInput, int indexOutput)
{
    int index = indexInput + indexOutput * (mInputsCount + 1);
    return mWeights + index;
}

void LayerNN::updateWeights(float* enteredValue)
{
    for (int out = 0; out < mOutputsCount; ++out) {
        for (int in = 0; in < mInputsCount; ++in) {
            *getWeight(in, out) += mLearnRate * mErrors[out] * enteredValue[in];
        }
        *getWeight(mInputsCount, out) += mLearnRate * mErrors[out];
    }
}

void LayerNN::calculateResults(float* inputs)
{
    for (int out = 0; out < mOutputsCount; ++out) {
        mSignals[out] = 0;
        for (int in = 0; in < mInputsCount; ++in) {
            mSignals[out] += *getWeight(in, out) * inputs[in];
        }
        mSignals[out] += *getWeight(mInputsCount, out);
        mResults[out] = mActivation(mSignals[out]);
    }
}

void LayerNN::calculateOutputError(float* targets)
{
    for (int out = 0; out < mOutputsCount; ++out) {
        mErrors[out] = (targets[out] - mResults[out]) * derivateActivation(mSignals[out]);
    }
}

void LayerNN::calculateHiddenError(LayerNN* nextLayerNN)
{
    for (int in = 0; in < nextLayerNN->getInputsCount(); ++in) {
        mErrors[in] = 0;
        for (int out = 0; out < nextLayerNN->getOutputsCount(); ++out) {
            mErrors[in] += *(nextLayerNN->getWeight(in, out)) * nextLayerNN->getErrors()[out];
        }
        mErrors[in] *= derivateActivation(mSignals[in]);
    }
}
