class Scorecard{
    vector<Box*> boxes;
    int numberOfYahtzeeBonus;
public:
    Scorecard();
    void update(Category* c, Roll roll);
    void print();
    bool isFull();
    int total();
    bool boxIsFull(int position);
private:
    int bonus();
    int upperSubTotal();
    int yahtzeeBonus();
    int lowerTotal();
    void printUpper();
    void printLower();
    bool isYahtzeeBoxFull();
    bool isJoker(Roll roll);
};

// Constructor:
Scorecard::Scorecard(){
    numberOfYahtzeeBonus = 0;
    vector<string> labels = {
        "Aces",
        "Twos",
        "Threes",
        "Fours",
        "Fives",
        "Sixes",
        "3 of a Kind",
        "4 of a Kind",
        "Full House",
        "Sm Straight",
        "Lg Straight",
        "Yahtzee",
        "Chance"
    };
    Box* b;
    for(int i = 0; i < 13; i++){
        b = new Box(i + 1, labels[i]);
        boxes.push_back(b);
    }
}

/**
    Prints the upper part of the scorecard to the console
*/
void Scorecard::printUpper(){
    for(int i = 0; i < 6; i++){
        cout << setw(2)  << boxes[i]->getPosition() << ". "
             << setw(11) << boxes[i]->getLabel();
        if(boxes[i]->isFilled()){
            cout << setw(4) << boxes[i]->getScore();
        }
        cout << endl;
    }
    cout << "Upper Subtotal:"     << setw(4) << upperSubTotal() << endl;
    cout << setw(15) <<  "Bonus:" << setw(4) << bonus() << endl;
    cout << setw(15) << "Upper Total:" << setw(4) << upperSubTotal() + bonus() << endl;
}

/**
    Prints the lower part of the scorecard to the console
*/
void Scorecard::printLower(){
    for(int i = 6; i < 13; i++){
        cout << setw(2)  << boxes[i]->getPosition() << ". "
             << setw(11) << boxes[i]->getLabel();
        if(boxes[i]->isFilled()){
            cout << setw(4) << boxes[i]->getScore();
        }
        cout << endl;
    }
    cout << setw(15) << "Yahtzee Bonus:" << setw(4) << yahtzeeBonus() << endl;
    cout << "Lower Subtotal:"     << setw(4) << lowerTotal() << endl;
    cout << setw(15) << "Total:" << setw(4) << total() << endl;
}

/**
    Prints the scorecard to the console
*/
void Scorecard::print(){
    for(int i = 0; i < 30; i++){cout << "-";}
    cout << endl;
    printUpper();
    printLower();
}

/**
    Updates one box of the scorecard with a given roll
    @param c points to the scoring category to be updated
    @param roll is the roll to update the scorecard with
*/
void Scorecard::update(Category* c, Roll roll){
    Box* b = boxes[c->getPosition() - 1];
    if(roll.isYahtzee() && isYahtzeeBoxFull()){numberOfYahtzeeBonus++;}
    b->fill();
    if(c->isValid(roll) || isJoker(roll)){b->setScore(c->score(roll));}
}

/**
    Checks if a Yahtzee has already been scored
    @return true if a Yahtzee has already been scored; false otherwise
*/
bool Scorecard::isYahtzeeBoxFull(){
    return boxes[11]->isFilled();
}

/**
    Checks if all the scoring positions have been filled
    @return true if all the scoring positions have been used; false otherwise
*/
bool Scorecard::isFull(){
    for(Box* b : boxes){
        if(!b->isFilled()){return false;}
    }
    return true;
}

/**
    Computes the total of the scores in the upper section 
    before adding the bonus.
    @return the total of the upper section (before adding the bonus)
*/
int Scorecard::upperSubTotal(){
    int sum = 0;
    for(int i = 0; i < 6; i++){
        sum += boxes[i]->getScore();
    }
    return sum;
}

/**
    Computes the bonus for the upper section which is either
    35 if the upper subtotal is at least 63, or 0 if the upper
    subtotal is less than 63.
    @return the bonus (either 0 or 35)
*/
int Scorecard::bonus(){
    if(upperSubTotal() >= 63){return 35;}
    else{return 0;}
}

/**
    Computes the score for the Yahtzee bonus section, which is
    100 points for each Yahtzee after the first Yahzee has been scored
    @return the score for the Yahtzee bonus section
*/
int Scorecard::yahtzeeBonus(){
    return 100 * numberOfYahtzeeBonus;
}

/**
    Computes the total of the lower section of the scorecard
    @return the total of the lower section
*/
int Scorecard::lowerTotal(){
    int sum = 0;
    for(int i = 6; i < 13; i++){
        sum += boxes[i]->getScore();
    }
    sum += yahtzeeBonus();
    return sum;
}

/**
    Computes the total score for the game
    @return the total score
*/
int Scorecard::total(){ 
    return bonus() + upperSubTotal() + lowerTotal();
}

/**
    Determines if a box at a given position has already been scored
    @param position is the position of the box to check
    @return true if the box at the given position has been scored; false otherwise
*/
bool Scorecard::boxIsFull(int position){
    return boxes[position - 1]->isFilled();
}

/**
    Determines whether or not a roll can be scored using the joker rule (i.e. the
    roll is a Yahtzee after the first Yahtzee has been scored)
    @param roll is the roll to check
    @return true if the joker rule is in effect; false otherwise
*/
bool Scorecard::isJoker(Roll roll){
    return roll.isYahtzee() && (numberOfYahtzeeBonus > 0);
}
