//
//  BinaryTree.hpp
//  BinaryTree
//
//  Created by Vicente Cubells on 13/10/20.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <iostream>
#include <vector>
#include "Fecha.cpp"
#include "TreeNode.hpp"

template <class T>
class BinaryTree {
protected:
    TreeNode<T> * root = nullptr;
    
    T Top5[5];

    void clear(TreeNode<T> * );
    
    Fecha id;
    
public:
    BinaryTree() {}
    virtual ~BinaryTree();
    
    /* Insertar un nodo en el árbol */
    bool insert(T &, TreeNode<T> *);
    bool insert(TreeNode<T> *, TreeNode<T> *);
    
    bool empty() const;
    
    /* Eliminar un nodo del árbol */
    virtual TreeNode<T> * remove(T &);
    
    /* Eliminar todos los nodos del árbol */
    void clear();
    
    
    /* Recorridos de un árbol */
    void preOrden() const;
    void preOrden(TreeNode<T> *) const;

    void inOrden() const;
    void inOrden(TreeNode<T> *) const;
    
    void postOrden() const;
    void postOrden(TreeNode<T> *) const;
    
    int topN(int) ;
    int topN(TreeNode<T> *, int, int) ;
    
    void printLeaf() const;
    void printLeaf(TreeNode<T> *) const;

    void setId(Fecha);
    Fecha getId();

    T getTop(int n);

        
};

template <class T>
BinaryTree<T>::~BinaryTree()
{
    this->clear();
}

template <class T>
bool BinaryTree<T>::empty() const
{
    return this->root == nullptr;
}

/* Insertar un nodo en el árbol */
template <class T>
bool BinaryTree<T>::insert(T & value, TreeNode<T> * parent)
{
    return this->insert( new TreeNode<T>(value), parent );
}

template <class T>
bool BinaryTree<T>::insert(TreeNode<T> * node, TreeNode<T> * parent)
{
    /* Declarar variable para saber si se insertó el nodo */
    bool inserted = false;
    
    /* Verificar si el árbol está vacío */
    if (this->root == nullptr) {
        /* Establecer el nodo como raíz */
        this->root = node;
    }
    else if (parent == nullptr)
    {
        /* Insertar un nuevo nodo raiz */
        node->setLeft(root);
        root = node;
    }
    else {
        if (parent->getLeft() == nullptr) {
            parent->setLeft(node);
            inserted = true;
        }
        else if (parent->getRight() == nullptr) {
            parent->setRight(node);
            inserted = true;
            }
        else {
            inserted = insert(node, parent->getLeft() );
            if (!inserted) {
                insert(node, parent->getRight() );
            }
        }
    }
    
    return inserted;
}

/* Eliminar un nodo del árbol */
template <class T>
TreeNode<T> * BinaryTree<T>::remove(T &)
{
    return nullptr;
}

/* Eliminar todos los nodos del árbol */
template <class T>
void BinaryTree<T>::clear()
{
    this->clear(this->root);
    this->root = nullptr;
}

template <class T>
void BinaryTree<T>::clear(TreeNode<T> * node)
{
    if (node != nullptr) {
        clear( node->getLeft() );
        clear( node->getRight() );
        delete node;
    }
}

/* Recorridos de un árbol */
template <class T>
void BinaryTree<T>::preOrden() const
{
    this->preOrden( this->root );
}

template <class T>
void BinaryTree<T>::preOrden(TreeNode<T> * node) const
{
    if (node != nullptr) {
        /* Procesar el nodo */
        std::cout << *node << " ";
        
        /* Desplazarse a la izquierda */
        preOrden( node->getLeft() );
        
        /* Desplazarse a la derecha */
        preOrden( node->getRight() );
    }
}

template <class T>
void BinaryTree<T>::inOrden() const
{
    this->inOrden( this->root );
}

template <class T>
void BinaryTree<T>::inOrden(TreeNode<T> * node) const
{
    if (node != nullptr) {
        /* Desplazarse a la izquierda */
        inOrden( node->getLeft() );
        
        /* Procesar el nodo */
        std::cout << *node << " ";
        
        /* Desplazarse a la derecha */
        inOrden( node->getRight() );
    }
}

template <class T>
void BinaryTree<T>::postOrden() const
{
    this->postOrden( this->root );
}

template <class T>
void BinaryTree<T>::postOrden(TreeNode<T> * node) const
{
    if (node != nullptr) {
        /* Desplazarse a la izquierda */
        postOrden( node->getLeft() );
        
        /* Desplazarse a la derecha */
        postOrden( node->getRight() );
        
        /* Procesar el nodo */
        std::cout << *node << " ";
    }
}


template <class T>
int BinaryTree<T>::topN(int n) 
{
    return this->topN( this->root, n, 0 );
}

template <class T>
int BinaryTree<T>::topN(TreeNode<T> * node, int n, int cont) 
{
    if (node != nullptr && cont < n) {
        
        /* Desplazarse a la izquierda */
        cont = topN( node->getRight(), n, cont);
         
        if (cont < n ) {  
            std::cout << *node << " (" << ++cont << ") " << endl;
            if (cont <= 5){
                Top5[cont-1] = node->getInfo();
            }
        }
        else return cont;
        
        /* Desplazarse a la derecha */
        cont = topN( node->getLeft(), n, cont);
    }
    
    return cont;
}

/* Imprimir los nodos hojas de un árbol */
template <class T>
void BinaryTree<T>::printLeaf() const
{
    this->printLeaf( this->root );
}

template <class T>
T BinaryTree<T>::getTop(int n){
    return Top5[n];
}

template <class T>
void BinaryTree<T>::setId(Fecha id_){
    id = id_;
}
template <class T>
Fecha BinaryTree<T>::getId(){
    return id;
}

#endif /* BinaryTree_hpp */