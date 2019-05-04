#ifndef TP1_LISTA_HPP
#define TP1_LISTA_HPP

#include <stdint-gcc.h>
#include <ostream>
#include "Node.hpp"

template<class T>
class Lista {
private:
    Node<T>* cabeca;
    Node<T>* ultimo;
    uint16_t tamanho;
public:
    Lista();
    Node<T>* getPrimeiro() const;
    Node<T>* getUltimo() const;
    uint16_t getTamanho() const;
    void adicionarNoFinal(T *elemento);
    void adicionarAntes(T *elemento, Node<T> *no);
    T* remover(Node<T>* no);
    bool vazia() const;
};

#endif
