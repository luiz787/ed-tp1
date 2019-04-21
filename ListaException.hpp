#ifndef TP1_LISTAEXCEPTION_HPP
#define TP1_LISTAEXCEPTION_HPP


#include <exception>
#include <string>

class ListaException : public std::exception {
private:
    const std::string message;
public:
    explicit ListaException(std::string);
    virtual const char* what() const noexcept;
};

#endif
