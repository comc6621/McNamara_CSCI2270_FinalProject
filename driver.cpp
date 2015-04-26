// Final Project
// Joe Castagneri and Conor McNamara
// Driver for checkerboard project. User interface and class implementation of the graph.

#include <iostream>
#include "Graph.h"

using namespace std;

void printMenu();
int main()
{
    Graph Board; // Initialize the board. This will set up the game
    int userInput;
    bool quit = false; // When they select quit, this value changes and program ends
    while (quit != true)
    {
        printMenu();
        cin >> userInput;
        cin.clear();
        switch (userInput)
        {
            case 1:
            {
                cout << "Greeting player! Welcome to Joe and Conor's Checkers, \nwhere we live for your enjoyment!\nCheckers is a very simple game. Here, we will create an 8x8 board and \nplace 12 white pieces and 12 black pieces on opposite sides.\nThis is a two player version of checkers where play will \nalternate between two users at the terminal. \nThese pieces will all be on \nblack tiles and they will only be able to move diagonally. \nRegular pieces can only move in the forward direction, \nforward being the opposite of the initial spawn point. \nA king is obtained when a piece lands on the opposite side of the board. \nA king can move in any direction, but is still limited to black spaces. \nTo take a piece, you have to diagonally jump over them. \nYou can do double jumps where you take two pieces to capture multiple pieces. \nAfter you take all the opposition's pieces, you win! \nGood luck and may the odds be ever in your favor."<<endl;
                break;
            }
                
            case 2:
            {
                cout << "Good Luck!\n";
                char userInputInGame;
                int turnCounter=0;//Alternates between black and white
                while (userInputInGame !='q')
                {
                    string pieceColor;
                    if (turnCounter==0) {
                        pieceColor= "White's";
                    }
                    if (turnCounter==2) {
                        pieceColor= "Black's";
                    }
                    Board.printBoard();
                    cout <<pieceColor<< " turn! If you wish to quit, hit 'q'. If not press any character \n";
                    cin >> userInputInGame;
                    
                    //FIRST INPUT FIX
                    
                    if (userInputInGame == '\n' || userInputInGame == ' ')
                    {
                        userInputInGame == 'a';
                    }
                    
                    if (userInputInGame == 'q')
                    {
                        quit = true;
                        cout << "Goodbye!\n";
                        break;
                    }
                    
                    Board.playerTurn(turnCounter);
                    
                    if (turnCounter==0) {//Switching turns
                        turnCounter=2;
                    }else{//Switching turns
                        turnCounter=0;
                    }
                    
                }
                if (Board.getNumWhiteLeft()->empty())
                {
                    cout << "Congratulations black, you win!\n";
                }
                else if (Board.getNumWhiteLeft()->empty())
                {
                    cout << "Congratulations white, you win!\n";
                }
                quit = true;
                
                
                
                break;
            }
                
            case 3:
            {
                quit = true;
                cout << "Goodbye!\n";
                break;
            }
                
            default: // If invalid input
            {
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
            }
        }
    }
    return 0;
}

void printMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Rules" << endl;
    cout << "2. Play Checkers" << endl;
    cout << "3. Quit" << endl;
}
