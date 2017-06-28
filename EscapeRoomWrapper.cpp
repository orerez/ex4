//
// Created by liav on 18/06/2017.
//

#include "EscapeRoomWrapper.h"
#include "EscapeRoom.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime, const int &level, const int &maxParticipants) {
    room=escapeRoomCreate(name,escapeTime,maxParticipants,level);
    if(this->room==NULL){
        EscapeRoomMemoryProblemException escapeRoomMemoryProblemException;
        throw escapeRoomMemoryProblemException;
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) {
    room=escapeRoomCreate(name,60,6,level);
    if(this->room==NULL){
        EscapeRoomMemoryProblemException escapeRoomMemoryProblemException;
        throw escapeRoomMemoryProblemException;
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper &room) {
    if (room.room == nullptr) {
        EscapeRoomMemoryProblemException escapeRoomMemoryProblemException;
        throw escapeRoomMemoryProblemException;
    }
    this->room = escapeRoomCopy(room.room);
    this->Enigmas = room.Enigmas;
}

void EscapeRoomWrapper::addEnigma (const Enigma& enigma){
    this->Enigmas.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma &enigma) {
    if(this->Enigmas.empty()){
        EscapeRoomNoEnigmasException exception;
        throw exception;
    }
    bool found=false;
    std::vector<Enigma>::iterator it = this->Enigmas.begin();
    int size = (int)this->Enigmas.size();
    for (int i =0; i<size; ++i)
    {
        if(*it==enigma){
            this->Enigmas.erase(it);
            found= true;
        }
    }

    if(!found){
        EscapeRoomEnigmaNotFoundException exception;
        throw exception;
    }

}

std::string EscapeRoomWrapper::getName() const {
    char* room_name_tmp=roomGetName(this->room);
    std::string room_name= room_name_tmp;
    free(room_name_tmp);
    return room_name;
}

int EscapeRoomWrapper::getMaxTime() const{
    return roomGetMaxTime(room);
}

int EscapeRoomWrapper::getMaxParticipants() const{
    return roomGetMaxParticipants(room);
}

std::vector<Enigma>& EscapeRoomWrapper::getAllEnigmas(){
    return this->Enigmas;
}

Enigma EscapeRoomWrapper::getHardestEnigma(){
    if(this->Enigmas.empty()){
        EscapeRoomNoEnigmasException exception;
        throw exception;
    }

    int max_difficulty=this->Enigmas[0].getDifficulty();
    int size = (int)this->Enigmas.size();
    for (int i =0; i<size; ++i)
        max_difficulty = this->Enigmas[i].getDifficulty()>max_difficulty ?
                         this->Enigmas[i].getDifficulty() : max_difficulty;

    for (int j = 0; j < size; ++j) {
        if(this->Enigmas[j].getDifficulty()==max_difficulty)
            return this->Enigmas[j];
    }

    return this->Enigmas[0];
}

int EscapeRoomWrapper::level() const{
    return getLevel(room);
}

RoomType EscapeRoomWrapper::getType() const {
    return BASE_ROOM;
}

double EscapeRoomWrapper::getRate() const{
    return roomGetRate(room);
}

void EscapeRoomWrapper::rate(const int& newRate) const{
    updateRate(room,newRate);
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
    escapeRoomDestroy(this->room);
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper &room){
    if(this==&room)
        return *this;
    escapeRoomDestroy(this->room);
    this->room=escapeRoomCopy(room.room);
    return *this;
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const{
    return areEqualRooms(this->room,room.room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const{
    return !(this->room==room.room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const{
    return isBiggerRoom(this->room,room.room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const{
    return room>*this;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const EscapeRoomWrapper& room){
    output <<room.getName()<<" ("<< room.getMaxTime()<<"/"<<room.level()
           <<"/"<<room.getMaxParticipants()<<")";
    return output;
}

