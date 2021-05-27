#ifndef POLICE_H
#define POLICE_H
#include "demogData.h"
#include <string>
#include <iostream>
#include <utility>
#include "regionData.h"
#include "visitor.h"

using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData : public enable_shared_from_this<psData>, public regionData
{
public:
  //add appropriate function paramaters to constructor once you add data
  psData();
  psData(string inState, string inName, int inAge, bool inMale, string inRace, string inCounty, bool inIllness, bool inFlee) : state(inState), name(inName), age(inAge), male(inMale), race(inRace), county(inCounty), signs_of_mental_illness(inIllness), flee(inFlee) {}
  void accept(class Visitor &v);

  string getState() const { return state; }
  string getName() const { return name; }
  int getAge() const { return age; }
  bool getGender() const { return male; }
  string getRace() const { return race; }
  string getCounty() const { return county; }
  bool getMental_Illness() const { return signs_of_mental_illness; }
  bool getFlee() const { return flee; }

  virtual void toString(std::ostream &out) const
  {
    out << "Police Shotting Info: " << this->getState();
    out << "\nPerson name: " << this->getName();
    out << "\nAge: " << this->getAge();
    out << "\nGender: " << this->getGender() ? "Male" : "Female";
    out << "\nRace:" << this->getRace();
    out << "\nMental Illness:" << this->getMental_Illness();
    out << "\nFleeing:" << this->getFlee();
  }

protected:
  const string state;
  const string name;
  const int age;
  const bool male;
  const string race;
  const string county;
  const bool signs_of_mental_illness;
  const bool flee;

  //add others
};

#endif
