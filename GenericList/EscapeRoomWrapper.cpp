//
// Created by liav on 18/06/2017.
//

#include "EscapeRoomWrapper.h"
#include "EscapeRoom.h"

using namespace mtm::escaperoom;

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime, const int &level, const int &maxParticipants) {
    room=escapeRoomCreate(name,escapeTime,maxParticipants,level);
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) {
    room=escapeRoomCreate(name,60,6,level);
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

int EscapeRoomWrapper::level() const{
    return getLevel(room);
}

double EscapeRoomWrapper::getRate() const{
    return roomGetRate(room);
}

void EscapeRoomWrapper::rate(const int& newRate) const{
    updateRate(room,newRate);
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper &room){
    this->room=escapeRoomCopy(room.room);
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