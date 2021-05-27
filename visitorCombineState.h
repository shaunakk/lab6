#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine
{
public:
    visitorCombineState() {}

    void visit(shared_ptr<demogData> obj)
    {
        if (allComboDemogData.count(obj->getState()) == 0) //If the state does exist in hash map, add more county data
        {
            allComboDemogData[obj->getState()] = make_shared<demogCombo>();
        }
        allComboDemogData[obj->getState()]->addCountyData(*obj);
    }

    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj)
    {
        if (allComboPoliceData.count(obj->getState()) == 0) //If the state does exist in hash map, add more county data
        {
            allComboPoliceData[obj->getState()] = make_shared<psCombo>(obj->getState());
        }
        allComboPoliceData[obj->getState()]->addIncident(*obj);
    }
    void visit(shared_ptr<psCombo> obj) {}

private:
    //inherited
};

#endif
