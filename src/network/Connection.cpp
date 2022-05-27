
#include "Gene.h"
#include "Connection.h"

using namespace NeatSquared;
#include "Neuron.h"
Connection::Connection(int innovationNumber, int from, int to, float weight, bool enabled) : Gene(innovationNumber),
                                                                                              from(from), to(to),
                                                                                              weight(weight),
                                                                                              enabled(enabled) {}

Connection::Connection(int innovationNumber, Neuron from, Neuron to, float weight, bool enabled): Gene(innovationNumber), weight(weight), enabled(enabled)  {
    this->from = from.innovationNumber;
    this->to = to.innovationNumber;
    from.addConnection(this);
    to.addConnection(this);
}
