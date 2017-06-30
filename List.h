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
    /** creates a new node which contains info. previous and next are initialized as nullptr. end initialized as false.
     *
     * @param info the info to be stored in the node.
     */
    node(const T& info);
    node(const node<T>& node)= default;
    /** creates a new node with the following parameters
     *
     * @param next a pointer to the next node
     * @param prev a pointer to the previous node
     * @param end a flag which indicates whether it is the last node or not.
     * @param info the info to be stored in the node.
     */
    node(node* next,node* prev, bool end,T info);
    ~node()= default;
    /** returns the info inside the node
     *
     * @return a const refernce to info inside the node
     */
    const T& getInfo() const;
    /** returns pointer to the next node in the list
     *
     * @return the node pointed by next
     */
    node* getNext() const;
    /** returns pointer to the previous node in the list
     *
     * @return the node pointed by previous
     */
    node* getPrevious() const;
    /** sets whether the current node is the last in the list or not.
     *
     * @param var true or false
     */
    void setEnd(bool var);
    /** sets the node to point to the given node as next.
     *
     * @param next a pointer to the next node
     */
    void setNext(node* next);
    /** sets the node to point to the given node as previous.
     *
     * @param next a pointer to the next previous
     */
    void setPrevious(node* previous);
    /** sets the node's info to be the given info
     *
     * @param info: the info to be stord in node.
     */
    void setInfo(T info);
    /** checks whether this node is the end of the list
     *
     * @return true if node is last, false otherwise.
     */
    const bool isEnd() const;
};

template <class T>
class List{
    int size;
    node<T>* first;
    node<T>* last;
public:
    /** creates an empty list.
     *
     */
    List();
    List(const List& list)= delete;
    ~List();
    List& operator=(const T& List)= delete;
    /** returns the list size
     *
     * @return The integer size of the list.
     */
    int getSize();
    class Iterator;
    /** points an iterator of the list back to the beginning of the list and returns it.
     *
     * @return iterator to the beginning of the list.
     */
    Iterator begin() const;
    /** pointes an iterator of the list forwards to the end of the list and returns it.
     *
     * @return iterator to the end of the list.
     */
    Iterator end() const;
    /** inserts a new node in the specified location
     *
     * @param data content of the new node.
     * @param iterator the location where the node should be placed.
     */
    void insert(const T& data, Iterator iterator);
    /** inserts a new node in the end of the list
     *
     * @param data the content of the new node
     */
    void insert(const T& data);
    /** removes the node in the specified location of the list.
     *
     * @param iterator an iterator pointing to the node to remove.
     */
    void remove(Iterator iterator);
    bool operator==(const List<T>& list) const;
    bool operator!=(const List<T>& list) const;
    template<class Compare>
    /** sorts the list by a given criteria.
     *
     * @tparam Compare: should be a function object.
     * @param compare: a Compare type variable which contains a function that returns true if element1 is smaller than
     * element2. Notice that element types must be consistent with the the type of the list.
     */
    void sort(const Compare& compare);
    /**
     *
     * @tparam Predicate should be a function object.
     * @param predicate a Predicate type variable which contains a function that returns true if given element answers
     * certain conditions. Notice that elemen types must be consistent with the the type of the list.
     * @return
     */
    template<class Predicate>
    Iterator find(const Predicate& predicate );
};

template <class T>
class List<T>::Iterator{
    friend class List<T>;
    node<T>* index;
    /** swaps between the info of this node and to_switch
     *
     * @param to_switch the node we want to switch info with.
     */
    void swap(node<T>* to_switch);

public:
    /** creates an iterator for the list indicated by node.
     *
     * @param node pointer to the initiak iterator position.
     */
    Iterator(node<T>* node);
    Iterator(const Iterator& iterator)= default;
    const T& operator*() const;
    /** returns the node pointed by the iterator
     *
     * @return the node pointed by the iterator
     */
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
void List<T>::Iterator::swap(node<T>* to_switch){
    T tmp = index->getInfo();
    index->setInfo(to_switch->getInfo());
    to_switch->setInfo(tmp);
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
    if(iterator==this->end()){
        insert(data);
        return;
    } else {
        node<T> *newNode = new node<T>(iterator.index, iterator.index->getPrevious(), false, data);
        iterator--;
        if(iterator.index == nullptr) {
            this->first->setPrevious(newNode);
            this->first = newNode;
        }
        else
            iterator.index->setNext(newNode);
        this->size++;
    }
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
template<class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) {
    Iterator iterator1=this->begin();
    for(iterator1=this->begin();!iterator1.index->isEnd();iterator1++) {
        if(predicate(iterator1.index->getInfo()))
            return iterator1;
    }
    return this->end();
}

template <class T>
template<class Compare>
void List<T>::sort(const Compare &compare) {
    for (auto begin2 = (*this).begin(); begin2 != (--(*this).end()); ++begin2) {
        for (auto begin3 = (*this).begin(); begin3 != (--(*this).end()); ++begin3) {
            if(compare(begin3.getNode().getNext()->getInfo(),begin3.getNode().getInfo())){
                begin3.swap(begin3.getNode().getNext());
            }
        }
    }

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