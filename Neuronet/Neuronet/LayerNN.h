#ifndef LAYERNN_H
#define LAYERNN_H

class LayerNN
{
public:
    LayerNN();

    ~LayerNN();

    int getInputsCount() const;

    int getOutputsCount() const;

    void setInputOutput(int inputsCount, int outputsCount);

    void setLearnRate(float learnRate);

    void setActivation(float (*activation) (float));

    float* getSignals();

    float* getResults();

    float* getErrors();

    float* getWeights();

    float randomWeight(float mult, float offset) const;

    float derivateActivation(float value) const;

    float* getWeight(int indexInput, int indexOutput);

    void updateWeights(float* enteredValue);

    void calculateResults(float* inputs);

    void calculateOutputError(float* targets);

    void calculateHiddenError(LayerNN* nextLayerNN);

private:
    int mInputsCount;
    int mOutputsCount;
    float mLearnRate;
    float (*mActivation) (float);
    float* mSignals;
    float* mResults;
    float* mErrors;
    float* mWeights;
};

#endif // LAYERNN_H
