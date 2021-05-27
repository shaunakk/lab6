#ifndef VISITOR_H
#define VISITOR_H
#include <memory>

using namespace std;
class psData;
class psCombo;
class demogData;

/* a visitor can visit any of my specific data types */
class Visitor
{
  //FILL IN
public:
  virtual void visit(shared_ptr<psCombo> p) = 0;
  virtual void visit(shared_ptr<psData> p) = 0;
  virtual void visit(shared_ptr<demogData> p) = 0;
};
#endif
