//
//  Deck.hpp
//  Five Animals
//

#ifndef Deck_hpp
#define Deck_hpp

#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class Deck : public std::vector<T> {
    
public:
    std::vector<T> m_deck;
    Deck() {}
    // Draw function of the deck
    T draw() {
        T temp = nullptr;
        if (!m_deck.empty()) {
            temp = m_deck.back();
            m_deck.pop_back();
        }
        return temp;
    }
    // Return the number of card in the deck
    int deckSize() const {
        return m_deck.size();
    }
    std::vector<T> get_m_deck(){
        return m_deck;
    }
    
    // May be handy later
    friend std::ostream& operator<<(std::ostream& out, const Deck& _deck);
};

#endif /* Deck_hpp */