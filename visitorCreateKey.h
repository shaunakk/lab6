#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>

using namespace std;

class visitorCreateKey : public Visitor
{
public:
  visitorCreateKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>))
  {
    demogFunc = df;
    psFunc = psf;
  }

  void visit(shared_ptr<demogData> obj)
  {
    size_t pos = obj->getName().find(" County");
    string keyname = obj->getName();
    if (pos != string::npos)
      keyname.erase(pos, 7);
    keyname += obj->getState();
    demogToKeyMap[keyname] = demogFunc(obj);
  }

  void visit(shared_ptr<psData> obj)
  {
    size_t pos = obj->getName().find(" County");
    string keyname = obj->getName();
    if (pos != string::npos)
      keyname.erase(pos, 7);
    keyname += obj->getState();
    psToKeyMap[keyname] = psFunc(obj);
  }
  void visit(shared_ptr<psCombo> obj)
  {
  }

  //add getters as needed
  map<string, string> getDemogRegionToKey()
      const
  {
    return demogToKeyMap;
  }
  map<string, string> getPsRegionToKey()
      const
  {
    return psToKeyMap;
  }

private:
  //the function pointers to the key functions
  string (*demogFunc)(shared_ptr<demogData>);
  string (*psFunc)(shared_ptr<psData>);

  //ADD data to map between location and key
  map<string, string> demogToKeyMap;
  map<string, string> psToKeyMap;
};

#endif