#include <iostream>
#include <vector>
#include "Neuron.h"
#include <cmath>



using namespace std;

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned numOutputs, unsigned myIndex) {
    for (unsigned c = 0; c < numOutputs; ++c)
    {
        m_output_weights.push_back(Connection());
        m_output_weights.back().weight = randomWeight();
    }
    m_myIndex = myIndex;
}


double Neuron::transferFunction(double sum) 
{
    return tanh(sum);
}

double Neuron::transferFunctionDeravative(double sum) {
    return 1.0 - sum*sum;
}


double Neuron::sumDOW(const Layer &nextLayer) const {
    double sum = 0.0;

    for (unsigned n = 0; n < nextLayer.size() -1; ++n)
    {
        sum += m_output_weights[n].weight * nextLayer[n].m_gradient;
    }
    return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer) {
    for (unsigned n = 0; n < prevLayer.size() ; ++n) {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_output_weights[m_myIndex].deltaWeight;
        double newDeltaWeight = 
        // Individual inputs, magnified by the gradient  and train rate
        eta 
        * neuron.getOutputVal()
        * m_gradient
        + alpha
        * oldDeltaWeight;

        neuron.m_output_weights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_output_weights[m_myIndex].weight += newDeltaWeight;
    }
}


void Neuron::feedForward(const Layer& prevLayer) {
    double sum =0.0;
    // Sum the previous layer outputs which are our inputs
    //  Include the bias node from the previous layer

    for (unsigned n= 0; n < prevLayer.size() ; ++n) {
        sum+= prevLayer[n].getOutputVal() * 
            prevLayer[n].m_output_weights[m_myIndex].weight;

        m_output_vals = transferFunction(sum);

    }
    
}

void Neuron::calcOutputGradients(double targetVal) {
    double delta = targetVal - m_output_vals;
    m_gradient = delta * Neuron::transferFunctionDeravative(m_output_vals);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunctionDeravative(m_output_vals);
}

Neuron::~Neuron() {

}