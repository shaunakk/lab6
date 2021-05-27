/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "visitorReport.h"
using namespace std;
dataAQ::dataAQ() {}

string makeKeyExample(shared_ptr<demogData> theData)
{

  string theKey = "Key";

  if (theData->getPopBelowPoverty() < 10)
  {
    theKey += "BelowPovLessTenPer";
  }
  else if (theData->getPopBelowPoverty() < 20)
  {
    theKey += "BelowPovLessTwentyPer";
  }
  else if (theData->getPopBelowPoverty() < 30)
  {
    theKey += "BelowPovLessThirtyPer";
  }
  else
  {
    theKey += "BelowPovAboveThirtyPer";
  }

  return theKey;
}

string makeKeyExample(shared_ptr<psData> theData)
{
  string theKey = "Key";
  if (theData->getRace() == "W")
  {
    theKey += "WhiteVictim";
  }
  else if (theData->getRace() == "A")
  {
    theKey += "AsianVictim";
  }
  else if (theData->getRace() == "H")
  {
    theKey += "HispanicVictim";
  }
  else if (theData->getRace() == "N")
  {
    theKey += "NativeAmericanVictim";
  }
  else if (theData->getRace() == "B")
  {
    theKey += "AfricanAmericanVictim";
  }
  else if (theData->getRace() == "O")
  {
    theKey += "OtherRaceVictim";
  }
  else
  {
    theKey += "RaceUnspecifiedVictim";
  }
  return theKey;
}

//swtich to a function parameter
void dataAQ::createComboDemogDataKey(std::vector<shared_ptr<demogData>> &theData)
{
  for (shared_ptr<demogData> d : theData)
  {
    if (allComboDemogData.count(makeKeyExample(d)) > 0) //If the state does exist in hash map, add more county data
    {
      allComboDemogData[makeKeyExample(d)]->addCountyData(*d);
    }
    else //Otherwise, create state entry
    {
      shared_ptr<demogCombo> s = make_shared<demogCombo>();
      s->addCountyData((demogData)(*d));
      allComboDemogData[makeKeyExample(d)] = s;
    }
  }
}

void dataAQ::createComboPoliceDataKey(std::vector<shared_ptr<psData>> &theData)
{
  for (shared_ptr<psData> p : theData)
  {
    if (allComboPoliceData.count(makeKeyExample(p)) > 0) //If the state does exist in hash map, add more county data
    {
      allComboPoliceData[makeKeyExample(p)]->addIncident(*p);
    }

    else //Otherwise, create state entry
    {

      shared_ptr<psCombo> s = make_shared<psCombo>(p->getState());
      s->addIncident((psData)(*p));
      allComboPoliceData[makeKeyExample(p)] = s;
    }
  }
}

/******************************************/
/* state examples */
void dataAQ::createComboDemogData(std::vector<shared_ptr<demogData>> &theData)
{
  for (shared_ptr<demogData> d : theData)
  {
    if (allComboDemogData.count(d->getState()) > 0) //If the state does exist in hash map, add more county data
    {
      allComboDemogData[d->getState()]->addCountyData(*d);
    }
    else //Otherwise, create state entry
    {
      shared_ptr<demogCombo> s = make_shared<demogCombo>();
      s->addCountyData((demogData)(*d));
      allComboDemogData[d->getState()] = s;
    }
  }
}

void dataAQ::createComboPoliceData(std::vector<shared_ptr<psData>> &theData)
{

  for (shared_ptr<psData> p : theData)
  {
    if (allComboPoliceData.count(p->getState()) > 0) //If the state does exist in hash map, add more county data
    {
      allComboPoliceData[p->getState()]->addIncident(*p);
    }
    else //Otherwise, create state entry
    {
      shared_ptr<psCombo> s = make_shared<psCombo>(p->getState());
      s->addIncident((psData)(*p));
      allComboPoliceData[p->getState()] = s;
    }
  }
}

