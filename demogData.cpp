#include "demogData.h"

void demogData::accept(class Visitor &v) { v.visit(shared_from_this()); }
