
#include "Gene.h"
#include "Connection.h"
#include "Neuron.h"
#include "utils/RandomGenerator.h"

using namespace NeatSquared;


const float Connection::STARTING_WEIGHT = 1;
const bool Connection::STARTING_ENABLED = true;


Connection::Connection(int innovationNumber, int from, int to, float weight, bool enabled) : Gene(innovationNumber),
                                                                                             from(from), to(to),
                                                                                             weight(weight),
                                                                                             enabled(enabled),
                                                                                             lastCalculatedValue(0) {}

Connection::Connection(int innovationNumber, Neuron &from, Neuron &to, float weight, bool enabled) : Gene(
        innovationNumber), weight(weight), enabled(enabled), lastCalculatedValue(0) {
    this->from = from.innovationNumber;
    this->to = to.innovationNumber;


    from.addConnection(this);
    to.addConnection(this);
}

Connection::Connection(int innovationNumber, int from, int to) : Connection(innovationNumber, from, to, STARTING_WEIGHT,
                                                                            STARTING_ENABLED) {}

std::size_t ConnectionHasher::operator()(const Connection &connection) const {
    int x = std::min(connection.from, connection.to);
    int y = std::max(connection.from, connection.to);

    // cantor pairing function
    return ((x + y) * (x + y + 1) / 2) + y;
}

bool ConnectionEqual::operator()(const Connection &lhs, const Connection &rhs) const {
    return (lhs.from == rhs.from && lhs.to == rhs.to) || (lhs.from == rhs.to && lhs.to == rhs.from);
}
