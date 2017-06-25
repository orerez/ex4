//
// Created by orerez on 24/06/2017.
//

#include "ScaryRoom.h"
#include "Exceptions.h"

void ScaryRoom::setNewAgeLimit(const int& limit){
    this->ageLimit=limit;
}

int ScaryRoom::getAgeLimit() const{
    if(this->ageLimit<0){
        mtm::escaperoom::ScaryRoomIllegalAgeLimit illegalAgeLimit;
        throw illegalAgeLimit;
    }
    return this->ageLimit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
    ++this->numOfScaryEnigmas;
}

int ScaryRoom::getNumOfScaryEnigmas() const {
    return this->numOfScaryEnigmas;
}

std::ostream& operator<<(std::ostream &output, const ScaryRoom &room) {
    output <<"Scary Room: " <<room.getName()<<" ("<< room.getMaxTime()<<"/"<<room.level()
           <<"/"<<room.getMaxParticipants()<<"/"<<room.getAgeLimit()<<")";
    return output;
}