class Box{
    int position;
    string label;
    int score;
    bool filled;
public:
    Box(int position, string label);
    // Getters:
    bool isFilled(){return filled;}
    int getPosition(){return position;}
    string getLabel(){return label;}
    int getScore(){return score;}
    // Setters: 
    void fill(){filled = true;}
    void setScore(int s){score = s;}
};

// Constructor:
Box::Box(int position, string label){
    this->position = position;
    this->label = label;
    this->score = 0;
    this->filled = false;
}
