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
void Lista<T>::adicionar(T* elemento) {
    auto no = new Node<T>(elemento);
    no->setAnterior(this->ultimo);
    this->ultimo->setProximo(no);
    this->ultimo = no;
    this->tamanho++;
}

template<class T>
void Lista<T>::adicionarEmOrdemDescendente(T* elemento) {
    if (this->vazia()) {
        this->adicionar(elemento);
        return;
    }

    auto noAtual = this->cabeca->getProximo();
    auto novoNo = new Node<T>(elemento);
    if (*elemento > *this->cabeca->getProximo()->getValor()) {
        novoNo->setProximo(noAtual);
        novoNo->getProximo()->setAnterior(novoNo);
        this->cabeca->setProximo(novoNo);
    } else {
        while (noAtual->getProximo() != nullptr
            && *noAtual->getProximo()->getValor() > *elemento) {
            noAtual = noAtual->getProximo();
        }
        novoNo->setProximo(noAtual->getProximo());
        if (noAtual->getProximo() != nullptr) {
            novoNo->getProximo()->setAnterior(novoNo);
        }
        noAtual->setProximo(novoNo);
        novoNo->setAnterior(noAtual);
    }
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

    *referenciaInicio = unirListas(a, b);
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
    slow->getProximo()->setAnterior(nullptr);
    slow->setProximo(nullptr);
}

template<class T>
Node<T>* Lista<T>::unirListas(Node<T> *a, Node<T> *b) {
    Node<T>* resultado = nullptr;

    if (a == nullptr) {
        return b;
    } else if (b == nullptr) {
        return a;
    }

    if (*a->getValor() > *b->getValor()) {
        resultado = a;
        resultado->setProximo(unirListas(a->getProximo(), b));
        resultado->getProximo()->setAnterior(resultado);
        resultado->setAnterior(nullptr);
    } else {
        resultado = b;
        resultado->setProximo(unirListas(a, b->getProximo()));
        resultado->getProximo()->setAnterior(resultado);
        resultado->setAnterior(nullptr);
    }
    return resultado;
}

template class Lista<Aluno>;
template class Lista<Curso>;
