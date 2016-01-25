//
//  main.cpp
//  Five Animals
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "SaveGame.hpp"
#include "Table.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "AnimalFactory.hpp"

static const std::string saveDataFileName = "saveData.txt";

int main( int narg, char *args[] ) {
    
    Deck<std::shared_ptr<AnimalCard> > deck;
    Table tab;
    int noPlayers = 0;
    Player* players = 0;
    AnimalFactory* factory = AnimalFactory::getFactory();
    deck = factory->getDeck();
    
    // Check if saved game exists
    bool savedGameExist = false;
    std::string checkForSavedGame = "";
    std::cout << "Check for saved game (y or n) (games are saved automatically)?" << std::endl;
    std::cin >> checkForSavedGame;
    if (!checkForSavedGame.compare("y")) {
        std::cout << "Checking..." << std::endl;
        // If answers yes
        std::ifstream file(saveDataFileName);
        savedGameExist = !(file.peek() == std::ifstream::traits_type::eof());
    }
    
    if (!savedGameExist) {
        std::cout << "\nStarting new game!..." << std::endl;
        bool num_of_players = false;
        //Check for valid number players, between 2 and 5
        while(!num_of_players){
            std::cout << "Number of Players? (2 to 5) (Please integers only)" << std::endl;
            std::cin >> noPlayers;
            if (noPlayers > 5 || noPlayers < 2) {
                std::cout << "Invalid number of players" << std::endl;
            }else{
                SaveGame::gameData.insert({"numPlayers", std::to_string(noPlayers)});
                num_of_players = true;
            }
        }
        
        players = new Player[noPlayers];
        for ( int pl=0; pl<noPlayers; ++pl ) {
            std::cout << "Name of player " << pl << "?" << std::endl;
            std::string name;
            std::cin >> name;
            players[pl] = *new Player(name);
            SaveGame::gameData.insert({"player "+std::to_string(pl), name});
            SaveGame::gameData.insert({"secretAnimal "+std::to_string(pl), players[pl].getSecretAnimal()});
            for (int i=0; i<3; ++i ) {
                players[pl].m_hand += deck.draw();
            }
        }
        SaveGame::mapToFile(saveDataFileName, SaveGame::gameData);
    } else {
        std::cout << "Saved game data exists!" << std::endl << "Loading..." << std::endl << "******************" << std::endl;
        std::map<std::string,std::string> fetchedSavedData;
        
        SaveGame::fileToMap(saveDataFileName, fetchedSavedData);
        noPlayers = std::stoi(fetchedSavedData["numPlayers"]);
        players = new Player[noPlayers];
        int tempPlayerID = 0;
        for (auto elem : fetchedSavedData) {
            if (elem.first.find("player") != std::string::npos) {
                tempPlayerID = SaveGame::extractFirstInt(elem.first);
                players[tempPlayerID] = *new Player(elem.second);
                for (int i = 0; i < 3; ++i) {
                    players[tempPlayerID].m_hand += deck.draw();
                }
            } else if (elem.first.find("secretAnimal") != std::string::npos) {
                tempPlayerID = SaveGame::extractFirstInt(elem.first);
                players[tempPlayerID].setSecretAnimal(elem.second);
            }
        }
    }
    
    bool won{false};
    
    do {
        for ( int pl=0; pl<noPlayers; ++pl ) {
            std::cout << "\nTable segment:\n";
            std::cout << tab;
            players[pl].m_hand += deck.draw();
            bool next = false;
            do {
                std::cout << players[pl];
                std::cout << std::endl;
                int cardNo;
                std::cout << "\nWhich card to play? (0 to " << players[pl].m_hand.noCards() - 1 << ")? ";
                std::cin >> cardNo;
                
                std::shared_ptr<AnimalCard> ac = players[pl].m_hand[cardNo];
                players[pl].m_hand -= ac;
                // try downcasting to action card
                std::shared_ptr<ActionCard> action = std::dynamic_pointer_cast<ActionCard>(ac);
                
                //Action Card is played
                if ( action != nullptr ) {
                    // on success
                    std::cout << "Top (1) or bottom (0) of start stack? " << std::endl;
                    int tmp;
                    std::cin >> tmp;
                    if (tmp>0){
                        tab += action;
                        next = true;
                    }else {
                        tab -= action;
                        // Perform action
                        QueryResult q = action->query();
                        try {
                            action->perfom( tab, players, q );
                        }catch(CustomExceptions ex){
                            std::cout << ex.what() << std::endl;
                        }
                        next = true;
                    }
                } else {
                    bool valid = false; //Is the player's action valid?
                    while(!valid){
                        int row, col;
                        std::string orientation;
                        std::cout << "Where should the card go? (row column)" << std::endl;
                        std::cin >> row >> col;
                        std::cout << "Orientation or card: up or down" << std::endl;
                        std::cin >> orientation;
                        if (orientation == "up") {
                            ac->setOrientation(Orientation::UP);
                        }else{
                            ac->setOrientation(Orientation::DOWN);
                        }
                        try {
                            int extraCard = tab.addAt( ac, row, col );
                            for ( int c=1;c<extraCard;++c ) {
                                players[pl].m_hand += deck.draw();
                            }
                            valid = true;
                            next = true;
                            
                        }catch(CustomExceptions ex){
                            std::cout << ex.what() << " , card cannot be added to table"<< std::endl;
                            std::cout << "Try to play another card? (yes or no)" << std::endl;
                            std::string play_new_card;
                            std::cin >> play_new_card;
                            if (play_new_card == "yes") {
                                ac->setOrientation(Orientation::UP);
                                valid = true;
                                players[pl].m_hand +=ac;
                            }
                            
                        }
                    }
                }
            }while(!next);
            if ( next ) {
                for ( int pl=0; pl<noPlayers && !won; ++pl ) {
                    won = tab.win( players[pl].getSecretAnimal() );
                    if (won) {
                        std::cout << players[pl] << "\n";
                        std::cout << "Has Won";
                    }
                }
            }
        }
    }while (!won);
    
    return 0;
}