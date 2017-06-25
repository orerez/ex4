//
// Created by orerez on 24/06/2017.
//
#include "EscapeRoomWrapper.h"


#ifndef UNTITLED_SCARYROOM_H
#define UNTITLED_SCARYROOM_H

class ScaryRoom : public mtm::escaperoom::EscapeRoomWrapper {
    int ageLimit;
    int numOfScaryEnigmas;
public:

    // Constructs a new Scary Escape Room with the specified data.
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
    ScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants,
                         const int& ageLimit, const int& numOfScaryEnigmas):
            EscapeRoomWrapper(name,escapeTime,level,maxParticipants),
            ageLimit(ageLimit),numOfScaryEnigmas(numOfScaryEnigmas){}

    ~ScaryRoom()= default;

     //the method changes the age limit according to the limit given.
     //
     // @param limit the new age limit of the room.
     //
    void setNewAgeLimit(const int& limit);

     // returns the room's age limit.
     //
     // @throws ScaryRoomIllegalAgeLimit if age limit is less then 0;
     // @return the room age limit
     //
    int getAgeLimit() const;

    // Increases number of scary enigmas in room by 1.
    //
    void incNumberOfScaryEnigmas();

    // returns the room's amount of scary enigmas.
    //
    // @return the room's amount of scary enigmas;
    //
    int getNumOfScaryEnigmas() const;

};


std::ostream& operator<<(std::ostream &output, const ScaryRoom &room);

#endif //UNTITLED_SCARYROOM_H
