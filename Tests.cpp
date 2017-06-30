#include <iostream>
#include <cstring>
#include "EscapeRoomWrapper.h"
#include "List.h"
#include <assert.h>
#include "Enigma.h"
#include "ScaryRoom.h"
#include "kidsRoom.h"
#include "Company.h"
#include "mtmtest.h"


using namespace mtm::escaperoom;

typedef string T;

typedef set<EscapeRoomWrapper*>::iterator Iterator;

class HasSameName{
    string name;
public:
    HasSameName(string name) : name(name) {}
    bool operator()(string node_name) const {
        return node_name == this->name;
    }
};

class StringIsSmaller{
public:
    StringIsSmaller() {}
    bool operator()(const string& string1 ,const string& string2) const {
        return string1 < string2;
    }
};

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
    ASSERT_EQUALS(hardest,enigma2);
    std::vector<Enigma>& roomEnigmas=room.getAllEnigmas();
    if(roomEnigmas.size()!=2 || roomEnigmas[0]!=enigma || roomEnigmas[1]!=enigma2)
        return false;
    ASSERT_NO_THROW(room.removeEnigma(enigma));
    if(roomEnigmas.size()!=1 || roomEnigmas[0]!=enigma2)
        return false;
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room.removeEnigma(enigma));
    ASSERT_NO_THROW(room.removeEnigma(enigma2));
    if(!roomEnigmas.empty())
        return false;
    ASSERT_THROWS(EscapeRoomNoEnigmasException, room.removeEnigma(enigma2));
    ASSERT_THROWS(EscapeRoomNoEnigmasException,room.getHardestEnigma());
    return true;
}

static bool getFunctions(){
    EscapeRoomWrapper room=EscapeRoomWrapper((char*)"roomName",50,4,5);
    ASSERT_EQUALS((std::string)"roomName",room.getName());
    ASSERT_EQUALS(5,room.getMaxParticipants());
    ASSERT_EQUALS(50,room.getMaxTime());
    ASSERT_EQUALS(4,room.level());

    ASSERT_NO_THROW(room.rate(5));
    ASSERT_NO_THROW(room.rate(4));
    ASSERT_NO_THROW(room.rate(3));
    ASSERT_NO_THROW(room.rate(2));

    ASSERT_EQUALS(3.5,room.getRate());

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
    ASSERT_NO_THROW(elements.insert("map"));
    ASSERT_NO_THROW(elements.insert("pen"));
    ASSERT_NO_THROW(elements.insert("clock"));
    ASSERT_NO_THROW(elements.insert("lock"));
    ASSERT_NO_THROW(elements.insert("key"));
    Enigma basic("Empty",(Difficulty)3);
    ASSERT_NO_THROW(basic.addElement("hat"));
    ASSERT_NO_THROW(basic.addElement("hat"));
    if(basic.getSetOfElements().size()!=1 || basic.getNumOfElements()!=1)
        return false;
    ASSERT_THROWS(EnigmaElementNotFundException,basic.removeElement("boom"));
    ASSERT_NO_THROW(basic.removeElement("hat"));
    if(basic.getSetOfElements().size()!=0 || basic.getNumOfElements()!=0)
        return false;
    ASSERT_THROWS(EnigmaNoElementsException,basic.removeElement("key"));
    try { Enigma enigma("allan",(Difficulty)0,1,elements); }
    catch( EnigmaIllegalSizeParamException illegalSizeParamException){ std::cout<<"Wrong set size!"<<std::endl; }
    Enigma enigma("allan",(Difficulty)0,5,elements);
    Enigma enigma1=enigma;
    Enigma enigma2(enigma1);
    std::cout<<"compute will now print 3 identical enigma from different constructors\n"
             <<enigma<<enigma1<<enigma2<<std::endl;
    ASSERT_EQUALS("allan",enigma.getName());
    ASSERT_EQUALS((Difficulty)0,enigma1.getDifficulty());
    ASSERT_EQUALS(enigma2,enigma1);
    ASSERT_EQUALS(true,enigma1.areEqualyComplex(enigma2));
    ASSERT_EQUALS(elements,enigma.getSetOfElements());
    set<string> more_elements;
    ASSERT_NO_THROW(more_elements.insert("budha sculpture"));
    ASSERT_NO_THROW(more_elements.insert("KFC Chicken"));
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
    ASSERT_NO_THROW(list1.insert("ahmad"));
    ASSERT_NO_THROW(list1.insert("allah"));
    assert(list1.getSize()==2);
    ASSERT_NO_THROW(list1.insert("davidof"));
    assert(list1.getSize()==3);
    List<T>::Iterator it=list1.begin();
    List<T>::Iterator it2(it);
    const node<T> node1=it2.getNode();
    ASSERT_EQUALS(it2,it);
    List<T>::Iterator it3=list1.end();
    ASSERT_NOT_EQUAL(it3,it);
    T var1=*it++;
    T var2=*it;
    --it;
    T var3=*it;
    ASSERT_EQUALS(var3,var1);
    it++;
    T var4=*--it;
    ASSERT_EQUALS(var4,var3);
    it=list1.end();
    it=it2;
    it=it;
    return true;
}

