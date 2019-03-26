class Category{ 
protected:
    int position;
public:
    // Factory method
    static Category *makeCategory(int choice);
    // Pure virtual functions
    virtual bool isValid(Roll roll) = 0;
    virtual int score(Roll roll) = 0;
    // Getter
    int getPosition(){return position;}
};

class UpperCategory: public Category{
public:
    UpperCategory(int pos){
        position = pos;
    }
    bool isValid(Roll roll){
        return true;
    }
    int score(Roll roll){
        return position * roll.count(position);
    }
};

class ThreeOfAKind: public Category{
public:
    ThreeOfAKind(){
        position = 7;
    }
    bool isValid(Roll roll){
        vector<int> dice = roll.getDice();
        for(int die : dice){
            if(roll.count(die) >= 3){return true;}
        }
        return false;
    }
    int score(Roll roll){
        return roll.sum();
    }
};

class FourOfAKind: public Category{
public:
    FourOfAKind(){
        position = 8;
    }
    bool isValid(Roll roll){
        vector<int> dice = roll.getDice();
        for(int die : dice){
            if(roll.count(die) >= 4){return true;}
        }
        return false;
    }
    int score(Roll roll){
        return roll.sum();
    }
};

class FullHouse: public Category{
public:
    FullHouse(){
        position = 9;
    }
    bool isValid(Roll roll){
        bool two = false;
        bool three = false;
        vector<int> dice = roll.getDice();
        for(int die : dice){
            if(roll.count(die) == 2){two = true;}
            if(roll.count(die) == 3){three = true;}
        }
        return two && three;
    }
    int score(Roll roll){
        return 25;
    }
};

class SmStraight: public Category{
public:
    SmStraight(){
        position = 10;
    }
    bool isValid(Roll roll){
        return roll.longestStraight() >= 4;
    }
    int score(Roll roll){
        return 30;
    }
};

class LgStraight: public Category{
public:
    LgStraight(){
        position = 11;
    }
    bool isValid(Roll roll){
        return roll.longestStraight() == 5;
    }
    int score(Roll roll){
        return 40;
    }
};

class Yahtzee: public Category{
public:
    Yahtzee(){
        position = 12;
    }
    bool isValid(Roll roll){
        return roll.isYahtzee();
    }
    int score(Roll roll){
        return 50;
    }
};

class Chance: public Category{
public:
    Chance(){
        position = 13;
    }
    bool isValid(Roll roll){
        return true;
    }
    int score(Roll roll){
        return roll.sum();
    }
};

Category* Category::makeCategory(int choice){
    switch(choice){
        case  7 : return new ThreeOfAKind();
        case  8 : return new FourOfAKind();
        case  9 : return new FullHouse();
        case 10 : return new SmStraight();
        case 11 : return new LgStraight();
        case 12 : return new Yahtzee();
        case 13 : return new Chance();
        default : return new UpperCategory(choice);
    }
}