#include "exceptions.hpp"

namespace sk {

Exception::Exception(const string& message) {
    this->message = message;
}

string Exception::what() {
    return message;
}

} // namespace sk
