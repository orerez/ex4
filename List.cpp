
//template <class T>
//T& node::getInfo () const {
//    T& info_reference = this->info;
//    return info_reference;
//}
//
//template <class T>
//node* node::getNext () const {
//    return this->next;
//}
//
//template <class T>
//node* node::getPrevious() const {
//    return this->previous;
//}
//
//void node::setNext(node *next) {
//    this->next=next;
//}
//
//void node::setPrevious(node *previous) {
//    this->previous=previous;
//}
//
//void node::setEnd() {
//    this->end= true;
//}
//
//template <class T>
//Iterator::Iterator(node<T> &node) {
//    this->index=&node;
//}
//
//template <class T>
//T& Iterator::operator*() {
//    if(this== nullptr){
//        ElementNotFound error;
//        throw(error);
//    }
//    return this->index->getInfo();
//}
//
//template <class T>
//Iterator<T>& Iterator::operator++() {
//    this->index=this->index->getNext();
//    return (*this->index);
//}
//
//template <class T>
//Iterator<T>& Iterator::operator--() {
//    this->index=this->index->getPrevious();
//    return (*this->index);
//}
//
//template <class T>
//Iterator<T> Iterator::operator++(int) {
//    Iterator<T> current_node = (*this->index);
//    this->index=this->index->getNext();
//    return current_node;
//}
//
//template <class T>
//Iterator<T> Iterator::operator--(int) {
//    Iterator<T> current_node = (*this->index);
//    this->index=this->index->getPrevious();
//    return current_node;
//}
//
//
//
//
//template <class T>
//List::List() {
//    this->size=0;
//    this->iterator= nullptr;
//    this->first= nullptr;
//    this->last= nullptr;
//}
//
////template <class T>
////void List::insert(const T &data) {
////    node<T> new_node(data);
////    if(size==0){
////        this->first=&new_node;
////        this->last=&new_node;
////        this->iterator;
////        size++;
////        return;
////    }
////    node<T> before_last = this->last->getPrevious();
////    before_last.setNext(&new_node);
////    new_node.setPrevious(&before_last);
////    new_node.setNext(this->last);
////    this->last->setPrevious(&new_node);
////
////}
//
////template <class T>
////Iterator::Iterator(const Iterator<T>& iterator){
////    this->index=iterator.index;
////}
//
////
////template <typename T>
////
////template <typename T>
////
////template <typename T>
//
//
//
//
//
//
//
//
//
//
