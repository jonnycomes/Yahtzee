#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Box;
class Roll;
class Category;
class Scorecard;
class Game;
class LeaderBoard;

#include "Box.h"
#include "Roll.h"
#include "Category.h"
#include "Scorecard.h"
#include "Game.h"
#include "LeaderBoard.h"


int main(){
    srand(time(0));
    Game game;
    game.play();
    int score = game.getScore();
    LeaderBoard lb;
    lb.checkAndPrint(score);
    return 0;
}