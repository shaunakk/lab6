#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;

class visitorCombineCounty : public visitorCombine
{
public:
    visitorCombineCounty()
    {
    }

    //store demographic data by county name
    void visit(shared_ptr<demogData> obj)
    {
        size_t pos = obj->getName().find(" County");
        string keyname = obj->getName();
        if (pos != string::npos)
            keyname.erase(pos, 7);
        keyname += obj->getState();
        allComboDemogData[keyname] = make_shared<demogCombo>();
        allComboDemogData[keyname]->addCountyData(*obj);
    }

    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj)
    {
        size_t pos = obj->getCounty().find(" County");
        string keyname = obj->getCounty();
        if (pos != string::npos)
            keyname.erase(pos, 7);
        keyname += obj->getState();
        if (allComboPoliceData.count(keyname) == 0) //If the county does exist in hash map, add more incident data
        {
            allComboPoliceData[keyname] = make_shared<psCombo>(obj->getCounty());
        }
        allComboPoliceData[keyname]->addIncident(*obj);
    }
    void visit(shared_ptr<psCombo> p)
    {
    }

private:
    //only inherited data at this point
};

#endif
