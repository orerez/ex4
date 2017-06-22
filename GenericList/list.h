#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include "Exceptions.h"

using namespace mtm::ListExceptions;

template <class T>
class node{
    node<T>* next;
    node<T>* previous;
    bool end;
    T info;
public:
    node()= default;
    node(const T& info);
    node(const node<T>& node)= default;
    node(node* next,node* prev, bool end,T info);
    ~node()= default;
    T getInfo() const;
    node* getNext() const;
    node* getPrevious() const;
    void setEnd(bool var);
    void setNext(node* next);
    void setPrevious(node* previous);
    void setInfo(T info);
    bool isEnd();
};

template <class T>
class Iterator;

template <class T>
class List{
    int size;
    node<T>* first;
    node<T>* last;
public:
    List();
    List(const List& list)= delete;
    ~List();
    List& operator=(const T& List);
    int getSize();
    Iterator<T> begin();
    Iterator<T> end();
    void insert(const T& data, Iterator<T> iterator);
    void insert(const T& data);
    void remove(Iterator<T> iterator);
};

template <class T>
class Iterator{
    friend class List<T>;
    node<T>* index;

public:
    Iterator(node<T>* node, List<T>* list);
    Iterator(node<T>& node);
    Iterator(const Iterator& iterator);
    Iterator(const List<T>* list, node<T>* node);
    T& operator*() const;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    Iterator& operator=(const Iterator& iterator)= default;
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const ;


};

// << ----- >>  Templates for node class << ------ >> //
template <class T>
node<T>::node(const T& info):next(NULL),previous(NULL),end(false),info(info) {
}

template <class T>
node<T>::node(node<T>* next,node<T>* prev, bool end,T info):next(next),previous(prev),end(end),info(info){
}

template <class T>
T node<T>::getInfo() const{
    return (this->info);
}

template <class T>
node<T>* node<T>::getNext() const{
    return this->next;
}

template <class T>
node<T>* node<T>::getPrevious() const{
    return this->previous;
}

template <class T>
void node<T>::setEnd(bool var){
    this->end=var;
}

template <class T>
void node<T>::setNext(node<T>* next){
    this->next=next;
}

template <class T>
void node<T>::setPrevious(node<T>* prev){
    this->previous=prev;
}

template <class T>
void node<T>::setInfo(T info) {
    this->info=info;
}

template <class T>
bool node<T>::isEnd() {
    return this->end;
}

// << ----- >> End of node class << ------ >> //



template <class T>
T& Iterator<T>::operator*() const {
    if(this== nullptr){
        ElementNotFound error;
        throw(error);
    }
    return this->index.getInfo();
}
/*
//
//template <class T>
//Iterator& List::Iterator<T>::operator++() {
//    this->index=this->index->getNext();
//    return *this;
//}
//
//template <class T>
//Iterator& List::Iterator<T>::operator--() {
//    this->index=this->index->getPrevious();
//    return (*this);
//}
//
//template <class T>
//Iterator List::Iterator<T>::operator++(int) {
//    Iterator current = *this;
//    ++*this;
//    return current;
//}
//
//template <class T>
//Iterator List::Iterator<T>::operator--(int) {
//    Iterator current = *this;
//    --*this;
//    return current;
//}
//
//template <class T>
//bool List::Iterator<T>::operator==(const Iterator& it) const {
//    if(List != it.List)
//        return false;
//    return this->index==it.index;
//}
//
//template <class T>
//bool List::Iterator<T>::operator!=(const Iterator &it) const {
//    return !(*this==it);
//}
//
//template <class T>
//List::Iterator<T>::Iterator(List <T> *List, node <T> *node) : List(List),node(node){}
////---------------------------------------------------------------------------------------------------
//
 */

template <class T>
List<T>::List() : size(0) {
    node<T> end_of_list;
    end_of_list.setEnd(true);
    this->last=&end_of_list;
    this->first=&end_of_list;
}

template <class T>
List<T>::~List() {
    node<T>* tmp;
    while(!this->first->isEnd()){
        tmp=this->first;
        this->first=this->first->getNext();
        delete tmp;
    }
}

template <class T>
void List<T>::insert(const T &data) {
    if (this->size==0){
        node<T>* node1=new node<T>(this->last, nullptr, false,data);
        this->first=node1;
        this->last->setPrevious(node1);
        this->size++;
    }
    else{
        node<T>* tmp=this->last->getPrevious();
        node<T>* node2=new node<T>(this->last,tmp, false,data);
        tmp->setNext(node2);
        this->last->setPrevious(node2);
        this->size++;
    }
}

//
//template <class T>
//int List<T>::getSize() {
//    return this->size;
//}
//
//Iterator List::begin() {
//    return Iterator(this,this->first);
//}
//
//Iterator List::end() {
//    return Iterator(this,this->last);
//}
//
//template <class T>
//void List::insert(const T &data, Iterator iterator) {
//    if(List!=iterator.List){
//        ElementNotFound error;
//        throw (error);
//    }
//    if(this->size==0){
//        node first_node =  node(this->last,NULL, false,data);
//        this->first=&first_node;
//        this->size++;
//        return;
//    }
//
//    bool is_first=false,is_last=false;
//    if(iterator==*this->first)
//        is_first= true;
//    if(iterator==*this->last)
//        is_last= true;
//    node new_node(iterator.index,(--iterator).index, false,data);
//    if(is_first)
//        this->first=&new_node;
//    if(is_last)
//        this->last=&new_node;
//    iterator=new_node;
//    this->size++;
//}
//
//template <class T>
//void List::insert(const T &data) {
//    List::Iterator iterator;
//    iterator = this->end();
//    this->insert(data,iterator);
//}



#endif //UNTITLED_LIST_H