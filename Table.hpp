//
//  Table.hpp
//  Five Animals
//

#ifndef Table_hpp
#define Table_hpp

#include <string>
#include "AnimalCard.hpp"
#include "StartStack.hpp"
#include "CustomExceptions.hpp"
#include "ActionCards.hpp"

class Table {
private:
    std::shared_ptr<AnimalCard> m_table[103][103];
    int m_bearCount;
    int m_hareCount;
    int m_wolfCount;
    int m_dearCount;
    int m_mooseCount;
    int upper_row;
    int lower_row;
    int upper_column;
    int lower_column;
    StartStack _startStack;
    
public:
    Table();
    
    int addAt(std::shared_ptr<AnimalCard> ac, int row, int col);
    
    std::shared_ptr<AnimalCard> pickAt(int row, int col);
    int matchCards(std::string one_cit, std::string two_cit, std::string one_ac, std::string two_ac);
    bool win(const std::string& animal );
    
    Table& operator+=( std::shared_ptr<ActionCard> ac);
    Table& operator-=( std::shared_ptr<ActionCard> );
    
    void incrementAnimalCount(std::string animal);
    void decrementAnimalCount(std::string animal);
    void changeAnimalCount(std::string, std::string, std::string, std::string);
    
    friend std::ostream& operator<<(std::ostream& out, Table& _table);
};

inline std::ostream& operator<<(std::ostream& out, Table& _table) {
    out << "   ";
    for (int i = _table.lower_column; i <= _table.upper_column; ++i) {
        out << i << " ";
    }
    out << "   ";
    out << "\n";
    for (int row = _table.lower_row; row <= _table.upper_row; ++row) {
        out << row << " ";
        for (int col = _table.lower_column; col <= _table.upper_column; ++col) {
            if(_table.m_table[row][col]){
                _table.m_table[row][col]->printRow(out, EvenOdd::ODD);
                out << " ";
            }else {
                out << "   ";
            }
        }
        out << "\n";
        out << "   ";
        for (int col = _table.lower_column; col <= _table.upper_column; ++col) {
            if(_table.m_table[row][col]){
                _table.m_table[row][col]->printRow(out, EvenOdd::EVEN);
                out << " ";
            }else {
                out << "   ";
            }
        }
        
        out << "\n\n";
    }
    out << "Bear Count: " <<  _table.m_bearCount << " ";
    out << "Hare Count: " <<  _table.m_hareCount << " ";
    out << "Wolf Count: " <<  _table.m_wolfCount << " ";
    out << "Dear Count: " <<  _table.m_dearCount << " ";
    out << "Moose Count: " <<  _table.m_mooseCount << " ";
    out << "\n";
    
    return out;
}

#endif /* Table_hpp */