static bool listInsertion(){
    List<T> list1;
    ASSERT_NO_THROW(list1.insert("aaaaa"));
    ASSERT_NO_THROW(list1.insert("bbbbb"));
    ASSERT_NO_THROW(list1.insert("ccccc"));
    List<T>::Iterator iterator=list1.begin();
    iterator++;
    List<T>::Iterator iterator2=list1.begin();
    iterator2++;
    if(iterator==iterator2)
        iterator2--;
    if (iterator2!=iterator)
        iterator--;
    List<T> list2;
    ASSERT_NO_THROW(list2.insert("aaaaa"));
    ASSERT_NO_THROW(list2.insert("bbbbb"));
    ASSERT_NO_THROW(list2.insert("ccccc"));
    ASSERT_EQUALS(list1,list2);
    List<T>::Iterator iterator3=list2.begin();
    if(iterator3==iterator)
        iterator2++;
    ASSERT_NO_THROW(list1.remove(iterator));
    iterator=list1.begin();
    iterator++;
    ASSERT_NO_THROW(list1.remove(iterator));
    ASSERT_NOT_EQUAL(list1,list2);
    std::cout<<"double yay"<<std::endl;
    return true;
}

static bool listAdvanced(){
    List<T> list;
    ASSERT_NO_THROW(list.insert("avraham"));
    List<T>::Iterator iterator1=list.begin();
    List<T>::Iterator iterator2=list.begin();
    ASSERT_NO_THROW(list.insert("Gury"));
    ASSERT_NO_THROW(list.insert("Alfy",iterator1));
    iterator1 =(++list.begin());
    ASSERT_NO_THROW(list.insert("Dolev Shifris",iterator1));
    HasSameName IsGury("Gury");
    const HasSameName& Predicate = IsGury;
    ASSERT_NO_THROW(iterator2=list.find(Predicate));
    ASSERT_EQUALS("Gury",iterator2.getNode().getInfo());
    const StringIsSmaller compare;
    ASSERT_NO_THROW(list.sort(compare));
    iterator1= list.begin();
    ASSERT_EQUALS("Alfy",iterator1.getNode().getInfo());
    ASSERT_EQUALS("Dolev Shifris",(++iterator1).getNode().getInfo());
    ASSERT_EQUALS("Gury",(++iterator1).getNode().getInfo());
    ASSERT_EQUALS("avraham",(++iterator1).getNode().getInfo());
    return true;
}

static bool scaryBaseFunctions(){
    ScaryRoom room=ScaryRoom((char*)"firstRoom",50,5,4,16,7);
    ASSERT_EQUALS(7,room.getNumOfScaryEnigmas());
    ASSERT_NO_THROW(room.setNewAgeLimit(14));
    ASSERT_NO_THROW(room.incNumberOfScaryEnigmas());
    ASSERT_EQUALS(8,room.getNumOfScaryEnigmas());
    ASSERT_THROWS(ScaryRoomIllegalAgeLimit,room.setNewAgeLimit(-3));
    return true;
}

static bool kidsBaseFunctions(){
    kidsRoom room=kidsRoom((char*)"firstRoom",50,5,4,7);
    ASSERT_NO_THROW(room.setNewAgeLimit(3));
    ASSERT_THROWS(mtm::escaperoom::KidsRoomIllegalAgeLimit,room.setNewAgeLimit(-3));
    return true;
}

