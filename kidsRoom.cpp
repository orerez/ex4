//
// Created by orerez on 25/06/2017.
//

#include "kidsRoom.h"
#include "Exceptions.h"

void kidsRoom::setNewAgeLimit(const int& limit){
    if(limit<0){
        mtm::escaperoom::KidsRoomIllegalAgeLimit illegalAgeLimit;
        throw illegalAgeLimit;
    }
    this->ageLimit=limit;
}

int kidsRoom::getAgeLimit() const{
    return this->ageLimit;
}

std::ostream& operator<<(std::ostream &output, const kidsRoom &room) {
    output <<"Kids Room: "<<room.getName()<<" ("<< room.getMaxTime()<<"/"<<room.level()
           <<"/"<<room.getMaxParticipants()<<"/"<<room.getAgeLimit()<<")";
    return output;
}