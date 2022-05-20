#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <random>


using namespace std;
struct Connection {
    double weight;
    double deltaWeight;
};


map<string, int> mapping = {
    {"", 0},
    {"X", 1},
    {"O", 2},
    {"positive", 3},
    {"negative", -2}
};

class Neuron;
typedef vector<Neuron> Layer;


class Neuron
{
private:
    static double randomWeight(void) {
        default_random_engine engine{static_cast<unsigned>(time(0))};
        uniform_real_distribution<double> randomDouble{0,1};
        return randomDouble(engine);
    }
    static double transferFunction(double sum);
    static double transferFunctionDeravative(double x);
    double sumDOW(const Layer &nextLayer) const;
    double m_output_vals;
    vector<Connection> m_output_weights;
    unsigned m_myIndex;
    double m_gradient;
    static double eta; // overall net learning rate
    static double alpha; // momentum
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal( double val) {m_output_vals = val;}
    double getOutputVal() const {return m_output_vals;}
    void feedForward(const Layer& prevLayer);
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);
    ~Neuron();
};

