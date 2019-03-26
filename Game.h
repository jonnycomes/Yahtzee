class Game{
    int score;
    bool gameOver;
public:
    Game();
    void play();
    // Getters
    int getScore(){return score;}
private:
    Roll playRound(Scorecard sc);
    int getScoringPosition(Scorecard s);
};

// Constructor:
Game::Game(){
    score = 0;
    gameOver = false;
}

/**
    Plays one round (i.e. 1-3 rolls of dice)
    @param sc is the scorecard for the game
    @return the roll from the round
*/
Roll Game::playRound(Scorecard sc){
    sc.print();
    Roll roll;
    roll.print();
    do{
        try{
            roll.getKeepersFromUser();
            if(roll.isSkipToScore()){break;}
            if(roll.areKeepersValid()){
                roll.again();
                sc.print();
                roll.print();
            }
        }
        catch(const char* msg){cout << msg << endl;}
    }while(roll.getNumber() < 3);
    return roll;
}

/**
    Prompts the user for the scoring category and returns the user's input
    @param sc is the scorecard for the game
    @return the position to score the round (an integer from 1 to 13)
*/
int Game::getScoringPosition(Scorecard sc){
    int choice;
    bool badInput;
    do{
        // Get user input:
        badInput = false;
        cout << "Choose a category: ";
        try{
            cin >> choice;
            // Check for bad inputs:
            if(cin.fail()){
                cin.clear();
                string trash;
                getline(cin, trash);
                throw "Enter an integer between 1 and 13.";
            }
            else if(choice < 1 || choice > 13){
                throw "Enter a number between 1 and 13.";
            }
            else if(sc.boxIsFull(choice)){
                throw "That category is already full.";
            }
        }
        catch(const char* msg){
            cout << msg << endl;
            badInput = true;
        }
    }while(badInput);
    cin.ignore();
    return choice;
}

/**
    Plays one game of Yahtzee with one player
*/
void Game::play(){
    Scorecard scorecard;
    do{
        Roll roll = Game::playRound(scorecard);
        int choice = Game::getScoringPosition(scorecard);
        Category* scoringCategory = Category::makeCategory(choice);
        scorecard.update(scoringCategory, roll);
        gameOver = scorecard.isFull();
        score = scorecard.total();
    }while(!gameOver);
    scorecard.print();
}

