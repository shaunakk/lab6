#ifndef VCOMBOKD_H
#define VCOMBOKD_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>

class visitorCombineKeyDemog : public visitorCombine
{
public:
  visitorCombineKeyDemog(string (*df)(shared_ptr<demogData>), const std::map<string, string> &mapDemogToKey)
  {
    demogFunc = df;
    //probably want to assert the map is legit and store it
    assert(mapDemogToKey.size() > 0);
    demogToKeyMap = mapDemogToKey;
  }

  //just store based on function
  void visit(shared_ptr<demogData> obj)
  {
    size_t pos = obj->getName().find(" County");
    string keyname = obj->getName();
    if (pos != string::npos)
      keyname.erase(pos, 7);
    keyname += obj->getState();
    string key = demogToKeyMap[keyname];
    if (allComboDemogData.count(key) == 0)
    {
      allComboDemogData[key] = make_shared<demogCombo>();
    }

    allComboDemogData[key]->addCountyData(*obj);
  }
  //store based on demog key
  void visit(shared_ptr<psData> obj)
  {
    //FILL IN
  }
  void visit(shared_ptr<psCombo> obj)
  {
    //FILL IN
  }
  void printAllCombo()
  {
    for (auto d : allComboDemogData)
    {
      cout << "name: " << d.first << endl;
      d.second->toString(cout);
      cout << endl;
    }
  }

private:
  string (*demogFunc)(shared_ptr<demogData>);
  map<string, string> demogToKeyMap;
};

#endif