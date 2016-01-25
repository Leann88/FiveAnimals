//
//  Table.cpp
//  Five Animals
//

#include "Table.hpp"

Table::Table() {
    m_table[52][52] = _startStack.getCurrBehaviour();
    m_bearCount = m_hareCount = m_wolfCount = m_dearCount = m_mooseCount = 0;
    upper_row = lower_row = upper_column = lower_column = 52;
}

int Table::addAt(std::shared_ptr<AnimalCard> ac, int row, int col) {
    
    int matchCount = 0;
    std::shared_ptr<AnimalCard> compare_card;
    std::string quad_one_of_cit;
    std::string quad_two_of_cit;
    std::string quad_one_of_ac;
    std::string quad_two_of_ac;
    
    if (m_table[row][col]) {
        // Something already occupies that spot!
        return 0;
    }
    
    //Joker case, increment count of all animal card counts and find "matches"
    if (ac->getQuadrant(0, 0) == "j") {
        m_bearCount++;
        m_hareCount++;
        m_wolfCount++;
        m_dearCount++;
        m_mooseCount++;
        
        //Need to check number of cards the joker "matches"
        //Card Above
        compare_card = m_table[row - 1][col];
        if(compare_card){
            quad_one_of_cit = compare_card->getQuadrant(1, 0);
            quad_two_of_cit = compare_card->getQuadrant(1, 1);
            
            //if the animals in the quadrants are the same, only one match
            
            if (!quad_one_of_cit.compare(quad_two_of_cit)){
                matchCount++;
            }else{
                matchCount += 2;
            }
        }
        //Card to left
        compare_card = m_table[row][col - 1];
        if(compare_card){
            quad_one_of_cit = compare_card->getQuadrant(0, 1);
            quad_two_of_cit = compare_card->getQuadrant(1, 1);
            
            //if the animals in the quadrants are the same, only one match
            
            if (!quad_one_of_cit.compare(quad_two_of_cit)){
                matchCount++;
            }else{
                matchCount += 2;
            }
        }
        
        //Card to right
        compare_card = m_table[row][col + 1];
        if (compare_card) {
            quad_one_of_cit = compare_card->getQuadrant(0, 0);
            quad_two_of_cit = compare_card->getQuadrant(1, 0);
            
            //if the animals in the quadrants are the same, only one match
            
            if (!quad_one_of_cit.compare(quad_two_of_cit)){
                matchCount++;
            }else{
                matchCount += 2;
            }
        }
        
        //Card Below
        compare_card = m_table[row + 1][col];
        if (compare_card) {
            
            quad_one_of_cit = compare_card->getQuadrant(0, 0);
            quad_two_of_cit = compare_card->getQuadrant(0, 1);
            
            //if the animals in the quadrants are the same, only one match
            
            if (!quad_one_of_cit.compare(quad_two_of_cit)){
                matchCount++;
            }else{
                matchCount += 2;
            }
        }
        
        //Joker card wasn't placed
    } else {
        
        // Card above
        compare_card = m_table[row -1][col];
        if (compare_card){
            quad_one_of_cit = compare_card->getQuadrant(1, 0);
            quad_two_of_cit = compare_card->getQuadrant(1, 1);
            quad_one_of_ac = ac->getQuadrant(0, 0);
            quad_two_of_ac = ac->getQuadrant(0, 1);
            
            matchCount += matchCards(quad_one_of_cit, quad_two_of_cit, quad_one_of_ac, quad_two_of_ac);
        }
        
        // Card to left
        compare_card = m_table[row][col - 1];
        if (compare_card) {
            
            quad_one_of_cit = compare_card->getQuadrant(0, 1);
            quad_two_of_cit = compare_card->getQuadrant(1, 1);
            quad_one_of_ac = ac->getQuadrant(0, 0);
            quad_two_of_ac = ac->getQuadrant(1, 0);
            matchCount += matchCards(quad_one_of_cit, quad_two_of_cit, quad_one_of_ac, quad_two_of_ac);
        }
        
        // Card to right
        compare_card = m_table[row][col + 1];
        if (compare_card) {
            quad_one_of_cit = compare_card->getQuadrant(0, 0);
            quad_two_of_cit = compare_card->getQuadrant(1, 0);
            quad_one_of_ac = ac->getQuadrant(0, 1);
            quad_two_of_ac = ac->getQuadrant(1, 1);
            matchCount += matchCards(quad_one_of_cit, quad_two_of_cit, quad_one_of_ac, quad_two_of_ac);
            
        }
        
        // Card below
        compare_card = m_table[row + 1][col];
        if (compare_card) {
            
            quad_one_of_cit = compare_card->getQuadrant(0, 0);
            quad_two_of_cit = compare_card->getQuadrant(0, 1);
            quad_one_of_ac = ac->getQuadrant(1, 0);
            quad_two_of_ac = ac->getQuadrant(1, 1);
            matchCount += matchCards(quad_one_of_cit, quad_two_of_cit, quad_one_of_ac, quad_two_of_ac);
        }
        
    }
    
    //A match was found along the way
    if (matchCount > 0) {
        //add card to table and change the animal counts
        m_table[row][col] = ac;
        changeAnimalCount(ac->getQuadrant(0, 0), ac->getQuadrant(0, 1), ac->getQuadrant(1, 0), ac->getQuadrant(1, 1));
        
        //Used to print the table, table will grow as more cards are added
        if (row < lower_row) {
            lower_row = row;
        }
        
        if (row > upper_row) {
            upper_row = row;
        }
        
        if (col < lower_column) {
            lower_column = col;
        }
        
        if (col > upper_column) {
            upper_column = col;
        }
    }
    if (matchCount == 0) {
        throw CustomExceptions("IllegalPlacement");
    }
    if (matchCount < 5) {
        return matchCount;
    }else{
        return 4;
    }
    
}

