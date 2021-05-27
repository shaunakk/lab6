#ifndef VCOMBO_H
#define VCOMBO_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitor.h"
#include <memory>
#include <map>

//The shared combo data
class visitorCombine : public Visitor
{
public:
    visitorCombine() {}

    //hust a helper to print out various fields
    void printAllCombo(int (demogData::*f1)() const, int (psCombo::*f2)() const)
    {
        cout << "" << endl;
        for (auto const &entry : allComboDemogData)
        {
            auto const key = entry.first;
            cout << "Name: " << key << endl;
            cout << "demogData: " << ((entry.second).get()->*f1)() << endl;
            if (allComboPoliceData[key])
            {
                cout << "psData: " << ((allComboPoliceData[key]).get()->*f2)() << endl;
            }
        }
    }

    shared_ptr<demogCombo> getComboDemogData(string regionName) { return allComboDemogData[regionName]; } //fill in
    shared_ptr<psCombo> getComboPoliceData(string regionName) { return allComboPoliceData[regionName]; }  //fill in

    std::map<string, shared_ptr<demogCombo>> &getComboDemog() { return allComboDemogData; } //fill in
    std::map<string, shared_ptr<psCombo>> &getComboPolice() { return allComboPoliceData; }  //fill in

public:
    std::map<string, shared_ptr<demogCombo>> allComboDemogData;
    std::map<string, shared_ptr<psCombo>> allComboPoliceData; //combo maps

    //store aggregated data here
};

#endif
