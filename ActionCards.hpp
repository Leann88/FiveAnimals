//
//  ActionCards.hpp
//  Five Animals
//

#ifndef ActionCards_hpp
#define ActionCards_hpp

#include <iostream>
#include <string>
#include <algorithm>
#include "Player.hpp"
// Forward declare AnimalCard and Table, to avoid circular dependency
class AnimalCard;
class Table;

class QueryResult {
private:
    std::string m_query;
    std::string m_performer;
    std::string m_performedOn;
    
    int m_pickUpAtRow;
    int m_pickUpAtCol;
    
    int m_placeAtRow;
    int m_placeAtCol;
    
public:
    
    QueryResult(std::string _query);
    std::string getQuery();
    std::string getPerformer();
    std::string getPlayerInput();
    int getPickUpAtRow();
    int getPickUpAtCol();
    int getPlaceAtRow();
    int getPlaceAtCol();
    
    void setPerformer(std::string _performer);
    void setPlayerInput(std::string _playerInput);
    bool setPickUpAtRow(int _row);
    bool setPickUpAtCol(int _col);
    bool setPlaceAtRow(int _row);
    bool setPlaceAtCol(int _col);
};

class ActionCard : public StartCard {
public:
    ActionCard(std::string action_symbol);
    virtual const std::string getSymbol() = 0;
    virtual QueryResult query() = 0;
    virtual void perfom( Table&, Player*, QueryResult ) = 0;
};

/************************************************************
 *** The following are the individual action card classes ***
 ************************************************************/

class BearAction : public ActionCard {
private:
    
    std::string m_bearAction;
    std::string m_symbol;
    
    QueryResult m_qr;
    
public:
    
    BearAction();
    
    virtual const std::string getSymbol();
    virtual QueryResult query();
    virtual void perfom( Table& _table, Player* _player, QueryResult _qr);
    void print();
};

class HareAction : public ActionCard {
private:
    std::string m_hareAction;
    std::string m_symbol;
    
    QueryResult m_qr;
    
public:
    
    HareAction();
    virtual const std::string getSymbol();
    virtual QueryResult query();
    virtual void perfom( Table& _table, Player* _player, QueryResult _qr);
    void print();
};

class WolfAction : public ActionCard {
private:
    std::string m_wolfAction;
    std::string m_symbol;
    
    QueryResult m_qr;
    
public:
    
    WolfAction();
    virtual const std::string getSymbol();
    virtual QueryResult query();
    void perfom( Table& _table, Player* _player, QueryResult _qr);
    void print();
};

class DearAction : public ActionCard {
private:
    std::string m_dearAction;
    std::string m_symbol;
    
    QueryResult m_qr;
    
public:
    
    DearAction();
    virtual const std::string getSymbol();
    virtual QueryResult query();
    virtual void perfom( Table& _table, Player* _player, QueryResult _qr);
    void print();
};

class MooseAction : public ActionCard {
private:
    std::string m_mooseAction;
    std::string m_symbol;
    
    QueryResult m_qr;
    
public:
    
    MooseAction();
    virtual const std::string getSymbol();
    virtual QueryResult query();
    virtual void perfom( Table& _table, Player* _player, QueryResult _qr);
    void print();
};


#endif /* ActionCards_hpp */