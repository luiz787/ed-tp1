#include "Node.hpp"
#include "Aluno.hpp"
#include "Curso.hpp"

template<class T>
Node<T>::Node() = default;

template<class T>
Node<T>::Node(T* elemento) {
    this->valor = elemento;
    this->anterior = nullptr;
    this->proximo = nullptr;
}

template <class T>
Node<T>* Node<T>::getProximo() const {
    return this->proximo;
}

template<class T>
void Node<T>::setProximo(Node<T> *no) {
    this->proximo = no;
}

template<class T>
Node<T> *Node<T>::getAnterior() const {
    return this->anterior;
}

template<class T>
void Node<T>::setAnterior(Node<T> *no) {
    this->anterior = no;
}

template<class T>
T* Node<T>::getValor() {
    return this->valor;
}

template class Node<Aluno>;
template class Node<Curso>;
