#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"
#include <map>
/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData
{
public:
  void addCountyData(demogData d)
  {
    numCounties++;
    popOver65Count += d.getpopOver65Count();
    popUnder18Count += d.getpopUnder18Count();
    popUnder5Count += d.getpopUnder5Count();
    popBachelorsCount += d.getBAupCount();
    popHighSchoolCount += d.getHSupCount();
    totalPopulation2014 += d.getPop();
    popBelowPovertyCount += d.getPovertyCount();
    racialData += d.getRacialData();
    states[d.getState()] = true;
  }
  int getNumCounties() const { return numCounties; }

  virtual void toString(std::ostream &out) const
  {
    out << fixed << setprecision(2);
    out << "Region info: comboData, ";
    for (auto s : this->states)
    {
      out << s.first;
    }
    // out << "total states: " << this->states.size();
    // out << "\nNumber of Counties: " << this->getNumCounties();
    // out << " County Demographics Info: comboData, many";
    // //consider re-writing with getters....
    // out << "\nPopulation info: \n(over 65): " << this->getpopOver65() << "\%";
    // out << " and total: " << this->getpopOver65Count();
    // out << "\n(under 18): " << this->getpopUnder18() << "\%";
    // out << " and total: " << this->getpopUnder18Count();
    // out << "\n(under 5): " << this->getpopUnder5() << "\%";
    // out << " and total: " << this->getpopUnder5Count();
    out << "\nEducation info:";
    out << "\n(Bachelor or more): " << this->getBAup() << "\%";
    out << " and total: " << this->getBAupCount();
    out << "\n(high school or more): " << this->getHSup() << "\%";
    out << " and total: " << this->getHSupCount();
    // out << "\npersons below poverty: " << this->getPopBelowPoverty() << "\%";
    // out << " and total: " << this->getPovertyCount();
    out << "\nTotal population: " << this->getPop();
    out << "\nRacial Demographics Info: ";
    out << "\n\% American Indian and Alaska Native percent: ";
    out << this->getRacialData().getFirstNationPercent() << " count: " << this->getRacialData().getFirstNationCount();
    out << "\n\% Asian American percent: ";
    out << this->getRacialData().getAsianPercent() << " count: " << this->getRacialData().getAsianCount();
    out << "\n\% Black/African American percent: ";
    out << this->getRacialData().getBlackPercent() << " count: " << this->getRacialData().getBlackCount();
    out << "\n\% Hispanic or Latinx percent: ";
    out << this->getRacialData().getLatinxPercent() << " count: " << this->getRacialData().getLatinxCount();
    out << "\n\% Native Hawaiian and Other Pacific Islander percent: ";
    out << this->getRacialData().getHIPacificIslePercent() << " count: " << this->getRacialData().getHIPacificIsleCount();
    out << "\n\% Two or More Races percent: ";
    out << this->getRacialData().getMultiRacePercent() << " count: " << this->getRacialData().getMultiRaceCount();
    out << "\n\% White (inclusive) percent: ";
    out << this->getRacialData().getWhitePercent() << " count: " << this->getRacialData().getWhiteCount();
    out << "\n\% White (nonHispanic) percent: ";
    out << this->getRacialData().getWhiteNHPercent() << " count: " << this->getRacialData().getWhiteNHCount();
    out << "\ntotal Racial Demographic Count: " << this->getRacialData().getCommunityCount();
  }

private:
  int numCounties = 0;
  std::map<string, bool> states;
};
#endif