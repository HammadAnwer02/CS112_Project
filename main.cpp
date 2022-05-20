#include <iostream>

#include <vector>
#include "Net.h"


int main()
{
    vector<unsigned> topology;
    topology.push_back(9);
    topology.push_back(3);
    topology.push_back(1);


    Net myNet(topology);

    vector<double> inputVals;
    
    myNet.feedForward(inputVals);

    vector<double> targetVals;

    myNet.backProp(targetVals);


    vector<double> resultVals;
    myNet.getResult(resultVals);
          


}