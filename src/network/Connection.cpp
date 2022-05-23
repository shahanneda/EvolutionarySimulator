
#include "Gene.h"
#include "Connection.h"

Connection::Connection(int innovationNumber, int in, int out, float weight, bool enabled) : Gene(innovationNumber),
                                                                                              in(in), out(out),
                                                                                              weight(weight),
                                                                                              enabled(enabled) {}
