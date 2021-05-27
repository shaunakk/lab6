#include "psData.h"

void psData::accept(class Visitor &v) { v.visit(shared_from_this()); }
