#ifndef VCOMBOKP_H
#define VCOMBOKP_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>

class visitorCombineKeyPS : public visitorCombine
{
public:
  visitorCombineKeyPS(string (*psf)(shared_ptr<psData>), const std::map<string, string> &mapPSToKey)
  {
    psFunc = psf;
    //probably want to assert the map is legit and store it
    assert(mapPSToKey.size() > 0);
    psToKeyMap = mapPSToKey;
  }

  //based on stored key
  void visit(shared_ptr<demogData> obj)
  {
  }

  //store based on function
  void visit(shared_ptr<psData> obj)
  {
    size_t pos = obj->getName().find(" County");
    string keyname = obj->getName();
    if (pos != string::npos)
      keyname.erase(pos, 7);
    keyname += obj->getState();
    string key = psToKeyMap[keyname];
    if (allComboPoliceData.count(key) == 0)
      allComboPoliceData[key] = make_shared<psCombo>(obj->getState());
    allComboPoliceData[key]->addIncident(*obj);
  }
  void visit(shared_ptr<psCombo> obj)
  {
    //FILL IN
  }
  void printAllCombo()
  {
    cout << endl
         << endl
         << "PSDATA KEYS: " << endl;
    for (auto d : allComboPoliceData)
    {
      cout << "name: " << d.first << endl;
      d.second->toString(cout);
      cout << endl;
    }
  }

private:
  //the function pointers to the key functions
  string (*psFunc)(shared_ptr<psData>);

  //data to help region to key for mapping between the two dataTypes
  map<string, string> psToKeyMap;
};

#endif