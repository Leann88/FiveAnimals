//
//  ActionCards.cpp
//  Five Animals
//
//  This file contains all the implementations of the action cards

#include "ActionCards.hpp"
#include "Table.hpp"
#include "CustomExceptions.hpp"

ActionCard::ActionCard(std::string action_symbol) : StartCard(action_symbol){}

//Query Result Class
QueryResult::QueryResult(std::string _query) {
    m_query = _query;
    m_performer = m_performedOn = "";
    // Set as -1 as a flag
    m_pickUpAtRow = m_pickUpAtCol = m_placeAtRow = m_placeAtCol = -1;
}

//Return the query
std::string QueryResult::getQuery() {
    return m_query;
}

//Return player that is performing the action
std::string QueryResult::getPerformer() {
    return m_performer;
}

//Return the player that the action is being performed on
std::string QueryResult::getPlayerInput() {
    return m_performedOn;
}

//Return the row of the card being moved
int QueryResult::getPickUpAtRow() {
    return m_pickUpAtRow;
}

//Return the column of the card being moved
int QueryResult::getPickUpAtCol() {
    return m_pickUpAtCol;
}


//Return the row of where the card should be placed
int QueryResult::getPlaceAtRow() {
    return m_placeAtRow;
}

//Return the column of where the card should be placed
int QueryResult::getPlaceAtCol() {
    return m_placeAtCol;
}

//Set the player that is performing the action
void QueryResult::setPerformer(std::string _performer) {
    m_performer = _performer;
}

//Set the player that the action is being performed on
void QueryResult::setPlayerInput(std::string _playerInput) {
    m_performedOn = _playerInput;
}

//Set the row of the card being moved
bool QueryResult::setPickUpAtRow(int _row) {
    // Add basic check for row
    if (_row >= 0) {
        m_pickUpAtRow = _row;
        return true;
    }
    return false;
}

//Set the column of the card being moved
bool QueryResult::setPickUpAtCol(int _col) {
    // Add basic check for col
    if (_col >= 0) {
        m_pickUpAtCol = _col;
        return true;
    }
    return false;
}

//Set the row of where the card should be moved to
bool QueryResult::setPlaceAtRow(int _row) {
    // Add basic check for row
    if (_row >= 0) {
        m_placeAtRow = _row;
        return true;
    }
    return false;
}

//Set the column of where the card should be moved to
bool QueryResult::setPlaceAtCol(int _col) {
    // Add basic check for col
    if (_col >= 0) {
        m_placeAtCol = _col;
        return true;
    }
    return false;
}

//Bear Card Action Card
BearAction::BearAction() :
m_symbol("B"),
m_bearAction("The bear action card allows a player to select another player to switch hands."),
m_qr(m_bearAction),
ActionCard("B") {}

const std::string BearAction::getSymbol() {
    return m_symbol;
}

QueryResult BearAction::query() {
    std::string performer;
    std::string performedOn;
    
    std::cout << "Enter your playerID: ";
    std::cin >> performer;
    std::cout << m_bearAction << "\nEnter the playerID to change hands with: ";
    std::cin >> performedOn;
    
    m_qr.setPerformer(performer);
    m_qr.setPlayerInput(performedOn);
    
    return m_qr;
}

void BearAction::perfom( Table& _table, Player* _player, QueryResult _qr) {
    if (std::stoi(_qr.getPlayerInput())>_player->numPlayers - 1) {
        throw CustomExceptions("No Player Found");
    }
    
    // Hold performer hand
    Hand temp_hand = _player[std::stoi(_qr.getPerformer())].m_hand;
    Hand temp_hand_two = _player[std::stoi(_qr.getPlayerInput())].m_hand;
    //Change the hand of the player
    _player[std::stoi(_qr.getPerformer())].m_hand = temp_hand_two;
    _player[std::stoi(_qr.getPlayerInput())].m_hand = temp_hand;
    
}

void BearAction::print() {
    // Use (int (*)(int)) to select the particular overload for the toupper function
    std::transform(m_bearAction.begin(), m_bearAction.end(), m_bearAction.begin(), (int (*)(int))toupper);
    std::cout << m_bearAction << std::endl;
}

//Hare Card Action Card
HareAction::HareAction() :
m_symbol("H"),
m_hareAction("The hare action card allows a player to move an animal card on the table including the joker to a different location on the table where the card is valid."),
m_qr(m_hareAction),
ActionCard("H") {}

const std::string HareAction::getSymbol() {
    return m_symbol;
}

QueryResult HareAction::query() {
    std::string performer;
    int coord_row_pickAt;
    int coord_col_pickAt;
    int coord_row_placeAt;
    int coord_col_placeAt;
    
    std::cout << "Enter your playerID: ";
    std::cin >> performer;
    
    // Perform simple checks
    do {
        std::cout << m_hareAction << "\nEnter the coordinates to pick up (ROW): ";
        std::cin >> coord_row_pickAt;
    } while (coord_row_pickAt < 0 || coord_row_pickAt > 102);
    
    do {
        std::cout << "\nEnter the coordinates to pick up (COL): ";
        std::cin >> coord_col_pickAt;
    } while (coord_col_pickAt < 0 || coord_col_pickAt > 102);
    
    do {
        std::cout << "\nEnter the coordinates to place (ROW): ";
        std::cin >> coord_row_placeAt;
    } while (coord_row_placeAt < 0 || coord_row_placeAt > 102);
    
    do {
        std::cout << "\nEnter the coordinates to place (COL): ";
        std::cin >> coord_col_placeAt;
    } while (coord_col_placeAt < 0 || coord_col_placeAt > 102);
    std::cout << "\n";
    m_qr.setPerformer(performer);
    m_qr.setPickUpAtRow(coord_row_pickAt);
    m_qr.setPickUpAtCol(coord_col_pickAt);
    m_qr.setPlaceAtRow(coord_row_placeAt);
    m_qr.setPlaceAtCol(coord_col_placeAt);
    
    return m_qr;
}

