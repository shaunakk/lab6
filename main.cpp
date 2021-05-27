//Shaunak Kale and Cassandra Lem
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "psData.h"
#include "parse.h"
#include "dataAQ.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "statTool.h"

using namespace std;

int main()
{
    vector<shared_ptr<regionData>> pileOfData;
    //create a visitor to combine the state data
    visitorCombineState theStates;
    statTool::createStateData(pileOfData, theStates);
    theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //Do stats work here
    cout << "State data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount);
    cout << "County data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount);

    return 0;
}
