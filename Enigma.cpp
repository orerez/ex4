//
// Created by liav on 19/06/2017.
//

#include "Enigma.h"
#include "Exceptions.h"
using namespace mtm::escaperoom;


Enigma::Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements,const set<string>& elements){
    int size =(int)elements.size();
    if(size!=numOfElements){
        EnigmaIllegalSizeParamException exception;
        throw exception;
    }
    this->name=name;
    this->difficulty=difficulty;
    this->numOfElements=numOfElements;
    this->elements=elements;
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty):name(name),difficulty(difficulty),numOfElements(0){}

void Enigma::addElement(const string& element){
  if(this->elements.find(element)==this->elements.end()){
      this->elements.insert(element);
      this->numOfElements++;
  }
}

void Enigma::removeElement(const string& element){
    if(this->elements.empty()){
        EnigmaNoElementsException exception;
        throw exception;
    }
    if(this->elements.find(element)==this->elements.end()){
        EnigmaElementNotFundException exception;
        throw exception;
    } else{
        this->elements.erase(element);
        this->numOfElements--;
    }
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

const set<string>& Enigma::getSetOfElements() const {
    const set<string>& my_elements = this->elements;
    return my_elements;
}

int Enigma::getNumOfElements() const {
    return this->numOfElements;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream &output, const Enigma &enigma) {
    output<<enigma.getName()<<" ("<<enigma.getDifficulty()<<") "<<enigma.numOfElements;
    return output;
}

