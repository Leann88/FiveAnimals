//
//  AnimalCard.hpp
//  Five Animals
//
//  This file also contains the definitions of the types of cards

#ifndef AnimalCard_hpp
#define AnimalCard_hpp

#include <iostream>
#include <string>

enum class Orientation {
    UP, //at 0 degrees
    DOWN //at 180 degrees
};

enum class EvenOdd {
    DEFAULT, //keep the same row as before
    EVEN,//print row 2
    ODD //print row 1
};

// Base Class
class AnimalCard {
protected:
    EvenOdd m_printState;
    std::string m_animals[2][2];
    Orientation m_cardOrientation;
    
public:
    //default constructor
    AnimalCard() {};
    
    virtual void setOrientation( Orientation ) = 0;
    virtual void setRow( EvenOdd ) = 0;
    virtual EvenOdd getRow() = 0;
    virtual void printRow( std::ostream& , EvenOdd ) const = 0;
    virtual std::string getQuadrant( int, int ) = 0;
    
    friend std::ostream& operator<<(std::ostream& out, const AnimalCard& _animalCard);
};

inline std::ostream& operator<<(std::ostream& out, const AnimalCard& _animalCard) {
    _animalCard.printRow(out, _animalCard.m_printState);
    return out;
}

class NoSplit : public AnimalCard {
    
public:
    NoSplit();
    NoSplit(std::string);
    
    void setOrientation( Orientation );
    void setRow( EvenOdd );
    EvenOdd getRow();
    // virtual keyword not necessary, since implied, but put to be clearer
    virtual void printRow( std::ostream& , EvenOdd ) const;
    std::string getQuadrant(int, int);
};

class SplitTwo : public AnimalCard {
    
public:
    SplitTwo();
    SplitTwo(std::string, std::string, int);
    
    void setOrientation( Orientation );
    void setRow( EvenOdd );
    EvenOdd getRow();
    virtual void printRow( std::ostream& , EvenOdd ) const;
    std::string getQuadrant(int, int);
};

class SplitThree : public AnimalCard {
    
public:
    SplitThree();
    SplitThree(std::string, std::string, std::string, int);
    void setOrientation( Orientation );
    void setRow( EvenOdd );
    EvenOdd getRow();
    virtual void printRow( std::ostream& , EvenOdd ) const;
    std::string getQuadrant(int, int);
};

class SplitFour : public AnimalCard {
    
public:
    SplitFour();
    SplitFour(std::string, std::string, std::string, std::string);
    void setOrientation( Orientation );
    void setRow( EvenOdd );
    EvenOdd getRow();
    virtual void printRow( std::ostream& , EvenOdd ) const;
    std::string getQuadrant(int, int);
};

class Joker : public NoSplit{
public:
    Joker();
};

class StartCard : public NoSplit{
public:
    StartCard();
    StartCard(std::string);
};

#endif /* AnimalCard_hpp */