void HareAction::perfom( Table& _table, Player* _player, QueryResult _qr) {
    //Pick up the card
    std::shared_ptr<AnimalCard> card = _table.pickAt(_qr.getPickUpAtRow(), _qr.getPickUpAtCol());
    //If you can't place the card
    if (!_table.addAt(card, _qr.getPlaceAtRow(), _qr.getPlaceAtCol())) {
        //Put it back
        _table.addAt(card, _qr.getPickUpAtRow(), _qr.getPickUpAtCol());
        throw CustomExceptions("No valid match is found.");
    }
}

void HareAction::print() {
    // Use (int (*)(int)) to select the particular overload for the toupper function
    std::transform(m_hareAction.begin(), m_hareAction.end(), m_hareAction.begin(), (int (*)(int))toupper);
    std::cout << m_hareAction << std::endl;
}

//Wolf Card, Action Card

WolfAction::WolfAction() :
m_symbol("W"),
m_wolfAction("The wolf action card allows a player to pick up a card from the table and place it in the player\'s hand."),
m_qr(m_wolfAction),
ActionCard("W") {}

const std::string WolfAction::getSymbol() {
    return m_symbol;
}

QueryResult WolfAction::query() {
    std::string performer;
    int coord_row;
    int coord_col;
    
    std::cout << "Enter your playerID: ";
    std::cin >> performer;
    
    do {
        std::cout << m_wolfAction << "\nEnter the coordinates to pick up (ROW): ";
        std::cin >> coord_row;
    } while (coord_row < 0 || coord_row > 102);
    
    do {
        std::cout << "\nEnter the coordinates to pick up (COL): ";
        std::cin >> coord_col;
    } while (coord_col < 0 || coord_col > 102);
     std::cout << "\n";
    m_qr.setPerformer(performer);
    m_qr.setPickUpAtRow(coord_row);
    m_qr.setPickUpAtCol(coord_col);
    
    return m_qr;
}

void WolfAction::perfom( Table& _table, Player* _player, QueryResult _qr) {
    //Pick up the card
    std::shared_ptr<AnimalCard> card = _table.pickAt(_qr.getPickUpAtRow(), _qr.getPickUpAtCol());
    //Place it in performing players hand
    _player[std::stoi(_qr.getPerformer())].m_hand += card;
}

void WolfAction::print() {
    // Use (int (*)(int)) to select the particular overload for the toupper function
    std::transform(m_wolfAction.begin(), m_wolfAction.end(), m_wolfAction.begin(), (int (*)(int))toupper);
    std::cout << m_wolfAction << std::endl;
}

//Dear Card Action Card

DearAction::DearAction() :
m_symbol("D"),
m_dearAction("The deer action card allows a player to select another player to trade goals with."),
m_qr(m_dearAction),
ActionCard("D") {}

const std::string DearAction::getSymbol() {
    return m_symbol;
}

QueryResult DearAction::query() {
    std::string performer;
    std::string performedOn;
    
    std::cout << "Enter your playerID: ";
    std::cin >> performer;
    std::cout << m_dearAction << "\nEnter the playerID of the player to trade to goals with: ";
    std::cin >> performedOn;
    
    m_qr.setPerformer(performer);
    m_qr.setPlayerInput(performedOn);
    
    return m_qr;
}

void DearAction::perfom( Table& _table, Player* _player, QueryResult _qr) {
    // Hold performer and performee's secret animals
    if (std::stoi(_qr.getPlayerInput())>_player->numPlayers - 1) {
        throw CustomExceptions("No Player Found");
    }
    std::string temp_animal = _player[std::stoi(_qr.getPerformer())].getSecretAnimal();
    std::string temp_animal2 = _player[std::stoi(_qr.getPlayerInput())].getSecretAnimal();
    //swap player's hand
    _player[std::stoi(_qr.getPerformer())].swapSecretAnimal(temp_animal2);
    _player[std::stoi(_qr.getPlayerInput())].swapSecretAnimal(temp_animal);
}

void DearAction::print() {
    // Use (int (*)(int)) to select the particular overload for the toupper function
    std::transform(m_dearAction.begin(), m_dearAction.end(), m_dearAction.begin(), (int (*)(int))toupper);
    std::cout << m_dearAction << std::endl;
}

//Mouse Card Action Card

MooseAction::MooseAction() :
m_symbol("M"),
m_mooseAction("The moose action card triggers a rotation of secret animals form player 1 to player 2, from 2 to 3, etc. in turn."),
m_qr(m_mooseAction),
ActionCard("M") {}

const std::string MooseAction::getSymbol() {
    return m_symbol;
}

QueryResult MooseAction::query() {
    
    std::cout << m_mooseAction << std::endl;
    
    return m_qr;
}

void MooseAction::perfom( Table& _table, Player* _player, QueryResult _qr) {
    //Make an array that will hold all the player's hands
    std::string player_animal = _player[0].getSecretAnimal();
    //Add each player's hand into the array
    //Swap all the player's hands
    for (int i = 0; i < _player->numPlayers; i++) {
        player_animal = _player[(i + 1) % _player->numPlayers].swapSecretAnimal(player_animal);
    }
}

void MooseAction::print() {
    // Use (int (*)(int)) to select the particular overload for the toupper function
    std::transform(m_mooseAction.begin(), m_mooseAction.end(), m_mooseAction.begin(), (int (*)(int))toupper);
    std::cout << m_mooseAction << std::endl;
}