//
//  AnimalFactory.cpp
//  Five Animals
//

#include "AnimalFactory.hpp"

AnimalFactory::AnimalFactory(){
    std::string animal[] = {"b", "m", "w", "h", "d"};
    //NoSplit card creation
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <NoSplit> card(new NoSplit(animal[i]));
        deck.m_deck.push_back(card);
    }
    
    //SplitTwo card creation
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitTwo> card(new SplitTwo(animal[i], animal[(i + 1) % 5], 1));
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitTwo> card(new SplitTwo(animal[i], animal[(i + 2) % 5], 2));
        deck.m_deck.push_back(card);
    }
    
    //SplitThree card creation
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitThree> card(new SplitThree(animal[i], animal[(i + 1) % 5], animal[(i + 2) % 5], 1 ));
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitThree> card(new SplitThree(animal[i], animal[(i + 2) % 5], animal[(i + 3) % 5], 1 ));
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitThree> card(new SplitThree(animal[i], animal[(i + 3) % 5], animal[(i + 4) % 5], 2 ));
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitThree> card(new SplitThree(animal[i], animal[(i + 1) % 5], animal[(i + 3) % 5], 2 ));
        deck.m_deck.push_back(card);
    }
    
    //SplitFour card creation
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitFour> card(new SplitFour(animal[i], animal[(i + 1) % 5], animal[(i + 2) % 5], animal[(i + 3) % 5]));
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitFour> card(new SplitFour(animal[i], animal[(i + 2) % 5], animal[(i + 3) % 5], animal[(i + 4) % 5]));
        deck.m_deck.push_back(card);
    }
    
    
    for (int i = 0; i < 5; i++) {
        std::shared_ptr <SplitFour> card(new SplitFour(animal[i], animal[(i + 3) % 5], animal[(i + 2) % 5], animal[(i + 1) % 5]));
        deck.m_deck.push_back(card);
    }
    
    std::shared_ptr <Joker> card(new Joker());
    deck.m_deck.push_back(card);
    //Adding the action cards into the deck
    for (int i = 0; i < 3; i++) {
        std::shared_ptr <BearAction> card(new BearAction());
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 3; i++) {
        std::shared_ptr <HareAction> card(new HareAction());
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 3; i++) {
        std::shared_ptr <WolfAction> card(new WolfAction());
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 3; i++) {
        std::shared_ptr <DearAction> card(new DearAction());
        deck.m_deck.push_back(card);
    }
    
    for (int i = 0; i < 3; i++) {
        std::shared_ptr <MooseAction> card(new MooseAction());
        deck.m_deck.push_back(card);
    }
    //Action cards can be created and put into deck here
    
    srand(static_cast<unsigned int>(time(NULL)));
    unsigned seed = std::rand() % 100;
    std::shuffle(deck.m_deck.begin(), deck.m_deck.end(), std::default_random_engine(seed));
    
}

AnimalFactory* AnimalFactory::getFactory(){
    static AnimalFactory an;
    return &an;
}

Deck<std::shared_ptr<AnimalCard>> AnimalFactory::getDeck(){
    return deck;
}