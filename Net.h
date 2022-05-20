
#pragma once
#include <iostream>

#include <iomanip>

#include <cmath>
#include <cassert>
#include <vector>
#include "Neuron.h"
using namespace std;









class Net {

    public:
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResult(vector<double> &resultVals) const;
    
    private:
    vector<Layer> m_layers;
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;

};
