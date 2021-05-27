#ifndef DEMOG_H
#define DEMOG_H
#include "raceDemogData.h"
#include "regionData.h"
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "visitor.h"
using namespace std;

/*
  class to represent county demographic data
  from CORGIS
*/
class demogData : public enable_shared_from_this<demogData>, public regionData
{
public:
  //Constructors
  demogData(string inN, string inS, double in65, double in18, double in5, double inB, double inH, int totPop14, double inP, raceDemogData rd) : name(inN), state(inS), popOver65Count(in65 * totPop14 / 100), popUnder18Count(in18 * totPop14 / 100), popUnder5Count(in5 * totPop14 / 100), popBachelorsCount(inB * totPop14 / 100),
                                                                                                                                                popHighSchoolCount(inH * totPop14 / 100), totalPopulation2014(totPop14), popBelowPovertyCount(round(inP * totPop14 / 100)), racialData(rd) {}
  demogData()
  {
    name = "";
    state = "";
    popOver65Count = 0;
    popUnder18Count = 0;
    popUnder5Count = 0;
    popBachelorsCount = 0;
    popHighSchoolCount = 0;
    popBelowPovertyCount = 0;
    totalPopulation2014 = 0;
  }
  void accept(class Visitor &v);
  raceDemogData getCommunityRaceMix() const { return racialData; }
  //Getters
  string getName() const
  {
    return name;
  }
  string getState() const { return state; }
  double getpopOver65() const { return popOver65Count * 100 / totalPopulation2014; }
  double getpopUnder18() const { return popUnder18Count * 100 / totalPopulation2014; }
  double getpopUnder5() const { return popUnder5Count * 100 / totalPopulation2014; }
  double getBAup() const { return popBachelorsCount * 100 / totalPopulation2014; }
  double getHSup() const { return popHighSchoolCount * 100 / totalPopulation2014; }
  int getPop() const { return totalPopulation2014; }
  double getPopBelowPoverty() const { return 100.f * ((double)(popBelowPovertyCount)) / totalPopulation2014; }
  int getBelowPovertyCount() const { return this->getPovertyCount(); }
  raceDemogData getRacialData() const { return racialData; }
  //Getters for counts
  int getpopOver65Count() const { return round(popOver65Count); }
  int getpopUnder18Count() const { return round(popUnder18Count); }
  int getpopUnder5Count() const { return round(popUnder5Count); }
  int getBAupCount() const { return round(popBachelorsCount); }
  int getHSupCount() const { return round(popHighSchoolCount); }
  int getPovertyCount() const
  {
    return round(popBelowPovertyCount);
  }
  double getBelowPoverty() const { return this->getPopBelowPoverty(); }

  virtual void toString(std::ostream &out) const
  {
    out << "County Demographics Info: " << this->getName() << ", " << this->getState();
    out << " total population: " << this->getPop();
    //consider re-writing with getters....
    out << "\nPopulation info: \n(\% over 65): " << this->getpopOver65();
    out << " Count: " << this->getpopOver65Count();
    out << "\n(\% under 18): " << this->getpopUnder18();
    out << " Count: " << this->getpopUnder18Count();
    out << "\n(\% under 5): " << this->getpopUnder5();
    out << " Count: " << this->getpopUnder5Count();
    out << "\nEducation info: ";
    out << "\n(\% Bachelor degree or more): " << this->getBAup();
    out << " Count: " << this->getBAupCount();
    out << "\n(\% high school or more): " << this->getHSup();
    out << " Count: " << this->getHSupCount();
    out << "\n(\% under the poverty level): " << this->getPopBelowPoverty();
    out << " Count: " << this->getPovertyCount();
  }

protected:
  string name;
  string state;
  double popOver65Count;
  double popUnder18Count;
  double popUnder5Count;
  double popBachelorsCount;
  double popHighSchoolCount;
  double popBelowPovertyCount;
  int totalPopulation2014;
  raceDemogData racialData;
};
#endif