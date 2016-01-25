//
//  StartStack.hpp
//  Five Animals
//

#ifndef StartStack_hpp
#define StartStack_hpp

#include <deque>
#include <memory>
#include "AnimalCard.hpp"
#include "ActionCards.hpp"

class StartStack : public AnimalCard {
private:
    std::deque<std::shared_ptr<AnimalCard>> m_startStack;
    std::shared_ptr<AnimalCard> m_curr_behav;
    std::shared_ptr<StartCard> m_startCard;
    
public:
    
    StartStack();
    StartStack& operator+=( std::shared_ptr<ActionCard> ac );
    StartStack& operator-=( std::shared_ptr<ActionCard> ac );
    std::shared_ptr<StartCard> getStartCard();
    std::shared_ptr<AnimalCard> getCurrBehaviour();
    
    // Need to be implemented, for most i think you just change the attributes of the m_curr_behavior
    // It does not matter too much because they are Technically NoSplit Cards, so orientation and what row is printed first doesn't matter
    void setOrientation( Orientation );
    void setRow( EvenOdd );
    EvenOdd getRow();
    void printRow(std::ostream& out, EvenOdd e_o) const;
    std::string getQuadrant( int, int );
};

#endif /* StartStack_hpp */
