#include <iostream>
#include <cstring>
#include "EscapeRoomWrapper.h"
#include "list.h"
#include "Enigma.h"
#include <assert.h>

#define RUN_TEST(test) \
do { \
printf("Running " #test "... "); \
if (test()) { \
    printf("[SUCCESS]"); \
} \
else{ \
    printf("[FAILED at %s : %d\n]", __FILE__, __LINE__); \
 } \
 printf("\n"); \
} while(0)

using namespace mtm::escaperoom;

typedef string T;

static bool escaperoomWrapperBasicFunctions(){
    EscapeRoomWrapper room=EscapeRoomWrapper((char*)"firstRoom",50,5,4);
    std::cout<<room<<std::endl;
    return true;
}

static bool getFunctions(){
    EscapeRoomWrapper room=EscapeRoomWrapper((char*)"roomName",50,4,5);
    if(room.getName()!=(std::string)"roomName") {
        return false;
    }
    if(room.getMaxParticipants()!=5)
        return false;
    if(room.getMaxTime()!=50)
        return false;
    if(room.level()!=4)
        return false;
    room.rate(5);
    room.rate(4);
    room.rate(3);
    room.rate(2);
    if(room.getRate()!=3.5)
        return false;
    std::cout<<"eliminate err"<<std::endl;
    return true;
}

static bool constructors(){
    EscapeRoomWrapper room_A=EscapeRoomWrapper((char*)"Escapus",4);
    EscapeRoomWrapper room_B=EscapeRoomWrapper(room_A);
    EscapeRoomWrapper room_C=EscapeRoomWrapper((char*)"chief",3);
    room_C=room_B;
    std::cout<<"computer printing 3 rooms which built from different constructors\n"
             <<room_A<<room_B<<room_C<<std::endl;
    return true;
}

static bool powerTests(){
    EscapeRoomWrapper room_A((char*)"thisIsName",6);
    EscapeRoomWrapper room_B((char*)"thisIs",50,5,6);
    EscapeRoomWrapper room_C((char*)"thisIs",40,5,6);
    EscapeRoomWrapper room_D((char*)"thisIs",30,5,6);
    EscapeRoomWrapper room_E((char*)"thisIs",20,5,6);
    EscapeRoomWrapper room_F((char*)"thisIs",10,5,6);
    EscapeRoomWrapper room_G((char*)"thisIs",10,4,6);
    EscapeRoomWrapper room_H((char*)"thisIs",11,3,6);
    if(room_A<room_B)
        return false;
    if(room_B<room_C||room_C<room_D||room_D<room_E||
            room_E<room_F||room_F<room_G||room_G<room_H)
        return false;
    if(!(room_A!=room_B && room_B!=room_E && room_F==room_F))
        return false;
    assert(true);
    return true;
}

static bool enigmaBasicFunctions(){
    Enigma enigma("allan",(Difficulty)0,5);
    Enigma enigma1=enigma;
    Enigma enigma2(enigma1);
    std::cout<<"compute will now print 3 identical enigma from different constructors\n"
    <<enigma<<enigma1<<enigma2<<std::endl;
    if(enigma.getName()!="allan")
        return false;
    if(enigma1.getDifficulty()!=(Difficulty)0)
        return false;
    if(enigma1!=enigma2)
        return false;
    if(!enigma1.areEqualyComplex(enigma2))
        return false;
    Enigma enigma3("bobo",(Difficulty)1,2);
    if(enigma3<enigma1||enigma3<enigma2)
        return false;
    return(enigma3!=enigma2);
}

static bool nodeBasic(){
    std::cout<<"hello"<<std::endl;
    node<T> node1, node2,node3;
    node1.setInfo("hi there");
    node2.setInfo("bro");
    node3.setInfo("dododo");
    T n1,n2,n3;
    n1=node1.getInfo();
    n2=node2.getInfo();
    n3=node3.getInfo();
    assert(n1=="hi there" && n2=="bro" && n3=="dododo");
    node1.setNext(&node2);
    node2.setNext(&node3);
    node3.setNext(&node1);

    node1.setPrevious(&node3);
    node2.setPrevious(&node1);
    node3.setPrevious(&node2);

    node1.setEnd(false);
    node2.setEnd(false);
    node3.setEnd(true);

    node<T> node4(&node2,&node1, false,"chipopotam");
    node<T> node5(node4);


    return true;
}

static bool iteratorBasic(){
    return true;
}

static bool listBasic(){
    List<T> list1;
    list1.insert("ahmad");
    list1.insert("allah");
    assert(list1.getSize()==2);
    list1.insert("davidof");
    assert(list1.getSize()==3);
    List<T>::Iterator it=list1.begin();
    List<T>::Iterator it2(it);
    const node<T> node1=it2.getNode();
    if(it != it2)
        return false;
    List<T>::Iterator it3=list1.end();
    if(it==it3)
        return false;
    T var1=*it++;
    T var2=*it;
    --it;
    T var3=*it;
    assert(var3==var1);
    it++;
    T var4=*--it;
    assert(var4==var3);
    it=list1.end();
    it=it2;
    it=it;
    return true;
}

static bool listInsertion(){
    List<T> list1;
    list1.insert("aaaaa");
    list1.insert("bbbbb");
    list1.insert("ccccc");
    List<T>::Iterator iterator=list1.begin();
    iterator++;
    List<T>::Iterator iterator2=list1.begin();
    iterator2++;
    if(iterator==iterator2)
        iterator2--;
    if (iterator2!=iterator)
        iterator--;
    List<T> list2;
    list2.insert("aaaaa");
    list2.insert("bbbbb");
    list2.insert("ccccc");
    if(list1==list2)
        std::cout<<"yay"<<std::endl;
    List<T>::Iterator iterator3=list2.begin();
    if(iterator3==iterator)
        iterator2++;
    list1.remove(iterator);
    iterator=list1.begin();
    iterator++;
    list1.remove(iterator);
    if(list1!=list2)
        std::cout<<"double yay"<<std::endl;
    return true;
}

static void tests(){
        RUN_TEST(escaperoomWrapperBasicFunctions);
        RUN_TEST(getFunctions);
        RUN_TEST(constructors);
        RUN_TEST(powerTests);
        RUN_TEST(enigmaBasicFunctions);
        RUN_TEST(nodeBasic);
        RUN_TEST(iteratorBasic);
        RUN_TEST(listBasic);
        RUN_TEST(listInsertion);
}

int main() {
    std::cout << "Program start" << std::endl;
    tests();
    return 0;
}