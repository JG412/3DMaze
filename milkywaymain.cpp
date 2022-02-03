#include "Pathfinder.h"
using namespace std;

int main(int argc, char* argv[]){
    Pathfinder jimbo;
    for(int i = 0; i < 1; i++){
        jimbo.createRandomMaze();
        cout << jimbo.toString();
        jimbo.solveMaze();
    }
    return 0;
}