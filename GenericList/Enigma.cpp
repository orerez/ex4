//
// Created by liav on 19/06/2017.
//

#include "Enigma.h"

using namespace mtm::escaperoom;

Enigma::Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements){
    this->name=name;
    this->difficulty=difficulty;
    this->numOfElements=numOfElements;
}

bool Enigma::operator==(const Enigma& enigma) const{
    return (this->name==enigma.name && this->difficulty==enigma.difficulty);
}

bool Enigma::operator!=(const Enigma& enigma) const{
    return !(*this==enigma);
}

bool Enigma::operator>(const Enigma& enigma) const{
    return (this->difficulty>enigma.difficulty);
}

bool Enigma::operator<(const Enigma& enigma) const{
    return (enigma>*this);
}

bool Enigma::areEqualyComplex(const Enigma& enigma) const{
    return (this->difficulty==enigma.difficulty &&
            this->numOfElements==enigma.numOfElements);
}

Difficulty Enigma::getDifficulty() const{
    return this->difficulty;
}

string Enigma::getName() const{
    return this->name;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream &output, const Enigma &enigma) {
    output<<enigma.getName()<<" ("<<enigma.getDifficulty()<<") "<<enigma.numOfElements;
    return output;
}