static bool companyBaseFunctions(){
    Company company1("EscapeHere","054232211");
    ASSERT_NO_THROW(company1.createRoom((char*)"anubis",60,5,3));
    Company company2("bla","blabla");
    ASSERT_NO_THROW(company2 = company1);
    ASSERT_NO_THROW(company1.createKidsRoom((char*)"toyLand",80,3,2,5));
    ASSERT_NO_THROW(company2.createScaryRoom((char*)"elemSt",55,8,4,16,6));
    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    PrintByType(rooms_set1);
    PrintByType(rooms_set2);
    return true;
}

static bool AddRemoveEnigma(Company company1, Company company2){
    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    set<string> elements;
    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Baskerwill("Baskerwill",(Difficulty)5,0,elements);
    ASSERT_NO_THROW(rooms_set1 = company1.getAllRooms());
    ASSERT_NO_THROW(company1.addEnigma(*(*(rooms_set1.begin())),LegoLand));
    ASSERT_NO_THROW(company1.addEnigma(*(*(++rooms_set1.begin())),Baskerwill));
    ASSERT_NO_THROW(rooms_set1=company1.getAllRooms());
    Iterator iterator = rooms_set1.begin();
    std::vector<Enigma>& enigmas = (*iterator)->getAllEnigmas();
    ASSERT_EQUALS(LegoLand,enigmas[0]);
    iterator++;
    std::vector<Enigma>& enigmas2 = (*iterator)->getAllEnigmas();
    ASSERT_EQUALS(Baskerwill,enigmas2[0]);
    ASSERT_EQUALS(1,enigmas2.size());
    ASSERT_NO_THROW(company1.removeEnigma(*(*iterator),Baskerwill));
    enigmas2 = (*iterator)->getAllEnigmas();
    ASSERT_EQUALS(0,enigmas2.size());
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company1.removeEnigma(*(*(--iterator)),Baskerwill));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company1.removeEnigma(*(*(++iterator)),Baskerwill));
    return true;
}

