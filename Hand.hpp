//
//  Hand.hpp
//  Five Animals
//

#ifndef Hand_hpp
#define Hand_hpp

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <memory>
#include "AnimalCard.hpp"
#include "CustomExceptions.hpp"

class Hand {
private:
    std::list<std::shared_ptr<AnimalCard>> m_hand;
public:
    // Default constructor for use in Player
    Hand();
    Hand(std::shared_ptr<AnimalCard> card1, std::shared_ptr<AnimalCard> card2, std::shared_ptr<AnimalCard> card3);
    // Overload the assignment operator for Player class to use
    Hand& operator=(Hand& c_hand);
    Hand& operator+=(std::shared_ptr<AnimalCard> ac);
    Hand& operator-=(std::shared_ptr<AnimalCard> ac);
    std::shared_ptr<AnimalCard> operator[](int _index);
    int noCards() const;
    friend std::ostream& operator<<(std::ostream& out, const Hand& _hand);
    
};

inline std::ostream& operator<<(std::ostream& out, const Hand& _hand) {
    // Print header row
    for (int i = 0; i < _hand.noCards(); ++i) {
        out << i << "  ";
    }
    out << "\n";
    // Print cards
    
    for (std::shared_ptr<AnimalCard> const& card : _hand.m_hand) {
        card->printRow(out, EvenOdd::ODD);
        out << " ";
    }
    out << "\n";
    for (std::shared_ptr<AnimalCard> const& card : _hand.m_hand) {
        card->printRow(out, EvenOdd::EVEN);
        out << " ";
    }
    
    return out;
}

#endif /* Hand_hpp */

