//
//  StartStack.cpp
//  Five Animals
//

#include "StartStack.hpp"

StartStack::StartStack() {
    std::shared_ptr<StartCard> _startCard(new StartCard());
    // Create the start stack with just the startcard
    m_startStack.push_front(_startCard);
    m_startCard = _startCard;
    m_curr_behav = _startCard;
}


StartStack& StartStack::operator+=( std::shared_ptr<ActionCard> ac ) {
    // Point at ac, which we will use to change the behaviour of the startstack
    m_curr_behav = ac;
    // Places a copy of the action card on top --> does this imply you can to make a copy of the card?
    // Get the animal of ac and increment the count of it
    m_startStack.push_front(ac);
    return *this;
}

StartStack& StartStack::operator-=( std::shared_ptr<ActionCard> ac ) {
    m_startStack.push_back(ac);
    return *this;
}

std::shared_ptr<StartCard> StartStack::getStartCard() {
    return m_startCard;
}

std::shared_ptr<AnimalCard> StartStack::getCurrBehaviour() {
    return  m_curr_behav;
}

void StartStack::setOrientation( Orientation _orientation) {
    m_curr_behav->setOrientation(_orientation);
}

void StartStack::setRow( EvenOdd e_o) {
    m_curr_behav->setRow(e_o);
}

EvenOdd StartStack::getRow(){
    return m_curr_behav->getRow();
}

void StartStack::printRow(std::ostream& out, EvenOdd e_o) const {
    // Card orientation should always be the same
    m_curr_behav->printRow(out, e_o);
}

std::string StartStack::getQuadrant( int row, int column){
    return m_curr_behav->getQuadrant(row, column);
}
