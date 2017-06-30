//
// Created by orerez on 25/06/2017.
//

#include "Company.h"
#include "ScaryRoom.h"
#include "kidsRoom.h"
#include "Exceptions.h"

using std::set;
using std::string;

using mtm::escaperoom::Company;

Company::Company(string name, string phoneNumber) : name(name),phone_number(phoneNumber) {}

Company::Company(const Company &company) {
    this->phone_number=company.phone_number;
    this->name=company.name;

    set<EscapeRoomWrapper*>::iterator iterator = company.room_set.begin();
    for (;iterator!=company.room_set.end();iterator++){
        try {
            EscapeRoomWrapper* ptrRoom = new EscapeRoomWrapper(*(*iterator));
            this->room_set.insert(ptrRoom);
        }
        catch(EscapeRoomMemoryProblemException){
            CompanyMemoryProblemException companyMemoryProblemException;
            throw companyMemoryProblemException;

        }
    }

}

Company::~Company() {
    set<EscapeRoomWrapper*>::iterator iterator = this->room_set.begin();
    for (;iterator!=this->room_set.end();iterator++) {
        EscapeRoomWrapper* roomWrapper= *iterator;
        delete(roomWrapper);
    }
}

void Company::createRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants) {
    try {
        EscapeRoomWrapper* ptrRoom = new EscapeRoomWrapper(name,escapeTime,level,maxParticipants);
        this->room_set.insert(ptrRoom);
    }
    catch(EscapeRoomMemoryProblemException){
        CompanyMemoryProblemException companyMemoryProblemException;
        throw companyMemoryProblemException;
    }

}

void Company::createScaryRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                              const int &ageLimit, const int &numOfScaryEnigmas) {
    try {
        ScaryRoom* ptrScary =  new ScaryRoom(name, escapeTime, level, maxParticipants, ageLimit, numOfScaryEnigmas);
        this->room_set.insert((EscapeRoomWrapper*)ptrScary);
    }
    catch(EscapeRoomMemoryProblemException){
            CompanyMemoryProblemException companyMemoryProblemException;
            throw companyMemoryProblemException;
    }
}

void Company::createKidsRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                             const int &ageLimit) {
    try {
        kidsRoom* ptrKids= new kidsRoom(name, escapeTime, level, maxParticipants, ageLimit);

        this->room_set.insert((EscapeRoomWrapper*)ptrKids);
    }
    catch(EscapeRoomMemoryProblemException){
        CompanyMemoryProblemException companyMemoryProblemException;
        throw companyMemoryProblemException;
    }
}

set<mtm::escaperoom::EscapeRoomWrapper*> Company::getAllRooms() const {
    return this->room_set;
}

void Company::removeRoom(const EscapeRoomWrapper &room) {
    set<EscapeRoomWrapper*>::iterator iterator=this->room_set.begin();
    for (;iterator!=this->room_set.end();iterator++){
        if(*(*iterator)==room){
            EscapeRoomWrapper* ptrRoom = *iterator;
            this->room_set.erase(*iterator);
            delete(ptrRoom);
            return;
        }
    }
    CompanyRoomNotFoundException roomNotFoundException;
    throw roomNotFoundException;
}

void Company::addEnigma(const EscapeRoomWrapper &room, const Enigma &enigma) {
    set<EscapeRoomWrapper*>::iterator iterator=this->room_set.begin();
    for (;iterator!=this->room_set.end();iterator++){
        if(*(*iterator)==room) {
            try {
                (*(*iterator)).addEnigma(enigma);
            }
            catch (EscapeRoomMemoryProblemException) {
                CompanyMemoryProblemException memoryProblemException;
                throw memoryProblemException;
            }
            catch (...) { throw; }
            return;
        }
    }
    CompanyRoomNotFoundException roomNotFoundException;
    throw roomNotFoundException;
}

Company& Company::operator=(const Company &company) {
    if(this==&company){
        return *this;
    }
    room_set.clear();
    phone_number=company.phone_number;
    name=company.name;

    set<EscapeRoomWrapper*>::iterator iterator = company.room_set.begin();
    for (;iterator!=company.room_set.end();iterator++){
        try {
            EscapeRoomWrapper* ptrRoom = new EscapeRoomWrapper(*(*iterator));
            this->room_set.insert(ptrRoom);
        }
        catch(EscapeRoomMemoryProblemException){
            CompanyMemoryProblemException companyMemoryProblemException;
            throw companyMemoryProblemException;
        }
    }
    return *this;
}

