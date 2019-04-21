#ifndef TP1_NODE_HPP
#define TP1_NODE_HPP

template <class T>
class Node {
private:
    T* valor;
    Node<T>* proximo;
public:
    Node();
    explicit Node(T* elemento);
    T* getValor();
    Node<T>* getProximo() const;
    void setProximo(Node<T>* no);
};

#endif