string dataAQ::youngestPop()
{

  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if (allComboDemogData[out]->getpopUnder5() < s.second->getpopUnder5())
    {
      out = s.first;
    }
  }
  return out;
}

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()
{
  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if (allComboDemogData[out]->getpopUnder18() < s.second->getpopUnder18())
    {
      out = s.first;
    }
  }
  return out;
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()
{
  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if (allComboDemogData[out]->getpopOver65() < s.second->getpopOver65())
    {
      out = s.first;
    }
  }
  return out;
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS()
{
  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if ((allComboDemogData[out]->getPop() - allComboDemogData[out]->getBAup()) < (s.second->getPop() - s.second->getBAup()))
    {
      out = s.first;
    }
  }
  return out;
}

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads()
{
  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if (allComboDemogData[out]->getBAup() < s.second->getBAup())
    {
      out = s.first;
    }
  }
  return out;
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty()
{
  string out = "";
  for (auto &s : allComboDemogData)
  {
    if (out == "")
    {
      out = s.first;
    }
    else if (allComboDemogData[out]->getPopBelowPoverty() < s.second->getPopBelowPoverty())
    {
      out = s.first;
    }
  }
  return out;
}

//sort and report the top ten states in terms of number of police shootings
void dataAQ::reportTopTenStatesPS()
{
  vector<pair<string, psCombo>> states;
  for (auto &s : allComboPoliceData)
  {
    states.push_back(make_pair(s.first, *(s.second)));
  }
  sort(states.begin(), states.end(), [](pair<string, psCombo> &lhs, pair<string, psCombo> &rhs) {
    return (lhs.second.getNumberOfCases() > rhs.second.getNumberOfCases());
  });
  cout << "Testing sort on PS state data...\nTop ten states sorted on Highest Number of Police Shootings:";
  for (int i = 0; i < 10; i++)
  {
    cout << endl
         << states[i].first;
    cout << "\nTotal population: " << allComboDemogData[states[i].first]->getPop();
    cout << "\nPolice shooting incidents: " << states[i].second.getNumberOfCases();
    cout << fixed << setprecision(2) << "\nPercent below poverty: " << allComboDemogData[states[i].first]->getPopBelowPoverty();
  }
  cout << "\n Full listings for top 3 states with most police shooting data:";
  for (int i = 0; i < 3; i++)
  {
    cout << "\nState Info: ";
    cout << states[i].first << endl;
    cout << states[i].second << endl;
    cout << "\nPolice shooting incidents:" << *(allComboPoliceData[states[i].first]);
  }
}

//sort and report the top ten states with largest population below poverty
void dataAQ::reportTopTenStatesBP()
{
  vector<pair<string, demogCombo>> states;
  for (auto &s : allComboDemogData)
  {
    states.push_back(make_pair(s.first, *(s.second)));
  }
  sort(states.begin(), states.end(), [](pair<string, demogCombo> &lhs, pair<string, demogCombo> &rhs) {
    return (lhs.second.getPopBelowPoverty() > rhs.second.getPopBelowPoverty());
  });
  cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:";
  for (int i = 0; i < 10; i++)
  {
    cout << endl;
    cout << states[i].first;
    cout << "\nTotal population: " << states[i].second.getPop();
    cout << fixed << setprecision(2) << "\nPercent below poverty: " << states[i].second.getPopBelowPoverty();
    cout << "\nPolice shooting incidents: " << allComboPoliceData[states[i].first]->getNumberOfCases();
  }
  cout << "\n Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:";
  for (int i = 0; i < 3; i++)
  {
    cout << "\nState Info: ";
    cout << states[i].first;
    cout << states[i].second;
    cout << "\nPolice shooting incidents:" << *(allComboPoliceData[states[i].first]);
  }
}

/* print all combo data */
std::ostream &operator<<(std::ostream &out, const dataAQ &theAnswers)
{
  for (auto const &entry : theAnswers.allComboDemogData)
  {
    out << "key: " << entry.first << endl;
    out << *(entry.second) << "\n";
  }

  for (auto const &entry : theAnswers.allComboPoliceData)
  {
    out << "key: " << entry.first << endl;
    out << *(entry.second) << "\n";
  }

  return out;
}

void dataAQ::comboReport(double thresh)
{
  std::vector<shared_ptr<regionData>> pileData;
  for (const auto &obj : allComboDemogData)
  {
    if (obj.second->getHSup() > thresh)
    {
      pileData.push_back(obj.second);
      pileData.push_back(allComboPoliceData[obj.first]);
    }
  }

  visitorReport report;

  for (const auto &obj : pileData)
  {
    obj->accept(report);
  }
}