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
    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);

    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG);
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //Do stats work here
    // cout << "State data Pop under 18 and below poverty: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18, &demogData::getBelowPoverty,
    //                                       &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);
    // cout << "County data Pop under 18 and below poverty: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18, &demogData::getBelowPoverty,
    //                                       &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);
    // cout << "State data Pop below poverty and hsup: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, &demogData::getHSup,
    //                                       &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    // cout << "County data Pop below poverty and hsup: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, &demogData::getHSup,
    //                                       &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    cout << "County data Pop below poverty and hsup: " << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getNumMentalI);

    return 0;
}
