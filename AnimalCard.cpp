//
//  AnimalCard.cpp
//  Five Animals
//

#include <iostream>
#include "AnimalCard.hpp"

//*************************No split**************************//
NoSplit::NoSplit(){}

NoSplit::NoSplit(std::string animal) {
    m_animals[0][0] = m_animals[0][1] = m_animals[1][0] = m_animals[1][1] = animal;
    m_cardOrientation = Orientation::UP;
    m_printState = EvenOdd::ODD;
}

void NoSplit::setOrientation( Orientation cardOrientation){
    m_cardOrientation = cardOrientation;
}

void NoSplit::setRow( EvenOdd printState ){
    if (printState != EvenOdd::DEFAULT) {
        m_printState = printState;
    }
}

EvenOdd NoSplit::getRow(){
    return m_printState;
};

void NoSplit::printRow(std::ostream& out, EvenOdd e_o) const {
    //Orientation of card doesn't matter since there is only on animal on the card
    std::cout << m_animals[0][0] << m_animals[0][0];
}

std::string NoSplit::getQuadrant(int, int){
    return m_animals[0][0];
}
//*************************Split Two**************************//

/*There is two possible types SplitTwo cards
 
 *******  *******
 *     *  *  *  *
 *******  *  * 2*
 *  1  *  *  *  *
 *******  *******
 
 */

SplitTwo::SplitTwo(){};
SplitTwo::SplitTwo(std::string animal_one, std::string animal_two, int ctype){
    
    if (ctype == 1) {
        m_animals[0][0] = m_animals[0][1] = animal_one;
        m_animals[1][0] = m_animals[1][1] = animal_two;
    }else{
        m_animals[0][0] = m_animals[1][0] = animal_one;
        m_animals[0][1] = m_animals[1][1] = animal_two;
    }
    
    m_cardOrientation = Orientation::UP;
    m_printState = EvenOdd::ODD;
}

void SplitTwo::setOrientation( Orientation cardOrientation ){
    
    m_cardOrientation = cardOrientation;
}
void SplitTwo::setRow( EvenOdd printState ){
    if (printState != EvenOdd::DEFAULT) {
        m_printState = printState;
    }
}

EvenOdd SplitTwo::getRow(){
    return m_printState;
}

void SplitTwo::printRow(std::ostream& out, EvenOdd e_o) const {
    
    if (m_cardOrientation == Orientation::UP ) {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[0][0] << m_animals[0][1];
            
        }else{
            
            out << m_animals[1][0] << m_animals[1][1];
        }
    }
    
    else {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[1][1] << m_animals[1][0];
            
        }else{
            
            out << m_animals[0][1] << m_animals[0][0];
        }
        
    }
}

std::string SplitTwo::getQuadrant(int row, int column){
    
    if (m_cardOrientation == Orientation::UP ) {
        
        return m_animals[row][column];
        
    } else {
        
        return m_animals[!row][!column];
    }
}
//*************************Split Three**************************//

/*There is two unique types SplitThree cards
 
 *******  *******
 *  |  *  *  *  *
 *******  *--* 2*
 *  1  *  *  *  *
 *******  *******
 
 */

SplitThree::SplitThree(){}

SplitThree::SplitThree(std::string animal_one, std::string animal_two, std::string animal_three, int ctype){
    
    if (ctype == 1) {
        m_animals[0][0] = animal_one;
        m_animals[0][1] = animal_two;
        m_animals[1][0] = m_animals[1][1] = animal_three;
    }else{
        m_animals[0][0] = animal_one;
        m_animals[0][1] = m_animals[1][1] = animal_two;
        m_animals[1][0] = animal_three;
    }
    
    m_cardOrientation = Orientation::UP;
    m_printState = EvenOdd::ODD;
}

void SplitThree::setOrientation( Orientation cardOrientation ){
    
    m_cardOrientation = cardOrientation;
}
void SplitThree::setRow( EvenOdd printState ){
    if (printState != EvenOdd::DEFAULT) {
        m_printState = printState;
    }
}

EvenOdd SplitThree::getRow(){
    return m_printState;
}

void SplitThree::printRow(std::ostream& out, EvenOdd e_o) const {
    
    if (m_cardOrientation == Orientation::UP ) {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[0][0] << m_animals[0][1];
            
        }else{
            
            out << m_animals[1][0] << m_animals[1][1];
        }
    }
    
    else {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[1][1] << m_animals[1][0];
            
        }else{
            
            out << m_animals[0][1] << m_animals[0][0];
        }
        
    }
}

std::string SplitThree::getQuadrant(int row, int column){
    
    if (m_cardOrientation == Orientation::UP ) {
        
        return m_animals[row][column];
        
    } else{
        
        return m_animals[!row][!column];
    }
}

//*************************Split Four**************************//

/*There is one unique type SplitFour card
 
 *******
 *  |  *
 *******
 *  |  *
 *******
 
 */

SplitFour::SplitFour(){}

SplitFour::SplitFour(std::string animal_one, std::string animal_two, std::string animal_three, std::string animal_four){
    
    m_animals[0][0] = animal_one;
    m_animals[0][1] = animal_two;
    m_animals[1][0] = animal_three;
    m_animals[1][1] = animal_four;
    m_cardOrientation = Orientation::UP;
    m_printState = EvenOdd::ODD;
}

void SplitFour::setOrientation( Orientation cardOrientation ){
    
    m_cardOrientation = cardOrientation;
}
void SplitFour::setRow( EvenOdd printState ){
    if (printState != EvenOdd::DEFAULT) {
        m_printState = printState;
    }
}

EvenOdd SplitFour::getRow(){
    return m_printState;
}

void SplitFour::printRow(std::ostream& out, EvenOdd e_o) const{
    
    if (m_cardOrientation == Orientation::UP ) {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[0][0] << m_animals[0][1];
            
        }else{
            
            out << m_animals[1][0] << m_animals[1][1];
        }
    }
    
    else {
        
        if (e_o == EvenOdd::ODD) {
            
            out << m_animals[1][1] << m_animals[1][0];
            
        }else{
            
            out << m_animals[0][1] << m_animals[0][0];
        }
        
    }
}

std::string SplitFour::getQuadrant(int row, int column){
    
    if (m_cardOrientation == Orientation::UP ) {
        
        return m_animals[row][column];
        
    } else{
        
        return m_animals[!row][!column];
    }
}

//*************************Joker**************************//
Joker::Joker(): NoSplit("j"){}

//*************************Joker**************************//
StartCard::StartCard(): NoSplit("c"){}
StartCard::StartCard(std::string animal): NoSplit(animal){}