static bool AddRemoveItem(Company company1, Company company2){
    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Spear("Spear",(Difficulty)2);
    Enigma Tuty("FruityTuty",(Difficulty)2);

    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();
    ASSERT_NO_THROW(company1.addEnigma(*(*(rooms_set1.begin())),LegoLand));
    ASSERT_NO_THROW(company2.addEnigma( (*(*(rooms_set2.begin()))),Spear));
    ASSERT_NO_THROW(company1.addEnigma( (*(*(rooms_set1.begin()))),Tuty));

    rooms_set1 = company1.getAllRooms();
    rooms_set2 = company2.getAllRooms();
    Iterator iterator1 = rooms_set1.begin();
    Iterator iterator2 = rooms_set2.begin();
    std::vector<Enigma>& enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    ASSERT_EQUALS(0,enigmasVector1[0].getNumOfElements());

    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"Gerbil"));
    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"Chinchila"));
    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"Chin"));
    enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    ASSERT_EQUALS(3,enigmasVector1[0].getNumOfElements());

    ASSERT_NO_THROW(company1.removeItem((*(*iterator1)),enigmasVector1[0],"Chinchila"));
    enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    ASSERT_EQUALS(2,enigmasVector1[0].getNumOfElements());

    ASSERT_THROWS(CompanyRoomNotFoundException,company1.addItem((*(*iterator2)),enigmasVector1[0],"Nambsatsul"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company1.addItem((*(*iterator1)),Spear,"Nambsatsul"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company1.removeItem((*(*iterator1)),enigmasVector1[1],"Chin"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,
                  company1.removeItem((*(*iterator1)),enigmasVector1[0],"Chinchila"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company1.removeItem((*(*iterator1)),Spear,"Chinchila"));
    ASSERT_THROWS(CompanyRoomNotFoundException,company1.removeItem((*(*iterator2)),enigmasVector1[0],"Gerbil"));

    return true;
}

static bool companyAddRemoveFunctions(){
    Company company1("Escape-oh","053666667");
    ASSERT_NO_THROW(company1.createRoom((char*)"AlexanderMokadon",60,5,3));
    Company company2("Freddy","034342678");
    ASSERT_NO_THROW(company2 = company1);
    ASSERT_NO_THROW(company1.createKidsRoom((char*)"toyLand",80,3,2,5));
    ASSERT_NO_THROW(company1.createRoom((char*)"Sherlock",65,7,4));
    ASSERT_NO_THROW(company2.createKidsRoom((char*)"Marshmello",120,6,3,9));
    ASSERT_NO_THROW(company2.createScaryRoom((char*)"elemSt",55,8,4,16,6));
    EscapeRoomWrapper Holand((char*)"Guttentag",50,7,8);
    EscapeRoomWrapper ElemSt2((char*)"elemSt",55,8,4);

    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();

    PrintByType(rooms_set1);
    PrintByType(rooms_set2);

    ASSERT_NO_THROW(company1.removeRoom(*(*(rooms_set1.begin()))));
    PrintByType( company1.getAllRooms());
    ASSERT_NO_THROW(company2.removeRoom(ElemSt2));
    ASSERT_THROWS(CompanyRoomNotFoundException, company2.removeRoom(ElemSt2));
    PrintByType(company2.getAllRooms());

    AddRemoveEnigma(company1,company2);
    AddRemoveItem(company1,company2);
    return true;
}

static bool companyGetPrintFunctions(){
    Company company1("Escape-oh","053666667");
    ASSERT_NO_THROW(company1.createRoom((char*)"AlexanderMokadon",60,5,3));
    Company company2("Freddy","034342678");
    ASSERT_NO_THROW(company2 = company1);
    ASSERT_NO_THROW(company2.createScaryRoom((char*)"Alien",40,3,5,15,5));
    ASSERT_NO_THROW(company1.createKidsRoom((char*)"toyLand",80,3,2,5));
    ASSERT_NO_THROW(company1.createRoom((char*)"Sherlock",65,7,4));
    ASSERT_NO_THROW(company2.createKidsRoom((char*)"Marshmello",120,6,3,9));
    ASSERT_NO_THROW(company2.createScaryRoom((char*)"elemSt",55,8,4,16,6));
    ASSERT_NO_THROW(company2.createScaryRoom((char*)"Jaws",67,6,7,18,10));

    set<EscapeRoomWrapper*> scary_room_company2 = company2.getAllRoomsByType(mtm::escaperoom::SCARY_ROOM);
    set<EscapeRoomWrapper*> kids_room_company1 = company1.getAllRoomsByType(mtm::escaperoom::KIDS_ROOM);
    set<EscapeRoomWrapper*> base_room_company1 = company1.getAllRoomsByType(mtm::escaperoom::BASE_ROOM);
    PrintByType(scary_room_company2);
    PrintByType(kids_room_company1);
    PrintByType(base_room_company1);

    ASSERT_THROWS(CompanyRoomNotFoundException,company1.getRoomByName("Alien"));
    EscapeRoomWrapper* roomWrapper = company2.getRoomByName("Alien");
    ASSERT_EQUALS(*(*scary_room_company2.begin()),*roomWrapper);

    std::set<string>Items;
    string hello="hi";
    ASSERT_NO_THROW(Items.insert(hello));
    const std::set<string>& Items1 =Items;

    set<EscapeRoomWrapper*> rooms_set1 = company1.getAllRooms();
    set<EscapeRoomWrapper*> rooms_set2 = company2.getAllRooms();

    Enigma LegoLand("LegoLand",(Difficulty)3);
    Enigma Tuty("FruityTuty",(Difficulty)2);
    Enigma Baskerwill("Baskerwill",(Difficulty)5,1,Items1);
    Enigma Freddy("Freddy",(Difficulty)1);

    rooms_set1 = company1.getAllRooms();
    ASSERT_NO_THROW(company1.addEnigma(*(*(rooms_set1.begin())),LegoLand));
    ASSERT_NO_THROW(company1.addEnigma(*(*(rooms_set1.begin())),Tuty));
    ASSERT_NO_THROW(company1.addEnigma(*(*(++rooms_set1.begin())),Baskerwill));
    ASSERT_NO_THROW(company2.addEnigma(*(*(++rooms_set2.begin())),Freddy));

    Iterator iterator1 = rooms_set1.begin();
    std::vector<Enigma>& enigmasVector1 = (*(*iterator1)).getAllEnigmas();
    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoBoy"));
    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoGuy"));
    ASSERT_NO_THROW(company1.addItem((*(*iterator1)),enigmasVector1[0],"LegoGirl"));

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
    RUN_TEST(listAdvanced);
    RUN_TEST(scaryBaseFunctions);
    RUN_TEST(kidsBaseFunctions);
    RUN_TEST(companyBaseFunctions);
    RUN_TEST(companyAddRemoveFunctions);
    RUN_TEST(companyGetPrintFunctions);
}

int FinalTests() {
    std::cout << "Program start" << std::endl;
    tests();
    return 0;
}

