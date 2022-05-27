
#include "Gene.h"
#include "Connection.h"

using namespace NeatSquared;
Connection::Connection(int innovationNumber, int from, int to, float weight, bool enabled) : Gene(innovationNumber),
                                                                                              from(from), to(to),
                                                                                              weight(weight),
                                                                                              enabled(enabled) {}
