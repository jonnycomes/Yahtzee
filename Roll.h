class Roll{
    int number;
    vector<int> dice;
    vector<int> keepers;
    bool skipToScore;
public:
    Roll();
    Roll(vector<int> dice);
    void print();
    int sum();
    int count(int die);
    int longestStraight();
    bool isYahtzee();
    bool areKeepersValid();
    void getKeepersFromUser();
    void again();
    // Getters:
    int getNumber(){return number;}
    vector<int> getDice(){return dice;}
    bool isSkipToScore(){return skipToScore;}
    vector<int> getKeepers(){return keepers;}
};

// Constructors:
Roll::Roll(){
    number = 1;
    skipToScore = false;
    for(int i = 0; i < 5; i++){
        dice.push_back(rand() % 6 + 1);
    }
}
Roll::Roll(vector<int> dice){
    number = 1;
    skipToScore = false;
    this->dice = dice;
}

/**
    Prints the dice of the roll to the console.
*/
void Roll::print(){
    vector< vector <string> > line = {
        {".---.",".---.",".---.",".---.",".---.",".---.",".---."},
        {"|   |","|   |","|*  |","|*  |","|* *|","|* *|","|* *|"},
        {"|   |","| * |","|   |","| * |","|   |","| * |","|* *|"},
        {"|   |","|   |","|  *|","|  *|","|* *|","|* *|","|* *|"},
        {"'---'","'---'","'---'","'---'","'---'","'---'","'---'"}
    };
    cout << "Roll " << number << ":" << endl;
    for(int row = 0; row < 5; row++){
        for(int die : dice){cout << line[row][die];}
        cout << endl;
    }
}

/**
    Computes the sum of the dice in the roll.
    @return the sum of the dice
*/
int Roll::sum(){
    int sum = 0;
    for(int die : dice){sum += die;}
    return sum;
}

/**
    Counts the number of times a die appears in the roll's dice
    @param die is the die counted in the roll
    @return the number of times die appears in dice
*/
int Roll::count(int die){
    int count = 0;
    for(int d : dice){
        if(d == die){count++;}
    }
    return count;
}

/**
    Computes the longest list of consecutive dice found in the roll's dice
    @return the length of the longest straight
*/
int Roll::longestStraight(){
    int longest = 0;
    int current = 0;
    for(int i = 1; i <= 6; i++){
        if(count(i) > 0){current++;}
        else{current = 0;}
        if(current > longest){longest = current;}
    }
    return longest;
}

/**
    Determines whether or not the roll is a Yahtzee (i.e. 5 of a kind
    @return true if the roll is Yahtzee; false otherwise
*/
bool Roll::isYahtzee(){
    return count(dice[0]) == 5;
}

/**
    Checks if the set of keepers is a subset (with multiplicity) 
    of the set of dice in the roll
    @return true if the keepers are valid; false otherwise
*/
bool Roll::areKeepersValid(){
    Roll keeps = Roll(keepers);
    for(int i = 1; i <= 6; i++){
        if(keeps.count(i) > this->count(i)){return false;}
    }
    return true;
}

/**
    Prompts the user to either enter the dice they want to keep from the 
    roll and roll again, or go directly to scoring the roll. Updates the 
    keepers and skipToScore according to the user's input.
*/
void Roll::getKeepersFromUser(){
    keepers.clear();
    cout << "Enter S to score. Enter keepers followed by R to roll again." << endl;
    string choice;
    int die;
    while(cin >> die){keepers.push_back(die);}
    cin.clear();
    getline(cin, choice);
    if(choice == "S" || choice == "s"){skipToScore = true;}
    else if(choice != "R" && choice != "r"){throw "Invalid input.";}
    else if(!areKeepersValid()){throw "Invalid input.";}
}

/**
    Re-rolls the non-keeper dice in the roll.
    Assumes that the keepers are valid for the roll.
    Increments the roll's number by one.
*/
void Roll::again(){
    dice = keepers;
    for(int i = keepers.size(); i < 5; i++){
        dice.push_back(rand() % 6 + 1);
    }
    number++;
}
