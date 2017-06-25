//
// Created by orerez on 25/06/2017.
//

#ifndef NEW_EX4_KIDSROOM_H
#define NEW_EX4_KIDSROOM_H

#include "EscapeRoomWrapper.h"

class kidsRoom : public mtm::escaperoom::EscapeRoomWrapper {
    int ageLimit;
public:

    // Constructs a new kids Escape Room with the specified data.
    //
    // @param name : the name of the escape room.
    // @param escapeTime : the maximal escape time allowed in the room.
    // @param level : the level of the escape room.
    // @param maxParticipants : the maximal participants allowed in the room.
    // @param ageLimit : The number of scary Enigmas in the room.
    // @param numOfScaryEnigmas : The number of scary Enigmas in the room.
    // @throws EscapeRoomMemoryProblemException in case of creation failure.
    // The rest of the room's data is initialized as described in the exercise sheet.
    //
    kidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants,
              const int& ageLimit):
            EscapeRoomWrapper(name,escapeTime,level,maxParticipants),
            ageLimit(ageLimit){}

    ~kidsRoom()= default;

    //the method changes the age limit according to the limit given.
    //
    // @param limit the new age limit of the room.
    //
    void setNewAgeLimit(const int& limit);

    // returns the room's age limit.
    //
    // @throws kidsRoomIllegalAgeLimit if age limit is less then 0;
    // @return the room age limit
    //
    int getAgeLimit() const;


};

std::ostream& operator<<(std::ostream &output, const kidsRoom &room);

#endif //NEW_EX4_KIDSROOM_H
