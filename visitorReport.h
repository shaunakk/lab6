#ifndef VISITREP_H
#define VISITREP_H
#include <iostream>
#include <iomanip>
#include "psData.h"
#include "visitor.h"
#include "demogData.h"
#include "psData.h"
#include "psCombo.h"
using namespace std;
class visitorReport : public Visitor
{
public:
    //FILL IN
    void visit(psCombo *p)

    {
        cout << "print aggregate police shooting data\n";
        p->toString(cout);
    }
    void visit(psData *p)

    {
    }

    void visit(demogData *p)

    {
        cout << "print summary demog Data:\n";
        p->toString(cout);
    }
};

#endif
