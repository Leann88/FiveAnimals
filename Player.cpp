//
//  Player.cpp
//  Five Animals
//
//  Only allow max 5 instances of this class

#include "Player.hpp"

// Initialize static member of Player class
int Player::numPlayers = 0;
const std::vector<std::string> Player::secretAnimalArray = getRandomSecretAnimals();

Player::Player() {}

Player::Player(std::string _playerName) {
    // Since it starts at 0
    if (numPlayers > 4) {
        throw "Too many player!";
    }
    m_playerName = _playerName;
    m_secretAnimal = secretAnimalArray.at(numPlayers);
    m_playerID = numPlayers;
    ++numPlayers;
}

Player::~Player() {
    --numPlayers;
}
std::string Player::swapSecretAnimal(std::string& _newSecretAnimal) {
    std::string temp = m_secretAnimal;
    m_secretAnimal = _newSecretAnimal;
    return temp;
}
std::string Player::getSecretAnimal(){
    return m_secretAnimal;
}
void Player::setSecretAnimal(const std::string &_secretAnimal){
    m_secretAnimal = _secretAnimal;
}
std::string Player::getPlayerName(){
    return m_playerName;
}
int Player::getPlayerID() const {
    return m_playerID;
}

