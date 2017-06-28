#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include <set>

using std::set;
using std::string;

namespace mtm{
namespace escaperoom{


    typedef enum{
        EASY_ENIGMA , MEDIUM_ENIGMA , HARD_ENIGMA
    } Difficulty;

    class Enigma{
    private:
        string name;
        Difficulty difficulty;
        int numOfElements;
        set<string> elements;

    public:

        // Constructs a new Enigma with the specified data.If numOfElements is not equal to size of elements,
        // throws EnigmaIllegalSizeParamException.
        //
        // @param name : the name of the enigma.
        // @param difficulty : the difficulty of the enigma.
        // @param numOfElements : the number of elements in the enigma.
        // @param set<string>&elements : the names of the elements involved in the enigma.
        Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements,const set<string>&elements);

        // Constructs a new Enigma with the specified data, and initiates numOfElements to 0.
        //
        // @param name : the name of the enigma.
        // @param difficulty : the difficulty of the enigma.
        Enigma(const std::string& name, const Difficulty& difficulty);

        //copy constructor
        //
        //@param enigma : the enigma to be copied.
        Enigma(const Enigma& enigma)= default;

        // adds a new element to the set of elements used in the enigma.
        //
        // @param element : the name of the new element.
        void addElement(const string& element);

        // removes the given element from the set of elements, if exists.If enigma has no elements,
        // throws EnigmaNoElementsException.  Otherwise, if no element was found, throws EnigmaNoElementsException.
        //
        // @param element : the name of the new element.
        void removeElement(const string& element);


        //assignment operator
        //
        //@param enigma : the enigma to be assigned.
        Enigma& operator=(const Enigma& enigma) = default;

        // Comparison operators for Enigmas. enigmas are compared as described in
        // the exercise sheet.
        //
        // @param enigma : the right-hand side operand.
        bool operator==(const Enigma& enigma) const;
        bool operator!=(const Enigma& enigma) const;
        bool operator<(const Enigma& enigma) const;
        bool operator>(const Enigma& enigma) const;

        bool operator<=(const Enigma& enigma) const = delete;
        bool operator>=(const Enigma& enigma) const = delete;

        // method returns true if both enigmas are equaly complex.
        //definition of equaly complex is described in the exercise sheet.
        //
        //@param enigma : the enigma being compared to.
        bool areEqualyComplex(const Enigma& enigma) const;

        // return the difficulty level of the enigma.
        //
        Difficulty getDifficulty() const;

        // Prints the data of the Enigma in the following format:
        //
        //     "<name> (<Difficulty>) <number of items>"
        //
        // @param output : the output stream to which the data is printed.
        // @param enigma : the enigma whose data is printed.
        friend std::ostream& operator<<(std::ostream& output, const Enigma& enigma);

        ~Enigma()= default;

        //Function returns the name of the enigma.
        //
        string getName() const;

        // return the set of the elements used in the enigma.
        //
        const set<string>& getSetOfElements() const;

        // return the num of elements used in the enigma.
        //
        int getNumOfElements() const;


    };

    std::ostream& operator<<(std::ostream& output, const Enigma& enigma);
} // end of namespace eascaperoom
} // end of namespace mtm



#endif //ENIGMA_H
