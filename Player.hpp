//
//  Player.hpp
//  Five Animals
//
//  Only allow max 5 instances of this class

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <vector>
#include "Hand.hpp"

class Player {
private:
    std::string m_playerName;
    std::string m_secretAnimal;
    // PlayerID is either 0,1,2,3,or4
    int m_playerID;
    
    // Returns a vector containing a random list of the secret animals
    // Should only be called max once a game
    static std::vector<std::string> getRandomSecretAnimals() {
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        std::vector<std::string> animals {"W","B","M","H","D"};
        auto currentIndexCounter = animals.size();
        
        for (auto iter = animals.rbegin(); iter != animals.rend(); ++iter, --currentIndexCounter) {
            int randomIndex = std::rand() % currentIndexCounter;
            if (*iter != animals.at(randomIndex)) {
                std::swap(animals.at(randomIndex), *iter);
            }
        }
        return animals;
    }
    
public:
    Hand m_hand;
    static int numPlayers;
    static const std::vector<std::string> secretAnimalArray;
    
    Player();
    Player(std::string _playerName);
    ~Player();
    
    std::string swapSecretAnimal(std::string& _newSecretAnimal);
    std::string getSecretAnimal();
    // This is to be used for loading a previous game
    void setSecretAnimal(const std::string &_secretAnimal);
    std::string getPlayerName();
    int getPlayerID() const;
    
    friend std::ostream& operator<<(std::ostream& out, const Player& _player);
};

inline std::ostream& operator<<(std::ostream& out, const Player& _player) {
    
    out << "Player Name: " << _player.m_playerName << "\nPlayer ID: " << _player.m_playerID << "\nSecret Animal: " << _player.m_secretAnimal;
    out << "\n";
    std::cout << "Hand:\n";
    std::cout << _player.m_hand;
    
    return out;
}

#endif /* Player_hpp */
