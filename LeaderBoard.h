class LeaderBoard{
    vector<int> highScores;
    vector<string> champions;
public:
    LeaderBoard();
    void checkAndPrint(int score);
private:
    void printTopTen();
    bool isNewTopTen(int score);
    void addHighScore(int score, string name);
};

// Constructor:
LeaderBoard::LeaderBoard(){
    ifstream file;
    file.open("HighScores.txt");
    if(file.fail()){
        cout << "Failed to open HighScores.txt" << endl;
    }
    int score;
    string comma;
    string name;
    while(file >> score >> comma){
        getline(file, name);
        highScores.push_back(score);
        champions.push_back(name);
    }
    file.close();
}

/**
    Adds a player's name and high score to the top ten list
    @param score is the high score to add
    @param name is the player's name
*/
void LeaderBoard::addHighScore(int score, string name){
    int place = 0;
    for(int s : highScores){
        if(s >= score){place++;}
    }
    for(int i = 8; i >= place; i--){
        highScores[i + 1] = highScores[i];
        champions[i + 1] = champions[i];
    }
    highScores[place] = score;
    champions[place] = " " + name;

    ofstream file;
    file.open("HighScores.txt");
    if(file.fail()){
        cout << "Failed to open HighScores.txt" << endl;
    }
    for(int i = 0; i < 10; i++)
    {
        file << highScores[i] << "," << champions[i] << endl;
    }
    file.close();
}

/**
    Checks if a new score should be added to the top ten list
    @param score is the new score to check
    @return true if score is greater than one of the scores 
            on the top ten list; false otherwise
*/
bool LeaderBoard::isNewTopTen(int score){
    return score > highScores[9];
}

/**
    Prints the top ten list to the console
*/
void LeaderBoard::printTopTen(){
    cout << endl << "Top 10 Scores:" << endl << endl;
    for(int i = 0; i < 10; i++){
        cout << setw(2) << right << i + 1 << "." 
             << setw(4) << right << highScores[i] << " " 
             << champions[i] << endl;
    }
}

/**
    Updates the top ten list in the case of a new high score.
    Then prints the (possibly new) top ten list.
    @param score is the score of the game
*/
void LeaderBoard::checkAndPrint(int score){
    if(isNewTopTen(score)){
        cout << "You got a new high score!" << endl;
        cout << "Name: ";
        string name;
        getline(cin, name);
        addHighScore(score, name);
    }
    printTopTen();
}


