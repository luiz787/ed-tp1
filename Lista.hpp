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
    void mergeSort(Node<T>** referenciaInicio);
    void dividirPelaMetade(Node<T>* fonte, Node<T>** referenciaFrente, Node<T>** referenciaTras);
    Node<T>* unirListas(Node<T> *a, Node<T> *b);
public:
    Lista();

    Node<T>* getPrimeiro() const;
    Node<T>* getUltimo() const;
    void adicionar(T* elemento);
    void adicionarEmOrdemDescendente(T* elemento);
    T* remover(Node<T>* no);
    uint16_t getTamanho() const;
    bool vazia() const;
    void ordenar();
};


#endif
