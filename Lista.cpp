#include "Lista.hpp"
#include "Aluno.hpp"
#include "Curso.hpp"
#include "ListaException.hpp"
#include <stdexcept>
#include <iostream>

template<class T>
Lista<T>::Lista() {
    this->cabeca = new Node<T>();
    this->cabeca->setProximo(nullptr);
    this->ultimo = cabeca;
    this->tamanho = 0;
}

template<class T>
Node<T> *Lista<T>::getPrimeiro() {
    return this->cabeca->getProximo();
}

template<class T>
Node<T> *Lista<T>::getUltimo() {
    return this->ultimo;
}

template<class T>
void Lista<T>::adicionar(T* elemento) {
    this->ultimo->setProximo(new Node<T>(elemento));
    this->ultimo = this->ultimo->getProximo();
    this->tamanho++;
}

template<class T>
T* Lista<T>::removerProximo(Node<T>* no) {
    if (vazia()) {
        throw ListaException("A lista está vazia.");
    }
    if (no == nullptr || no->getProximo() == nullptr) {
        throw ListaException("Elemento não se encontra na lista.");
    }
    Node<T>* aux = no->getProximo();
    no->setProximo(aux->getProximo());
    if (no->getProximo() == nullptr) {
        this->ultimo = no;
    }
    T* valor = aux->getValor();
    delete aux;
    return valor;
}

template <class T>
uint16_t Lista<T>::getTamanho() const {
    return this->tamanho;
}

template <class T>
bool Lista<T>::vazia() const {
    return this->ultimo == this->cabeca;
}

template<class T>
void Lista<T>::ordenar() {
    if (this->tamanho < 2) {
        return;
    }
    Node<T>* noInicio = this->cabeca->getProximo();
    mergeSort(&noInicio);
    this->cabeca->setProximo(noInicio);
}

template<class T>
void Lista<T>::mergeSort(Node<T>** referenciaInicio) {
    Node<T>* inicio = *referenciaInicio;
    Node<T>* a;
    Node<T>* b;
    if (inicio == nullptr || inicio->getProximo() == nullptr) {
        return;
    }

    // Dividir cabeça em sublistas a e b
    dividirPelaMetade(inicio, &a, &b);

    // Recursivamente ordenar as sublistas
    mergeSort(&a);
    mergeSort(&b);

    *referenciaInicio = sortedMerge(a, b);
}

template<class T>
void Lista<T>::dividirPelaMetade(Node<T>* fonte, Node<T>** referenciaFrente, Node<T>** referenciaTras){
    Node<T>* fast = fonte->getProximo();
    Node<T>* slow = fonte;

    while(fast != nullptr) {
        fast = fast->getProximo();
        if (fast != nullptr) {
            slow = slow->getProximo();
            fast = fast->getProximo();
        }
    }

    *referenciaFrente = fonte;
    *referenciaTras = slow->getProximo();
    slow->setProximo(nullptr);
}

template<class T>
Node<T>* Lista<T>::sortedMerge(Node<T>* a, Node<T>* b) {
    Node<T>* resultado = nullptr;

    if (a == nullptr) {
        return b;
    } else if (b == nullptr) {
        return a;
    }

    if (*a->getValor() > *b->getValor()) {
        resultado = a;
        resultado->setProximo(sortedMerge(a->getProximo(), b));
    } else {
        resultado = b;
        resultado->setProximo(sortedMerge(a, b->getProximo()));
    }
    return resultado;
}

template<class T>
void Lista<T>::imprimir() {
    auto aux = this->cabeca->getProximo();
    while (aux != nullptr) {
        std::cout << *aux->getValor() << std::endl;
        aux = aux->getProximo();
    }
}

template class Lista<Aluno>;
template class Lista<Curso>;
