#include <utility>

#include "ListaException.hpp"

ListaException::ListaException(std::string message) : message(std::move(message)) {}

const char *ListaException::what() const noexcept {
    return this->message.c_str();
}
