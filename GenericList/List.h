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
    const T& getInfo() const;
    node* getNext() const;
    node* getPrevious() const;
    void setEnd(bool var);
    void setNext(node* next);
    void setPrevious(node* previous);
    void setInfo(T info);
    const bool isEnd() const;
};


template <class T>
class List{
    int size;
    node<T>* first;
    node<T>* last;
public:
    List();
    List(const List& list)= delete;
    ~List();
    List& operator=(const T& List)= delete;
    int getSize();
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    void insert(const T& data, Iterator iterator);
    void insert(const T& data);
    void remove(Iterator iterator);
    bool operator==(const List<T>& list) const;
    bool operator!=(const List<T>& list) const;

};

template <class T>
class List<T>::Iterator{
    friend class List<T>;
    node<T>* index;

public:
    Iterator(node<T>* node);
    Iterator(const Iterator& iterator)= default;
    const T& operator*() const;
    const node<T> getNode() const ;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    Iterator& operator=(const Iterator& iterator);
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
const T& node<T>::getInfo() const{
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
const bool node<T>::isEnd() const {
    return this->end;
}

// << ----- >> End of node class << ------ >> //


// << ----- >>  Templates for Iterator class << ------ >> //
template <class T>
const T& List<T>::Iterator::operator*() const {
    if(this== nullptr){
        ElementNotFound error;
        throw(error);
    }
    return index->getInfo();
}

template <class T>
List<T>::Iterator::Iterator(node<T> *node) {
    this->index=node;
}

template <class T>
const node<T> List<T>::Iterator::getNode() const{
    return *index;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){
    index=index->getNext();
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int){
    List<T>::Iterator result(index);
    index=index->getNext();
    return result;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator--(){
    index=index->getPrevious();
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int){
    List<T>::Iterator result(index);
    index=index->getPrevious();
    return result;
}

template <class T>
bool List<T>::Iterator::operator==(const Iterator& it) const{
    return (this->index==it.index);
}

template <class T>
bool List<T>::Iterator::operator!=(const Iterator& it) const{
    return !(*this==it);
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& iterator){
    if(*this==iterator)
        return *this;
    this->index=iterator.index;
    return *this;
}

// << ----- >> End of Iterator class << ------ >> //


// << ----- >>  Templates for list class << ------ >> //
template <class T>
List<T>::List() : size(0) {
    node<T>* end_of_list=new node<T>();
    end_of_list->setEnd(true);
    this->last=end_of_list;
    this->first=end_of_list;
}

template <class T>
List<T>::~List() {
    node<T>* tmp;
    while(!this->first->isEnd()){
        tmp=this->first;
        this->first=this->first->getNext();
        delete tmp;
    }
    tmp=this->first;
   if(tmp!= nullptr)
       delete(tmp);
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
        node<T>* debug=this->last;
        node<T>* tmp=debug->getPrevious();
        node<T>* node2=new node<T>(this->last,tmp, false,data);
        tmp->setNext(node2);
        this->last->setPrevious(node2);
        this->size++;
    }
}

template <class T>
void List<T>::insert(const T& data, Iterator iterator){
    node<T>* newNode=new node<T>(iterator.index,iterator.index->getPrevious(),false,data);
    iterator--;
    iterator.index->setNext(newNode);
    this->size++;
}

template <class T>
void List<T>::remove(Iterator iterator){
    bool found=false;
    Iterator iterator1=this->begin();
    for(iterator1=this->begin();!iterator1.index->isEnd()&&!found;iterator1++)
        if(iterator1==iterator)
            found=true;
    if(!found)
        throw ElementNotFound();
    iterator1--;
    if(this->first==iterator1.index) {
        this->first = iterator1.index->getNext();
        delete iterator.index;
        this->size--;
    }
    else {
        iterator1--;
        iterator1.index->setNext(iterator.index->getNext());
        delete iterator.index;
        this->size--;
    }
}

template <class T>
int List<T>::getSize() {
    return this->size;
}

template <class T>
typename List<T>::Iterator List<T>::begin() const {
    Iterator iterator(this->first);
    return iterator;
}

template <class T>
typename List<T>::Iterator List<T>::end() const {
    Iterator iterator(this->last);
    return iterator;
}

template <class T>
bool List<T>::operator==(const List<T>& list) const{
    Iterator iterator1=this->begin();
    Iterator iterator2=list.begin();
    while(!iterator1.index->isEnd() && !iterator2.index->isEnd()) {
        if (iterator1.index->getInfo() != iterator2.index->getInfo())
            return false;
        iterator1++;
        iterator2++;
    }
    return (iterator1.index->isEnd()&&iterator2.index->isEnd());
}

template <class T>
bool List<T>::operator!=(const List<T>& list) const {
    return !(*this==list);
}

// << ----- >> End of list class << ------ >> //




#endif //UNTITLED_LIST_H