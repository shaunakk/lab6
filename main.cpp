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
    //3.1-3.2
    cout << "State data Pop under 18 and below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18, &demogData::getBelowPoverty,
                                          &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

    //3.3-3.5
    cout << "County data Pop under 18 and below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18, &demogData::getBelowPoverty,
                                          &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

    //3.6
    cout << "State data Pop below poverty and hsup: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, &demogData::getHSup,
                                          &demogData::getBelowPovertyCount, &demogData::getHSupCount);

    //3.7-3.8
    cout << "County data Pop below poverty and hsup: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, &demogData::getHSup,
                                          &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    //4.1
    cout << "County data Pop mental illness and whites: " << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getWhiteCount);

    //4.2
    cout << "County data Pop mental illness and african american: " << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getBlackCount);

    //4.3
    cout << "County data total population and number of incidents: " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getPop, &psCombo::getNumberOfCases);

    //4.4
    cout << "County data population under 18 and number of incidents under 18: " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getpopUnder18Count, &psCombo::getCasesUnder18);

    //5.1
    cout << "mean of the proportion of the population at the county level that is White versus the proportion of the reported police shooting when the victim is White (non Hispanic): " << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);

    //5.2
    cout << "mean of the proportion of the population at the county level that is black versus the proportion of the reported police shooting when the victim is black: " << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);

    //5.3
    cout << "mean of the proportion of the population at the state level that is white versus the proportion of the reported police shooting when the victim is white: " << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);

    //5.4
    cout << "mean of the proportion of the population at the state level that is black versus the proportion of the reported police shooting when the victim is black: " << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);

    //5.5
    cout << "mean of the proportion of the population at the state level that is hispanic versus the proportion of the reported police shooting when the victim is hispanic " << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getLatinxCount, &raceDemogData::getLatinxCount);

    //5.6
    cout << "mean of the proportion of the population at the state level that is native versus the proportion of the reported police shooting when the victim is native " << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getFirstNationCount, &raceDemogData::getFirstNationCount);

    //5.7
    cout << "mean of the proportion of the population at the state level that is asian versus the proportion of the reported police shooting when the victim is asian " << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getAsianCount, &raceDemogData::getAsianCount);
    return 0;
}
