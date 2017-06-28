#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include "Exceptions.h"

using namespace mtm::ListExceptions;

template <class T>
class node{
    node* next;
    node* previous;
    bool end;
    T info;
public:
    node()= default;
    node(const T& info);
    node(const node& node)= delete;
    node(node* next,node* prev, bool end,T info);
    ~node()= default;
    T getInfo() const;
    node* getNext() const;
    node* getPrevious() const;
    void setEnd(bool var);
    void setNext(node* next);
    void setPrevious(node* previous);
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
    List(const List& list);
    ~List()= default;
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
    const List<T>* my_list;
    node<T>* index;
    Iterator(node<T>* node, List<T>* list):index(node),my_list(list){}
public:
//      Iterator(node<T>& node);
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

template <class T>
node<T>::node(const T& info):next(NULL),previous(NULL),end(false),info(info) {
}

template <class T>
node<T>::node(node* next,node* prev, bool end,T info):next(next),previous(prev),end(end),info(info){
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
void node<T>::setNext(node* next){
    this->next=next;
}

template <class T>
void node<T>::setPrevious(node* prev){
    this->previous=prev;
}

template <class T>
bool node<T>::isEnd() {
    return this->end;
}


template <class T>
T& Iterator<T>::operator*() const {
    if(this== nullptr){
        ElementNotFound error;
        throw(error);
    }
    return this->index.getInfo();
}
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
template <class T>
List<T>::List() : size(0) ,first(nullptr) {
    node<T> end_of_list(NULL);
    end_of_list.setEnd(true);
    this->last=&end_of_list;
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