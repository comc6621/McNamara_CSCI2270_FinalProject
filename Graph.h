// Class for checker board
// Joe Castagneri and Conor McNamara
#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct node;
struct adjNode;

struct node
{
    int row; // Coordinates 1-8
    int column; // Coordinates a-h expressed again as integers 1-8
    bool visited; //Used for transversal
    node *previous; //Used for transversal
    std::string type; // Piece type. b is black, w is white, bk is black king, wk is white king
    std::vector<adjNode> adj; // Vector of adjacent nodes held by each graph node
    
    node () {} // Default constructor
    node (int x, int y, std::string piece) // Constructor for a node using coordinates and a named type of piece
    {
        row = x;
        column = y;
        type = piece; // Piece is a null string if there is no piece on the node
    }
};

struct adjNode
{
    node *v; // Pointer to the adjacent node referred to
    int weight; // Always one, not really necessary but could be expanded if an AI is developed
};

class Graph
{
public:
    Graph(); // Default constructor builds board
    void addNode(int x, int y, std::string type); // Used in constructor, adds nodes to board
    void addEdge(int x1, int y1, int x2, int y2); // Used in constructor, adds edges between nodes
    void printBoard(); // Prints the current state of the board
    bool checkValidMove(node v1, node v2); // Checks if the requested move is legal. If yes, move will be made
    bool checkValidMoveKing(node v1, node v2);//Checks valid move for king
    void makeKing(int x, int y); // Makes a piece into a king
    void makeMove(node* x, node *y); // Moves a piece--also removes taken pieces
    void transversal (int row);
    node* findNode (int y, int x);
    node* getNIL();
    std::vector<int>* getNumWhiteLeft();
    std::vector<int>* getNumBlackLeft();
    void playerTurn(int turnCounter);
    
    
private:
    std::vector<int> numWhiteLeft; // Holds remaining white nodes
    std::vector<int> numBlackLeft; // Holds remaining black nodes
    std::vector<node> squares; // This is poorly named, but it holds all nodes or "squares" on the board
    node* NIL;
};

#endif // GRAPH_H
