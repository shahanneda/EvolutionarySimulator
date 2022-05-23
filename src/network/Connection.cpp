
#include "Gene.h"
#include "Connection.h"

using namespace NeatSquared;
Connection::Connection(int innovationNumber, int in, int out, float weight, bool enabled) : Gene(innovationNumber),
                                                                                              in(in), out(out),
                                                                                              weight(weight),
                                                                                              enabled(enabled) {}
