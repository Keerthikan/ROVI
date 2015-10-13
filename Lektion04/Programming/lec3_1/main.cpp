//
//  main.cpp
//  mapLoading
//
//  Created by Keerthikan Ratnarajah on 07/10/15.
//  Copyright (c) 2015 Keerthikan Ratnarajah. All rights reserved.
//

#include <iostream>
#include<fstream>

using namespace std;

class sokoban{
    int row;
    int col;
    int diamonds;
    char **board;
public:
    sokoban(string file);

};

sokoban::sokoban(string file)
{
    ifstream myReadFile;
    myReadFile.open(file);
    myReadFile >> row;
    myReadFile >> col;
    myReadFile >> diamonds;
    //cout << row << col << diamonds << endl;
    board = new char*[row];
    for (int i = 0; i < col; i++) {
        board[i] = new char[row];
    }
    //char board[col][row];
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            board[i][j] = ' ';
        }
    }
    //GotoLine(myReadFile, 1);
    string str;
    std::getline(myReadFile, str);
    cout << str << endl;
    
    int column = 0;
    int rows = 0;
    while(std::getline(myReadFile, str))
    {
        //cout << str << endl;
        while (rows < str.length())
        {
            //cout << "lenght of string: " << str.length() << " at: " << rows << endl;
            board[column][rows] = str.at(rows);
                
            rows++;
        }
        rows = 0;
        column++;
    }
    for (int i = 0; i < col;  i++) {
        for (int j  = 0; j < row; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
   
}
int main(int argc, const char * argv[]) {
    sokoban test("/Users/keerthikanratnarajah/Desktop/mappe\ uden\ navn/mapLoading/mapLoading/map.txt");
    
    std::cout << "Hello, World!\n";
    return 0;
}

