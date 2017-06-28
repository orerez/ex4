#include <iostream>
#include <cstring>
#include "EscapeRoomWrapper.h"
#include "List.h"
#include <assert.h>
#include "Enigma.h"
#include "ScaryRoom.h"
#include "kidsRoom.h"
#include "Company.h"

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

typedef set<EscapeRoomWrapper*>::iterator Iterator;

static void PrintByType(set<EscapeRoomWrapper*> rooms_set1){
    std::cout << std::endl;
    Iterator iterator1 = rooms_set1.begin();
    int size1 = (int)rooms_set1.size();
    for (int i =0; i<size1; ++i) {
        EscapeRoomWrapper* ptrWrapper = *iterator1;
        EscapeRoomWrapper roomWrapper = *ptrWrapper;
        const ScaryRoom* scary = dynamic_cast<const ScaryRoom*>(*iterator1);
        const kidsRoom* kids = dynamic_cast<const kidsRoom*>(*iterator1);
        if(scary!= nullptr)
            std::cout<< i+1 <<") "<< *scary <<std::endl;
        else if(kids!= nullptr){
            std::cout << i+1<< ") "<<*kids << std::endl;
        } else {
            std::cout<< i+1<< ") "<< roomWrapper << std::endl;
        }
        iterator1++;
    }
}

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

static bool scaryBaseFunctions(){
    ScaryRoom room=ScaryRoom((char*)"firstRoom",50,5,4,16,7);
    std::cout<<room<<std::endl;
    if(room.getNumOfScaryEnigmas()!=7)
        return false;
    room.setNewAgeLimit(14);
    room.incNumberOfScaryEnigmas();
    if (room.getNumOfScaryEnigmas()!=8)
        return false;
    std::cout<<room<<std::endl;

    try{ room.setNewAgeLimit(-3); }
    catch(ScaryRoomIllegalAgeLimit){ std::cout<<"Illegal Age Limit!" <<std::endl; }
    std::cout<<room<<std::endl;
    return true;
}

static bool kidsBaseFunctions(){
    kidsRoom room=kidsRoom((char*)"firstRoom",50,5,4,7);
    std::cout<<room<<std::endl;
    room.setNewAgeLimit(3);
    std::cout<<room<<std::endl;
    try{
        room.setNewAgeLimit(-3);
    }
    catch(mtm::escaperoom::KidsRoomIllegalAgeLimit){
        std::cout<<"Illegal Age Limit!" <<std::endl;

    }
    std::cout<<room<<std::endl;
    return true;
}

static bool companyBaseFunctions(){
    Company company1("EscapeHere","054232211");
    company1.createRoom((char*)"anubis",60,5,3);
    Company company2("bla","blabla");
    company2 = company1;
    company1.createKidsRoom((char*)"toyLand",80,3,2,5);
    company2.createScaryRoom((char*)"elemSt",55,8,4,16,6);
    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    PrintByType(rooms_set1);
    PrintByType(rooms_set2);
    return true;
}

static bool AddRemoveEnigma(Company company1, Company company2){
    std::cout<<std::endl;
    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    set<string> elements;
    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Baskerwill("Baskerwill",(Difficulty)5,0,elements);
    rooms_set1 = company1.getAllRooms();
    company1.addEnigma(*(*(rooms_set1.begin())),LegoLand);
    company1.addEnigma(*(*(++rooms_set1.begin())),Baskerwill);
    rooms_set1=company1.getAllRooms();
    Iterator iterator = rooms_set1.begin();
    std::vector<Enigma>& enigmas = (*iterator)->getAllEnigmas();
    if(enigmas[0]!=LegoLand)
        return false;
    iterator++;
    std::vector<Enigma>& enigmas2 = (*iterator)->getAllEnigmas();
    if(enigmas2[0]!=Baskerwill)
        return false;

    if(enigmas2.size()!=1)
        return false;
    company1.removeEnigma(*(*iterator),Baskerwill);
    enigmas2 = (*iterator)->getAllEnigmas();
    if(enigmas2.size()!=0)
        return false;

    try { company1.removeEnigma(*(*(--iterator)),Baskerwill); }
    catch(CompanyRoomEnigmaNotFoundException){ std::cout<<"enigma not found!"<<std::endl; }

    try { company1.removeEnigma(*(*(++iterator)),Baskerwill); }
    catch(CompanyRoomHasNoEnigmasException){std::cout<<"no enigmas in room!"<<std::endl<<std::endl;}


    return true;
}

