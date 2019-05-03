#include "Lista.hpp"
#include "Aluno.hpp"
#include "Curso.hpp"
#include "ListaException.hpp"
#include <stdexcept>
#include <iostream>

template<class T>
Lista<T>::Lista() {
    this->cabeca = new Node<T>(nullptr);
    this->cabeca->setAnterior(nullptr);
    this->cabeca->setProximo(nullptr);
    this->ultimo = cabeca;
    this->tamanho = 0;
}

template<class T>
Node<T> *Lista<T>::getPrimeiro() const {
    return this->cabeca->getProximo();
}

template<class T>
Node<T> *Lista<T>::getUltimo() const {
    return this->ultimo;
}

template<class T>
void Lista<T>::adicionarNoFinal(T *elemento) {
    auto no = new Node<T>(elemento);
    no->setAnterior(this->ultimo);
    this->ultimo->setProximo(no);
    this->ultimo = no;
    this->tamanho++;
}

template<class T>
void Lista<T>::adicionarAntes(T *elemento, Node<T> *no) {
    auto novoNo = new Node<T>(elemento);

    auto noAnterior = no->getAnterior();
    noAnterior->setProximo(novoNo);
    novoNo->setAnterior(noAnterior);

    novoNo->setProximo(no);
    no->setAnterior(novoNo);
    this->tamanho++;
}

template<class T>
T* Lista<T>::remover(Node<T>* no) {
    if (vazia()) {
        throw ListaException("A lista está vazia.");
    }
    if (no == nullptr) {
        throw ListaException("Elemento não se encontra na lista.");
    }
    if (no->getProximo() == nullptr) {
        this->ultimo = no->getAnterior();
    } else {
        no->getProximo()->setAnterior(no->getAnterior());
    }

    no->getAnterior()->setProximo(no->getProximo());
    tamanho--;
    T* valor = no->getValor();
    delete no;
    return valor;
}

template <class T>
bool Lista<T>::vazia() const {
    return this->ultimo == this->cabeca;
}

template class Lista<Aluno>;
template class Lista<Curso>;