//Removing a card from the table
std::shared_ptr<AnimalCard> Table::pickAt(int row, int col) {
    if (row == 52 && col == 52) {
        throw CustomExceptions("IllegalPick");
    }
    
    std::shared_ptr<AnimalCard> remove_card = m_table[row][col];
    //If there is actually a card, change the counts of each animal
    if (remove_card) {
        std::string quad_one_of_card = remove_card->getQuadrant(0, 0);
        std::string quad_two_of_card = remove_card->getQuadrant(0, 1);
        std::string quad_three_of_card = remove_card->getQuadrant(1, 0);
        std::string quad_four_of_card = remove_card->getQuadrant(1, 1);
        //if card to be removed is the joker
        if (quad_one_of_card == "j") {
            m_bearCount--;
            m_hareCount--;
            m_wolfCount--;
            m_dearCount--;
            m_mooseCount--;
            
        } else {
            decrementAnimalCount(quad_one_of_card);
            //make sure the animals in the quadrant aren't the same
            if (quad_one_of_card != quad_two_of_card) {
                decrementAnimalCount(quad_two_of_card);
            }
            
            if ((quad_one_of_card != quad_three_of_card) && (quad_two_of_card != quad_three_of_card)) {
                decrementAnimalCount(quad_three_of_card);
            }
            
            if ((quad_one_of_card != quad_four_of_card) && (quad_two_of_card != quad_four_of_card) && (quad_three_of_card != quad_four_of_card)) {
                decrementAnimalCount(quad_four_of_card);
            }
        }
        
        m_table[row][col] = nullptr;
        remove_card->setOrientation(Orientation::UP);
        return remove_card;
    } else {//No card at location
        
        throw CustomExceptions("IllegalPick");
    }
}

//Number of animal matches between sections of cards
int Table::matchCards(std::string one_cit, std::string two_cit, std::string one_ac, std::string two_ac){
    int num_matches = 0;
    
    std::transform(one_cit.begin(), one_cit.end(), one_cit.begin(), ::tolower);
    std::transform(two_cit.begin(), two_cit.end(), two_cit.begin(), ::tolower);
    //If the quadrants are the same, you only need to compare one quadrant with the quadrants of the card to be added, trying to match the animals on the card
    if (one_cit == two_cit){
        if (one_cit == one_ac || one_cit== two_ac){
            // Match increment the animal
            num_matches++;
        }
        
    }else {
        
        if (one_cit == one_ac) {
            num_matches++;
        }
        
        if (two_cit == two_ac) {
            num_matches++;
        }
    }
    
    //check to see if you are putting the card next to a joker or the start card
    if (one_cit == "c" || one_cit == "j") {
        //check to see if the animals in the quadrant are the same, if so, only one match
        if (one_ac == two_ac) {
            num_matches++;
            
        } else {
            num_matches += 2;
        }
    }
    return num_matches;
}

//Function that determines whether or not the game has been won
bool Table::win( const std::string& animal ){
    if (animal == "B" && m_bearCount == 12) {
        return true;
    }
    
    if (animal == "M" && m_mooseCount == 12) {
        return true;
    }
    
    if (animal == "W" && m_wolfCount == 12) {
        return true;
    }
    
    if (animal == "D" && m_dearCount == 12) {
        return true;
    }
    
    if (animal == "H" && m_hareCount == 12) {
        return true;
    }
    
    return false;
}

Table& Table::operator+=( std::shared_ptr<ActionCard> ac){
    
    incrementAnimalCount(ac->getSymbol());
    decrementAnimalCount(_startStack.getCurrBehaviour()->getQuadrant(1, 1));
    _startStack += ac;
    m_table[52][52] = _startStack.getCurrBehaviour();
    
    return *this;
}

Table& Table::operator-=( std::shared_ptr<ActionCard> ac) {
    _startStack -= ac;
    
    return *this;
}

//Function that increments the count of animal cards
void Table::incrementAnimalCount(std::string animal){
    if (animal == "b" || animal == "B") {
        m_bearCount++;
    }
    
    if (animal == "m" || animal == "M") {
        m_mooseCount++;
    }
    
    if (animal == "w" || animal == "W") {
        m_wolfCount++;
    }
    
    if (animal == "d" || animal == "D") {
        m_dearCount++;
    }
    
    if (animal == "h" || animal == "H") {
        m_hareCount++;
    }
}

//Increment the animal count based on a given animal's on a given card
void Table::changeAnimalCount( std::string quad_one_of_card, std::string quad_two_of_card, std::string quad_three_of_card,std::string quad_four_of_card){
    
    incrementAnimalCount(quad_one_of_card);
    if (quad_one_of_card != quad_two_of_card) {
        incrementAnimalCount(quad_two_of_card);
    }
    
    if ((quad_one_of_card != quad_three_of_card) && (quad_two_of_card != quad_three_of_card)) {
        incrementAnimalCount(quad_three_of_card);
    }
    
    if ((quad_one_of_card != quad_four_of_card) && (quad_two_of_card != quad_four_of_card) && (quad_three_of_card != quad_four_of_card)) {
        incrementAnimalCount(quad_four_of_card);
    }
}
//Function that decrements the count of animal cards
void Table::decrementAnimalCount(std::string animal){
    if (animal == "b" || animal == "B") {
        m_bearCount--;
    }
    
    if (animal == "m" || animal == "M") {
        m_mooseCount--;
    }
    
    if (animal == "w" || animal == "W") {
        m_wolfCount--;
    }
    
    if (animal == "d" || animal == "D") {
        m_dearCount--;
    }
    
    if (animal == "h" || animal == "H") {
        m_hareCount--;
    }
}