static bool AddRemoveItem(Company company1, Company company2){
    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Spear("Spear",(Difficulty)2);
    Enigma Tuty("FruityTuty",(Difficulty)2);

    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    company1.addEnigma(*(*(rooms_set1.begin())),LegoLand);
    company2.addEnigma( (*(*(rooms_set2.begin()))),Spear);
    company1.addEnigma( (*(*(rooms_set1.begin()))),Tuty);

    rooms_set1 = company1.getAllRooms();
    rooms_set2 = company2.getAllRooms();
    Iterator iterator1 = rooms_set1.begin();
    Iterator iterator2 = rooms_set2.begin();
    std::vector<Enigma>& enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    if(enigmasVector1[0].getNumOfElements()!=0)
        return false;
    company1.addItem((*(*iterator1)),enigmasVector1[0],"Gerbil");
    company1.addItem((*(*iterator1)),enigmasVector1[0],"Chinchila");
    company1.addItem((*(*iterator1)),enigmasVector1[0],"Chin");
    enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    if(enigmasVector1[0].getNumOfElements()!=3)
        return false;
    company1.removeItem((*(*iterator1)),enigmasVector1[0],"Chinchila");
    enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    if(enigmasVector1[0].getNumOfElements()!=2)
        return false;

    try { company1.addItem((*(*iterator2)),enigmasVector1[0],"Nambsatsul"); }

    catch(CompanyRoomNotFoundException){ std::cout<<"No such room in that company!"<<std::endl; }

    try { company1.addItem((*(*iterator1)),Spear,"Nambsatsul"); }

    catch(CompanyRoomEnigmaNotFoundException){ std::cout<<"No such enigma in that room!"<<std::endl;}

    try {  company1.removeItem((*(*iterator1)),enigmasVector1[1],"Chin"); }

    catch(CompanyRoomEnigmaHasNoElementsException){std::cout<<"There are no elements in that enigma!"<<std::endl; }

    try {  company1.removeItem((*(*iterator1)),enigmasVector1[0],"Chinchila"); }

    catch(CompanyRoomEnigmaElementNotFoundException){ std::cout<<"There is no such element in that enigma!"<<std::endl;}

    try {company1.removeItem((*(*iterator1)),Spear,"Chinchila"); }

    catch(CompanyRoomEnigmaNotFoundException){ std::cout<<"There is no such enigma in that room!"<<std::endl;}

    try {company1.removeItem((*(*iterator2)),enigmasVector1[0],"Gerbil"); }

    catch(CompanyRoomNotFoundException){ std::cout<<"There is no such room in that company!"<<std::endl;}

    return true;
}

static bool companyAddRemoveFunctions(){
    Company company1("Escape-oh","053666667");
    company1.createRoom((char*)"AlexanderMokadon",60,5,3);
    Company company2("Freddy","034342678");
    company2 = company1;
    company1.createKidsRoom((char*)"toyLand",80,3,2,5);
    company1.createRoom((char*)"Sherlock",65,7,4);
    company2.createKidsRoom((char*)"Marshmello",120,6,3,9);
    company2.createScaryRoom((char*)"elemSt",55,8,4,16,6);
    EscapeRoomWrapper Holand((char*)"Guttentag",50,7,8);
    EscapeRoomWrapper ElemSt2((char*)"elemSt",55,8,4);

    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();

    PrintByType(rooms_set1);
    PrintByType(rooms_set2);

    company1.removeRoom(*(*(rooms_set1.begin())));
    PrintByType( company1.getAllRooms());
    try { company2.removeRoom(Holand); }
    catch (CompanyRoomNotFoundException){ std::cout <<"room not found!"<<std::endl; }
    company2.removeRoom(ElemSt2);
    PrintByType(company2.getAllRooms());

    AddRemoveEnigma(company1,company2);

    AddRemoveItem(company1,company2);

    return true;
}

static bool companyGetPrintFunctions(){
    Company company1("Escape-oh","053666667");
    company1.createRoom((char*)"AlexanderMokadon",60,5,3);
    Company company2("Freddy","034342678");
    company2 = company1;
    company2.createScaryRoom((char*)"Alien",40,3,5,15,5);
    company1.createKidsRoom((char*)"toyLand",80,3,2,5);
    company1.createRoom((char*)"Sherlock",65,7,4);
    company2.createKidsRoom((char*)"Marshmello",120,6,3,9);
    company2.createScaryRoom((char*)"elemSt",55,8,4,16,6);
    company2.createScaryRoom((char*)"Jaws",67,6,7,18,10);

    set<EscapeRoomWrapper*> scary_room_company2 = company2.getAllRoomsByType(mtm::escaperoom::SCARY_ROOM);
    set<EscapeRoomWrapper*> kids_room_company1 = company1.getAllRoomsByType(mtm::escaperoom::KIDS_ROOM);
    set<EscapeRoomWrapper*> base_room_company1 = company1.getAllRoomsByType(mtm::escaperoom::BASE_ROOM);
    PrintByType(scary_room_company2);
    PrintByType(kids_room_company1);
    PrintByType(base_room_company1);

    try { company1.getRoomByName("Alien"); }
    catch(CompanyRoomNotFoundException){std::cout<<"There is no room with such name in company!"<<std::endl;}

    EscapeRoomWrapper* roomWrapper = company2.getRoomByName("Alien");
    if(*roomWrapper!=*(*scary_room_company2.begin()))
        return false;

    std::set<string>Items;
    string hello="hi";
    Items.insert(hello);

    const std::set<string>& Items1 =Items;


    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();

    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Tuty("FruityTuty",(Difficulty)2);
    Enigma Baskerwill("Baskerwill",(Difficulty)5,1,Items1);
    Enigma Freddy("Freddy",(Difficulty)1);

    rooms_set1 = company1.getAllRooms();
    company1.addEnigma(*(*(rooms_set1.begin())),LegoLand);
    company1.addEnigma(*(*(rooms_set1.begin())),Tuty);
    company1.addEnigma(*(*(++rooms_set1.begin())),Baskerwill);
    company2.addEnigma(*(*(++rooms_set2.begin())),Freddy);

    Iterator iterator1 = rooms_set1.begin();
    std::vector<Enigma>& enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoBoy");
    company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoGuy");
    company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoGirl");

    std::cout<<std::endl;
    std::cout<<company1<<std::endl;
    std::cout<<std::endl;
    std::cout<<company2<<std::endl;

    return true;
}

static void tests() {
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
    RUN_TEST(scaryBaseFunctions);
    RUN_TEST(kidsBaseFunctions);
    RUN_TEST(companyBaseFunctions);
    RUN_TEST(companyAddRemoveFunctions); //Don't forget to fix copy constructors !!!
    RUN_TEST(companyGetPrintFunctions);
}

int main() {
    std::cout << "Program start" << std::endl;
    tests();
    return 0;
}

