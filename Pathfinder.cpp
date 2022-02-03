#include "Pathfinder.h"

using namespace std;

string Pathfinder::toString() const{
    
    if (!existingMaze) { // makes a string to return if a mazeReal has not been created yet
        string fakeMaze = "";
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
                    if (k < N - 1){
                        fakeMaze += "1 ";
                    } else {
                        fakeMaze += "1";
                    }
                }
                if (j < N - 1){
                    fakeMaze += "\n";
                }
            }
            if (i < N - 1){
                fakeMaze += "\n\n";
            }
        } 
        cout << "FAAAAAAAKE ALERT ALERT ALERT" << endl;
        fakeMaze += '\n';
        return fakeMaze;

    } else {return repMaze;} // returns the string representation of the mazeReal
}

void Pathfinder::createRandomMaze(){
    string ranMaze;
    created = false;
    valid = false;
    int cellR;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                cellR = rand() % 2;
                if(i == 0 && j == 0 && k == 0 || i == 4 && j == 4 && k == 4){
                    cellR = 1;
                }
                mazeReal[i][j][k] = cellR;
                ranMaze += to_string(cellR);
                if (k < N - 1){
                    ranMaze += ' ';
                }
            } if (j < N - 1){ranMaze += '\n';}
        } if (i < N - 1){ranMaze += "\n\n";}
    }
    ranMaze += '\n';
    existingMaze = true;
    created = true;
    valid = true;
    repMaze = ranMaze;
}

bool Pathfinder::importMaze(string file_name){
    newSolve = true;
    ifstream in(file_name);
    int cell;
    count = 0;
    sumTotal = 0;
    created = false;
    valid = false;
    string newMaze;
    solution.clear();

    if(!in.is_open()){
        cout << "\nFile " << file_name << " could not open\n"; 
        created = false;
        return created;

    } else {
        newMaze = "";
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
                    if(!in.eof()){
                        in >> skipws >> cell;
                        if(cell > 1 || cell < 0){
                            //cout << endl << cell*2 << endl;
                            created = false;
                            return created;
                        }
                        count += 1;
                        sumTotal += cell;

                        maze[i][j][k] = cell;

                        newMaze += to_string(cell);
                        if(k < N - 1){newMaze += ' ';}
                    } else {break;}
                }
                if(j < N - 1){newMaze += '\n';}
            }
            if(i < N - 1){newMaze += "\n\n";}
        } 
        newMaze += '\n';
        if(in.eof() && checkValid()){
            created = true; 
            existingMaze = true;
            repMaze = newMaze;
            copyMaze(maze, mazeReal);
        } else {created = false;} 
    }
    return created;
}

vector <string> Pathfinder::solveMaze(){
    int unsolvable = 0;

    if(mazeReal[4][4][3] != 1 && mazeReal[4][3][4] != 1 && mazeReal[3][4][4] != 1){
        cout << "NO SOLUTION" << endl;
        solution.clear();
        return solution;
    }
    
    if(solution.empty() && newSolve){
        newSolve = false;
        x = 0, y = 0, z = 0;
        copyMaze(mazeReal, mazeCopy);
        current = &mazeCopy[0][0][0];
    }

    string coordinates = "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";

    solution.push_back(coordinates);

    if(!solution.empty() && x+y+z == 12){
        
        cout << "\nSOLVED!!!\n" << endl;
        return solution;
    }
    
    if(mazeCopy[0][0][0] == 1 || mazeCopy[4][4][4] == 1 && existingMaze){
        int fORb; // 1 will be the first hit if backtracking it will be 3
        if(backTrack){
            *current = 6;
            fORb = 3;
            solution.pop_back();
            backTrack = false;
        } else {
            *current = 3; 
            fORb = 1;
        }

        if(x < N - 1 && mazeCopy[z][y][x + 1] == fORb){ // east
            x += 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();

        } if(y < N - 1 && mazeCopy[z][y + 1][x] == fORb){ // south
            y += 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();

        } if(z < N - 1  && mazeCopy[z + 1][y][x] == fORb){ // down one layer
            z += 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();

        } if(x > 0 && mazeCopy[z][y][x - 1] == fORb){ // west
            x -= 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();

        } if(y > 0 && mazeCopy[z][y - 1][x] == fORb){ // north
            y -= 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();

        } if(z > 0 && mazeCopy[z - 1][y][x] == fORb){ // up one layer
            z -= 1;
            current = &mazeCopy[z][y][x];
            return solveMaze();
        }
        
        //unsolvable edition
        if(x < N - 1 && mazeCopy[z][y][x + 1] == 6 || mazeCopy[z][y][x + 1] == 0){ // east
            unsolvable += 1;
        } if(y < N - 1 && mazeCopy[z][y + 1][x] == 6 || mazeCopy[z][y + 1][x] == 0){ // south
            unsolvable += 1;
        } if(z < N - 1  && mazeCopy[z + 1][y][x] == 6 || mazeCopy[z + 1][y][x] == 0){ // down one layer
            unsolvable += 1;
        } if(x > 0 && mazeCopy[z][y][x - 1] == 6 || mazeCopy[z][y][x - 1] == 0){ // west
            unsolvable += 1;
        } if(y > 0 && mazeCopy[z][y - 1][x] == 6 || mazeCopy[z][y - 1][x] == 0){ // north
            unsolvable += 1;
        } if(z > 0 && mazeCopy[z - 1][y][x] == 6 || mazeCopy[z - 1][y][x] == 0){ // up one layer
            unsolvable += 1;
        }
        if(x > 0 && x < 5 && y > 0 && y < 5 && z > 0 && z < 5){
            if(unsolvable >= 5){
                cout << "NO SOLUTION" << endl;
                solution.clear();
                return solution;
            }
        } 
        if(mazeCopy[4][4][4] == 1 ){
            backTrack = true;
            return solveMaze();
        }
    }
    cout << "Something didn't go according to plan" << endl;
    solution.push_back("whoops");
    return solution;
}

bool Pathfinder::checkValid(){
    if(maze[0][0][0] == 1 && maze[4][4][4] == 1 && count == 125){
        valid = true;
    } else {valid = false;}

    return valid;
}

void Pathfinder::copyMaze(int maze2Bcopied[N][N][N], int (&copiedMaze)[N][N][N]){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                copiedMaze[i][j][k] = maze2Bcopied[i][j][k];
            }
        }
    }
}


void Pathfinder::printMazeCopy(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                cout << mazeCopy[i][j][k] << " ";
            } cout << endl;
        } cout << endl;
    } cout << endl;
}

