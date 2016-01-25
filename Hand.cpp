//
//  Hand.cpp
//  Five Animals
//

#include "Hand.hpp"
Hand::Hand(){}

Hand::Hand(std::shared_ptr<AnimalCard> card1, std::shared_ptr<AnimalCard> card2, std::shared_ptr<AnimalCard> card3) {
    // Add initial three animal cards to the hand
    m_hand.push_back(card1);
    m_hand.push_back(card2);
    m_hand.push_back(card3);
}

// Overload the assignment operator for Player class to use
Hand& Hand::operator=(Hand& c_hand) {
    // Check for self assignment
    if (this == &c_hand) {
        return *this;
    }
    
    // Clear the list
    m_hand.clear();
    
    std::list<std::shared_ptr<AnimalCard>>::iterator itr = c_hand.m_hand.begin();
    while (itr != c_hand.m_hand.end()) {
        m_hand.push_back(*itr);
        ++itr;
    }
    
    return *this;
}

//Add the animal card to the hand
Hand& Hand::operator+=(std::shared_ptr<AnimalCard> ac) {
    if (ac == nullptr) {
        return *this;
    }
    m_hand.push_back(ac);
    return *this;
}

//Take a card out of the hand
Hand& Hand::operator-=(std::shared_ptr<AnimalCard> ac) {
    if (m_hand.empty()) {
        throw CustomExceptions("Your hand is empty!");
    }
    bool errorFlag = true;
    std::list<std::shared_ptr<AnimalCard>>::iterator itr = m_hand.begin();
    while (itr != m_hand.end()) {
        if (*itr == ac) {
            // Don't have to readjust the iterator as we are only erasing one element
            m_hand.erase(itr);
            errorFlag = false;
            break;
        } else {
            // Increment here or it may invalidate the iterator
            ++itr;
        }
    }
    (errorFlag) ? throw CustomExceptions("You are missing a card.") : "";
    return *this;
}

std::shared_ptr<AnimalCard> Hand::operator[](int _index) {
    if (m_hand.empty()) {
        throw CustomExceptions("Your hand is empty!");
    }
    std::shared_ptr<AnimalCard> indexAt = nullptr;
    std::list<std::shared_ptr<AnimalCard>>::iterator itr = m_hand.begin();
    bool errorFlag = false;
    
    for (int i = 0; i <= _index && itr != m_hand.end(); ++i) {
        if (i == _index) {
            indexAt = *itr;
        } else if (itr == m_hand.end()) {
            errorFlag = true;
        } else {
            // Increment here or it may invalidate the iterator
            ++itr;
        }
    }
    
    (errorFlag) ? throw CustomExceptions("Out of scope.") : "";
    return indexAt;
}

int Hand::noCards() const {
    return static_cast<int>(m_hand.size());
}

