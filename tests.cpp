#include <iostream>
#include <cstring>
#include "EscapeRoomWrapper.h"
#include "List.h"
#include <assert.h>
#include "Enigma.h"

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

static bool escaperoomWrapperVectorFunctions(){
    EscapeRoomWrapper room=EscapeRoomWrapper((char*)"roomName",50,4,5);
    Enigma enigma("findExit",(Difficulty)6);
    Enigma enigma2("openDoor",(Difficulty)8);
    room.addEnigma(enigma);
    room.addEnigma(enigma2);
    Enigma hardest = room.getHardestEnigma();
    if(hardest!=enigma2)
        return false;
    std::vector<Enigma>& roomEnigmas=room.getAllEnigmas();
    if(roomEnigmas.size()!=2 || roomEnigmas[0]!=enigma || roomEnigmas[1]!=enigma2)
        return false;

    room.removeEnigma(enigma);
    if(roomEnigmas.size()!=1 || roomEnigmas[0]!=enigma2)
        return false;
    try {
        room.removeEnigma(enigma);
    }
    catch(EscapeRoomEnigmaNotFoundException roomEnigmaNotFoundException){
        std::cout<<"Enigma is not in room!"<<std::endl;
    }
    room.removeEnigma(enigma2);
    if(!roomEnigmas.empty())
        return false;

    try {
        room.removeEnigma(enigma2);
    }

    catch(EscapeRoomNoEnigmasException roomNoEnigmasException){
        std::cout<<"There are no enigmas in room!"<<std::endl;
    }

    try {
        room.getHardestEnigma();
    }

    catch(EscapeRoomNoEnigmasException roomNoEnigmasException){
        std::cout<<"There are no enigmas in room!"<<std::endl;
    }

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
    set<string> elements;
    elements.insert("map");
    elements.insert("pen");
    elements.insert("clock");
    elements.insert("lock");
    elements.insert("key");
    Enigma basic("Empty",(Difficulty)3);
    basic.addElement("hat");
    basic.addElement("hat");
    if(basic.getSetOfElements().size()!=1 || basic.getNumOfElements()!=1)
        return false;
    try {
        basic.removeElement("boom");
    }

    catch(EnigmaElementNotFundException) {
        std::cout<<"Element not found!"<<std::endl;
    }
    basic.removeElement("hat");
    if(basic.getSetOfElements().size()!=0 || basic.getNumOfElements()!=0)
        return false;
    try {
        basic.removeElement("key");
    }
    catch(EnigmaNoElementsException noElementsException){
        std::cout<<"No elements in current enigma!"<<std::endl;
    }
    try {
        Enigma enigma("allan",(Difficulty)0,1,elements);
    }
    catch( EnigmaIllegalSizeParamException illegalSizeParamException){
        std::cout<<"Wrong set size!"<<std::endl;
    }
    Enigma enigma("allan",(Difficulty)0,5,elements);
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
    if (enigma.getSetOfElements()!=elements)
        return false;
    set<string> more_elements;
    more_elements.insert("budha sculpture");
    more_elements.insert("KFC Chicken");
    Enigma enigma3("bobo",(Difficulty)1,2,more_elements);
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
    node5.getNext();

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
    list1.insert("AAAAA",iterator);
    return true;
}

static void tests(){
    RUN_TEST(escaperoomWrapperBasicFunctions);
    RUN_TEST(escaperoomWrapperVectorFunctions);
    RUN_TEST(getFunctions);
    RUN_TEST(constructors);
    RUN_TEST(powerTests);
    RUN_TEST(enigmaBasicFunctions);
    RUN_TEST(nodeBasic);
    RUN_TEST(iteratorBasic);
    RUN_TEST(listBasic);
    RUN_TEST(listInsertion);
}

int Tests() {
    std::cout << "Program start" << std::endl;
    tests();
    return 0;
}