void Company::removeEnigma(const EscapeRoomWrapper &room, const Enigma &enigma) {
    set<EscapeRoomWrapper *>::iterator iterator = this->room_set.begin();
    for (; iterator != this->room_set.end(); iterator++) {
        if (iterator == this->room_set.end()) {
            CompanyRoomNotFoundException roomNotFoundException;
            throw roomNotFoundException;
        } else if (*(*iterator) == room) {

            try { (*(*iterator)).removeEnigma(enigma); }

            catch (EscapeRoomNoEnigmasException) {
                CompanyRoomHasNoEnigmasException companyRoomHasNoEnigmasException;
                throw companyRoomHasNoEnigmasException;
            }
            catch (EscapeRoomEnigmaNotFoundException) {
                CompanyRoomEnigmaNotFoundException roomEnigmaNotFoundException;
                throw roomEnigmaNotFoundException;
            }

            catch (...) { throw; }
        }
    }
}

void Company::addItem(const EscapeRoomWrapper &room, const Enigma &enigma, const string &element) {
    set<EscapeRoomWrapper *>::iterator iterator = this->room_set.begin();
    for (; iterator != this->room_set.end(); iterator++) {
        if (iterator == this->room_set.end()) {
            CompanyRoomNotFoundException roomNotFoundException;
            throw roomNotFoundException;
        } else if (*(*iterator) == room) {
            std::vector<Enigma> &room_enigmas = (*(*iterator)).getAllEnigmas();
            int size = (int) room_enigmas.size();
            for (int i = 0; i < size; ++i) {
                if (room_enigmas[i] == enigma) {
                    room_enigmas[i].addElement(element);
                    return;
                }
            }
            CompanyRoomEnigmaNotFoundException roomEnigmaNotFoundException;
            throw roomEnigmaNotFoundException;
        }

    }
    CompanyRoomNotFoundException roomNotFoundException;
    throw roomNotFoundException;
}

void Company::removeItem(const EscapeRoomWrapper &room, const Enigma &enigma, const string &element) {
    set<EscapeRoomWrapper *>::iterator iterator = this->room_set.begin();
    for (; iterator != this->room_set.end(); iterator++) {
        if (*(*iterator) == room) {
            std::vector<Enigma> &room_enigmas = (*(*iterator)).getAllEnigmas();
            int size = (int) room_enigmas.size();
            for (int i = 0; i < size; ++i) {
                if (room_enigmas[i] == enigma) {
                    if(room_enigmas[i].getNumOfElements()==0){
                        CompanyRoomEnigmaHasNoElementsException noElementsException;
                        throw noElementsException;
                    }
                    try { room_enigmas[i].removeElement(element); }
                    catch (EnigmaElementNotFundException){
                        CompanyRoomEnigmaElementNotFoundException notFoundException;
                        throw notFoundException;
                    }
                    catch (...){
                        throw;
                    }
                    return;
                }
            }
            CompanyRoomEnigmaNotFoundException roomEnigmaNotFoundException;
            throw roomEnigmaNotFoundException;
        }
    }
    CompanyRoomNotFoundException roomNotFoundException;
    throw roomNotFoundException;
}

set<mtm::escaperoom::EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {
    set<EscapeRoomWrapper*> set_of_type;
    set<EscapeRoomWrapper*>::iterator iterator= room_set.begin();
    int size = (int)this->room_set.size();
    for (int i =0; i<size; ++i){
        RoomType iterType =(RoomType)(*(*iterator)).getType();
        if(type==iterType)
            set_of_type.insert(&(*(*iterator)));
        iterator++;
    }
    return set_of_type;
}

mtm::escaperoom::EscapeRoomWrapper* Company::getRoomByName(const string &name) const {
    set<EscapeRoomWrapper*>::iterator iterator = room_set.begin();
    int size = (int) this->room_set.size();
    for (int i = 0; i < size; ++i) {
        if (name == (*(*iterator)).getName()) {
            return &(*(*iterator));
        }
        ++iterator;
    }
        CompanyRoomNotFoundException roomNotFoundException;
        throw roomNotFoundException;
}

namespace mtm {
    namespace escaperoom {

        std::ostream &operator<<(std::ostream &output, const Company &company) {

            set<escaperoom::EscapeRoomWrapper *>::iterator iterator = company.room_set.begin();
            std::cout << company.name << ":" << company.phone_number << std::endl;
            for (;iterator!=company.room_set.end();iterator++) {
                const ScaryRoom *scary = dynamic_cast<const ScaryRoom *>(*iterator);
                const kidsRoom *kids = dynamic_cast<const kidsRoom *>(*iterator);
                if (scary != nullptr)
                    std::cout << *scary << std::endl;
                else if (kids != nullptr) {
                    std::cout << *kids << std::endl;
                } else {
                    std::cout << *(*(iterator)) << std::endl;
                }

            }
            return output;
        }
    }
}
