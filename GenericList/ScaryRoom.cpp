//
// Created by orerez on 24/06/2017.
//

#include "ScaryRoom.h"
#include "Exceptions.h"

void ScaryRoom::setNewAgeLimit(const int& limit){
    if(limit<0){
        mtm::escaperoom::ScaryRoomIllegalAgeLimit illegalAgeLimit;
        throw illegalAgeLimit;
    }
    this->ageLimit=limit;
}

int ScaryRoom::getAgeLimit() const{
    return this->ageLimit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
    ++this->numOfScaryEnigmas;
}

int ScaryRoom::getNumOfScaryEnigmas() const {
    return this->numOfScaryEnigmas;
}

RoomType ScaryRoom::getType() const{
    return SCARY_ROOM;
}

std::ostream& operator<<(std::ostream &output, const ScaryRoom &room) {
    output <<"Scary Room: " <<room.getName()<<" ("<< room.getMaxTime()<<"/"<<room.level()
           <<"/"<<room.getMaxParticipants()<<"/"<<room.getAgeLimit()<<")";
    return output;
}