//
//  AnimalFactory.hpp
//  Five Animals
//

#ifndef AnimalFactory_hpp
#define AnimalFactory_hpp

#include <memory>
#include <algorithm>
#include <random>
#include <iostream>

#include "AnimalCard.hpp"
#include "Deck.hpp"
#include "ActionCards.hpp"


class AnimalFactory {
    
private:
    Deck <std::shared_ptr<AnimalCard> > deck;
    AnimalFactory();
    
public:
    static AnimalFactory* getFactory();
    Deck<std::shared_ptr<AnimalCard> > getDeck();
};

#endif /* AnimalFactory_hpp */