// Class definitions file for checkerboard project--Graph.h
// Joe Castagneri and Conor McNamara
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>// INCLUDE THESE FOR INPUT BUG FIXES

using namespace std;
/*
 Function prototype:
 Graph::Graph()
 
 Function Description:
 The Default Graph Constructor that builds the graph that we shall implement throughout the program
 
 Example:
 Board Graph;
 
 Precondition: 
 The existance of the class Graph, which is defined in the header
 
 Postcondition: 
 Builds entire connected graph with values and edges
    //===========================================================================
    // NOTE: Coordinates are NOT intuitive. They are organized (ROW,COLUMN)
    //       Indices start at 0, so (0,0) corresponds to first row, first column.
    //       This is opposite an (x,y) cartesian graph--(0,6) is first row, seventh
    //       column. You will expect it the other way around but it is not.
    //===========================================================================
 */

Graph::Graph() // Default constructor
{
   
    bool altBool = true;
    // This bool serves as a means to alternate the for loops since the coordinates for the
    // squares on the board switch (ie (0,0),(0,2),(0,6),(1,1),(1,3),(1,5),(1,7),(2,0), etc)
    for (int i = 0; i < 8;  i++) // Runs through ROWS--there are eight from 0-7
    {
        if( altBool == true) // If on row 0,2,4,6
        {
            for (int j = 0; j < 8; j=j+2) // We only want column 0,2,4,6
            {
                if (i < 3) // If on white half of board
                {
                    addNode(i,j," W "); // Build node with coordinates and white type
                }
                else if (i > 4) // If on black side of board
                {
                    addNode(i,j," B ");
                }
                else // If on empty board
                {
                    addNode(i,j,"   ");
                }
                altBool = false; // SWITCH bool for next run through because we need odd numbers next
            }
        }
        
        else // altBool is false, rows 1,3,5,7
        {
            for (int m = 1; m < 8; m = m+2) // We only want columns 1,3,5,7
            {
                if (i < 3) // White side
                {
                    addNode(i,m," W ");
                }
                else if (i > 4) // Black side
                {
                    addNode(i,m," B ");
                }
                else // Neutral
                {
                    addNode(i,m,"   ");
                }
                altBool = true;
            }
        }
    }
    // We now have a set of nodes only pertaining to the relevant coordinates of the board
    //====================================================================================
    //                                 EDGES
    //====================================================================================
    // First, manually insert edges for first row
    addEdge(0,0,1,1);
    addEdge(0,2,1,1);
    addEdge(0,2,1,3);
    addEdge(0,4,1,3);
    addEdge(0,4,1,5);
    addEdge(0,6,1,5);
    addEdge(0,6,1,7);
    
    // Now we can program the rest with for loops except for the last row, so all nodes save the first and last four in squares
    for (int n = 4; n < 28; n++)
    {
        // change case for first/last column--there are no nodes on one of the sides, so we restrict case
        if (n == 7 || n == 15 || n == 23) // Right side of board. These nodes correspond to the n values listed
        {
            addEdge(squares[n].row,squares[n].column,squares[n].row - 1,squares[n].column - 1); // Edge down to the left
            addEdge(squares[n].row,squares[n].column,squares[n].row + 1,squares[n].column - 1); // Edge up to the left
        }
        
        else if (n == 8 || n == 16 || n == 24) // Left side of board, same process
        {
            addEdge(squares[n].row,squares[n].column,squares[n].row - 1,squares[n].column + 1);
            addEdge(squares[n].row,squares[n].column,squares[n].row + 1,squares[n].column + 1);
        }
        
        else // Everything else that has four edges
        {
            addEdge(squares[n].row,squares[n].column,squares[n].row - 1,squares[n].column - 1); // Down left
            addEdge(squares[n].row,squares[n].column,squares[n].row - 1,squares[n].column + 1); // Down right
            addEdge(squares[n].row,squares[n].column,squares[n].row + 1,squares[n].column - 1); // Up left
            addEdge(squares[n].row,squares[n].column,squares[n].row + 1,squares[n].column + 1); // Up right
        }
    }
    // Edges for the last row entered manually
    addEdge(7,1,6,0);
    addEdge(7,1,6,2);
    addEdge(7,3,6,2);
    addEdge(7,3,6,4);
    addEdge(7,5,6,4);
    addEdge(7,5,6,6);
    addEdge(7,7,6,6);
    
    //==========================================================================================
    // This commented printout is for reference if the programmer wishes to understand the structure
    // of this graph. It will print out every node and point to all nodes adjacent to it.
    // It is for reference only and shows the connectivity of this finite graph.
    //==========================================================================================
    /*for (int i = 0; i < squares.size(); i++)
     {
     cout  << squares[i].row<<":"<<squares[i].column << " " << squares[i].type << "-->";
     for (int j = 0; j < squares[i].adj.size()-1; j++)
     {
     cout<<"(" <<squares[i].adj[j].v->row << ":" << squares[i].adj[j].v->column << ") * ";
     }
     cout << "(" << squares[i].adj[squares[i].adj.size()-1].v->row << ":" << squares[i].adj[squares[i].adj.size()-1].v->column << ")" << endl;
     }*/
}
/*
 Function prototype:
 void Graph::addNode(int x, int y, string type)
 
 Function Description:
 Adds a node to the graph
 
 Example:
 int xCordinate, yCordinate;
 string type;
 Board Graph;
 Board.addNode(xCordinate, yCordinate, type);
 
 Precondition:
 Function requires two non negative integers to be sent to it as well as a string. The numbers have to be less than or equal to 7

 
 Postcondition:
 Creates a new node with the values that the function recieved and adds the new node to the Graph
 */
void Graph::addNode(int x, int y, string type)
{
    node newNode(x,y,type); // Build new node with node constructor and add it to squares
    squares.push_back(newNode);
    if (type == " W ") // Adds node to remaining white vector if it is a white node
    {
        numWhiteLeft.push_back(newNode.row);
    }
    if (type == " B ") // Adds node to remaining black vector if it is a black node
    {
        numBlackLeft.push_back(newNode.row);
    }
}
/*
 Function prototype:
 void Graph::addEdge(int x1, int y1, int x2, int y2)
 
 Function Description:
 Adds a edge between nodes on the graph
 
 Example:
 int node1xCordinate, node1yCordinate, node2xCordinate, node2yCordinate;
 Board Graph;
 Board.addEdge(node1xCordinate, node1yCordinate, node2xCordinate, node2yCordinate);
 
 Precondition:
 Function requires four non negative integers to be sent to it. The numbers have to be less than or equal to 7
 
 Postcondition:
 Creates a new edge between nodes with the values that the function recieved and, in doing so connects the nodes together, thus helping to build the connected graph
 */
void Graph::addEdge(int x1, int y1, int x2, int y2)
{
    for (int i = 0; i < squares.size(); i++)
    {
        if (squares[i].row == x1 && squares[i].column == y1) // Find node defined by (x1,y1)
        {
            for (int j = 0; j < squares.size(); j++)
            {
                if (squares[j].row == x2 && squares[j].column == y2 && i != j) // Find node defined by (x2,y2)
                {
                    adjNode newEdge;
                    newEdge.v = &squares[j]; // Make new node point at (x2,y2)
                    newEdge.weight = 1; // Set weight. Could be used for AI
                    squares[i].adj.push_back(newEdge); // Add adjNode to (x1,y1) adj vector
                }
            }
        }
    }
}
/*
 Function prototype:
 void Graph::transversal(int row)
 
 Function Description:
 Transverses the graph and prints it one row
 
 Example:
 int row;
 Board Graph;
 Board.transversal(int row);
 
 Precondition:
 Function requires a non negative integer to be sent to it. The number has to be less than or equal to 7
 
 Postcondition:
 Stores the nodes that are in the row and prints the values of the nodes in order and in a form that resembels a checker board
 */
void Graph::transversal(int row){
    node *x;
    node *u;
    node arr[100];
    vector<node> print;
    int h =0;
    int t=0;
    //Set Visited to False
    for (int p=0; p<squares.size();p++){
        squares[p].visited=false;
        squares[p].previous=NULL;
    }
    //Set Starting Values and put it in Q
    squares[0].visited=true;
    arr[h]=squares[0];
    arr[h].previous=NULL;
    if (row ==0) {
        print.push_back(arr[h]);
    }
    t++;
    while(h!=t){
        x=&arr[h];
        h++;
        //Loop through Adjacents
        for (int y=0; y<x->
             adj.size();y++){
            //If adj hasnt been visited
            if (x->adj[y].v->visited==false){
                x->adj[y].v->visited=true;
                //Set previous equal to the value ahead of it in the array
                x->adj[y].v->previous=&arr[h-1];
                //If the adj is the distination
                if (x->adj[y].v->row==row) {
                    arr[t]=*x->adj[y].v;
                    u=x->adj[y].v;
                    print.push_back(*u);
                    t++;
                }else if(x->adj[y].v->row!=row){
                    arr[t]=*x->adj[y].v;
                    t++;
                }
            }
        }
    }
    //Print
    if (row==7 ||row==5 ||row==3||row==1) {
        cout<<row<<" |///|"<<print[0].type<<"|///|"<<print[1].type<<"|///|"<<print[2].type<<"|///|"<<print[3].type<<"|"<<endl;
        cout<<"  ---------------------------------"<<endl;
    }if (row==6 ||row==4 ||row==2||row==0) {
        cout<<row<<" |"<<print[0].type<<"|///|"<<print[1].type<<"|///|"<<print[2].type<<"|///|"<<print[3].type<<"|///|"<<endl;
        cout<<"  ---------------------------------"<<endl;
    }
}
/*
 Function prototype:
 void Graph::printBoard()
 
 Function Description:
 Prints the board using the transversal function and sending specific rows to it while building the score system below it
 
 Example:
 Board Graph;
 Board.printBoard();
 
 Precondition:
 The existance of the class Graph, which is defined in the header along with the graph being built
 
 Postcondition:
 Calss transversal 8 times and prints the entire board in order with rows and columns and a score board
 */
void Graph::printBoard (){
    cout<<"  ---------------------------------"<<endl;
    transversal(7);
    transversal(6);
    transversal(5);
    transversal(4);
    transversal(3);
    transversal(2);
    transversal(1);
    transversal(0);
    cout<<"    0   1   2   3   4   5   6   7"<<endl;
    cout<<"      Black: "<<numBlackLeft.size()<<"     White: "<<numWhiteLeft.size()<<endl;
    
}
/*
 Function prototype:
 node* Graph::getNIL();
 
 Function Description:
 Returns a node whoes value is NIL. Is helpful for resetting values
 
 Example:
 Board Graph;
 node* nilNode = Board.getNil();
 
 Precondition:
 The existance of the class Graph, which is defined in the header along with the definition of a structure called node
 
 Postcondition:
 Returns a node that is NIL
 */
node* Graph::getNIL()
{
    return NIL;
}
/*
 Function prototype:
 std::vector<int>* Graph::getNumWhiteLeft();
 
 Function Description:
 Returns a vector of ints which is the size of all of the nodes of type 'White' remaining. Used for scoring system
 
 Example:
 Board Graph;
 vector<int> whiteRemaining= Board.getNumWhiteLeft;
 
 Precondition:
 The existance of the class Graph, which is defined in the header and creates the vector numWhiteLeft
 
 Postcondition:
 Returns a vector whose size is the number of white nodes remaining
 */
std::vector<int>* Graph::getNumWhiteLeft()
{
    return &numWhiteLeft;
}
/*
 Function prototype:
 std::vector<int>* Graph::getNumBlackLeft();
 
 Function Description:
 Returns a vector of ints which is the size of all of the nodes of type 'Black' remaining. Used for scoring system
 
 Example:
 Board Graph;
 vector<int> blackRemaining= Board.getNumBlackLeft;
 
 Precondition:
 The existance of the class Graph, which is defined in the header and creates the vector numBlackLeft
 
 Postcondition:
 Returns a vector whose size is the number of black nodes remaining
 */
std::vector<int>* Graph::getNumBlackLeft()
{
    return &numBlackLeft;
}
/*
 Function prototype:
 node* Graph::findNode(int row, int column);
 
 Function Description:
 Transverses the graph and returns a node with the same row and column value that are sent to it
 
 Example:
 int row, column;
 Board Graph;
 node* newNode= Board.findNode(row, column);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires a non negative integer to be sent to it. The number has to be less than or equal to 7
 Postcondition:
 Returns a node whose row and column are the same as the values passed to the function
 */
node* Graph::findNode (int row, int column){
    node *x = new node;
    x = NIL;
    for (int p=0; p<squares.size();p++){
        if (squares[p].row == row && squares[p].column==column) {
            x = &squares[p];
        }
    }
    return x;
}
/*
 Function prototype:
 void Graph::playerTurn(int turnCounter)
 
 Function Description:
 Function runs a players turn, getting a location of the piece they wish to move, making sure it is their peice, getting a destination location and then passing the pieces to check funtions that will see if the move is valid and, if it is, making the move
 
 Example:
 int turnCounter;
 Board Graph;
 Board.playerTurn(turnCounter);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires a non negative integer to be sent to it. The number is either 0 or 2
 Postcondition:
 Runs a players turn, promting them for values of their piece location and desired location and calls check funtions based on the type of piece and moves the piece if it passes all checks
 */
void Graph::playerTurn(int turnCounter)
{
    string r1,c1;
    int row1,col1;
    int tracer=0;
    node* t= new node;
    t = NIL; // Start t node as nil
    while (t == NIL) // While t remains nil (while input is invalid)
    {
        tracer=0; //reset tracer
        
        while (true)
        {
            cout<<"Enter the row of your piece"<<endl;
            cin >> r1;
            cout<<"Enter the column of your piece"<<endl;
            cin >> c1;
            
            // This code converts from string to number safely.
            stringstream myStream(r1);
            stringstream myStream2(c1);
            if (myStream >> row1 && myStream2 >> col1)
                break;
            cout << "Invalid number(s), please try again" << endl;
        }
        t = findNode(row1,col1); // Find node for first piece
        
        if (t == NIL) {// If nil returned, piece is not valid
            cout<<"Piece not found"<<endl;
            tracer=1;
        }if (turnCounter==0&&tracer==0) {//If whites turn
            if (t->type==" B "||t->type=="B K") {//If found piece is black
                cout<<"The piece you entered is not a white piece\n";
                t=NIL;
                tracer=1;
            }
        }else if (turnCounter==2&&tracer==0) {//If blacks turn
            if (t->type==" W "||t->type=="W K") {//If found piece is white
                cout<<"The piece you entered is not a black piece\n";
                t=NIL;
                tracer=1;
            }
        }if (tracer==0&&t->type=="   ") {//Check for empty piece, order matters here
            cout<<"No piece in your square"<<endl;
            t=NIL;
            tracer=1;
        }
        if (tracer==0) // If found get destination
        {
            string r2,c2; // FOR BUG FIX
            int row2,col2; // FOR BUG FIX
            node* d=new node;
            //    BUG FIX
            while (true)
            {
                cout<<"Enter the destination row of your piece"<<endl;
                cin >> r2;
                cout<<"Enter the destination column of your piece"<<endl;
                cin >> c2;
                
                // This code converts from string to number safely.
                stringstream myStream(r2);
                stringstream myStream2(c2);
                if (myStream >> row2 && myStream2 >> col2)
                    break;
                cout << "Invalid number(s), please try again" << endl;
            }
            d = findNode(row2,col2); // Find destination
            
            if (d != NIL) // If destination is valid node
            {
                if (t->type==" B "||t->type==" W ") {//If regular piece
                    if (checkValidMove(*t,*d)) // Check if move is legal, if yes, make move for piece
                    {
                        makeMove(t,d);
                    } else { // If invalid move
                        cout << "Invalid move\n";
                        t = NIL; // Reset t so move is remade
                    }
                }else if(t->type=="W K" ||t->type == "B K"){//If King
                    if (checkValidMoveKing(*t, *d)) {//Check if move is legal, if yes, make move for king
                        makeMove(t, d);
                    } else { // If invalid move
                        cout << "Invalid move\n";
                        t = NIL; // Reset t so move is remade
                    }
                }
                else { // If invalid move
                    cout << "Invalid move\n";
                    t = NIL; // Reset t so move is remade
                }
            }
            else{ // destination square doesn't exist
                cout << "Invalid destination square\n";
                t = NIL; // Continue while loop for re move
            }
        }
    }
}
/*
 Function prototype:
 bool Graph::checkValidMove(node v1, node v2);
 
 Function Description:
 Check to see if move from node 1 to node 2 is a valid move for a regular piece
 
 Example:
 node v1, v2;
 Board Graph;
 bool isMoveValid = Board.checkValidMove(v1,v2);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires two non NIL nodes to be sent to it
 Postcondition:
 Returns 'true' if the move is legal and 'false' if the move is illegal
 */
bool Graph::checkValidMove(node v1, node v2) // Checks if requested move is legal for regular pieces
{
    bool validMove = false;
    node *x = new node;
    int r1,r2,c1,c2; // Pull rows, columns of nodes
    r1 = v1.row;
    c1 = v1.column;
    r2 = v2.row;
    c2 = v2.column;
    
    if (v1.type == " W ")// If white piece
    {
        if (r2 == r1+1) // If we jump up a row
        {
            if (c2 == c1+1 || c2 == c1-1) // If we slide over a column
            {
                if (v2.type == "   ") // If dest is empty
                {
                    validMove = true; // Good move
                }
                
            }
        }
        else if (r2 == r1 + 2) // If it jumps a piece
        {
            if (c2 == c1 + 2) // Case 1, up to right
            {
                x = findNode(r1+1,c1+1); // Grab intermediate node
                if (x->type != "   " && x->type != " W " && x->type != "W K") // Intermediate node can't be empty or same color
                {
                    if (v2.type == "   ") // If dest is empty
                    {
                        validMove = true; // Good move
                    }
                }
            }
            if (c2 == c1 - 2) // Case 2, up to left
            {
                x = findNode(r1+1,c1-1);
                if (x->type != "   " && x->type != " W " && x->type != "W K") // Check color of intermediate node
                {
                    if (v2.type == "   ")
                    {
                        validMove = true;
                    }
                }
                
            }
        }
    }
    else if (v1.type == " B ")// Black pieces, same process
    {
        if (r2 == r1-1) // If we jump down a row
        {
            if (c2 == c1+1 || c2 == c1-1) // If we slide over a column
            {
                if (v2.type == "   ")
                {
                    validMove = true;
                }
                
            }
        }
        else if (r2 == r1 - 2) // If it jumps a piece
        {
            if (c2 == c1 + 2) // Case 1, down to right
            {
                x = findNode(r1-1,c1+1);
                if (x->type != "   " && x->type != " B " && x->type != "B K")
                {
                    if (v2.type == "   ")
                    {
                        validMove = true;
                    }
                }
            }
            if (c2 == c1 - 2) // Case 2, down to left
            {
                x = findNode(r1-1,c1-1);
                if (x->type != "   " && x->type != " B " && x->type != "B K")
                {
                    if (v2.type == "   ")
                    {
                        validMove = true;
                    }
                }
            }
        }
    }
    return validMove;
}
/*
 Function prototype:
 void Graph::makeMove(node* x, node* y)
 
 Function Description:
 Makes the move from node x to node y. It calls the makeKing function if a move is made so a piece becomes a king. Also handles the case of jumping peices and doing a double or triple jump as well

 
 Example:
 node v1, v2;
 Board Graph;
 Board.makeMove(v1,v2);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires two non NIL nodes to be sent to it
 Postcondition:
 Changes the value of node y to be node x and leaves node x black. If necessary, it makes a king and, if a piece is jumped, it eliminates the jumped piece and also goes into the double jump option
*/
void Graph::makeMove(node* x, node* y)
{
    node* z = new node;
    
    if (x->type== " W " && y->row ==7) {//King a white piece
        makeKing(x->row, x->column);
    }
    if (x->type== " B " && y->row ==0) {//King a black piece
        makeKing(x->row, x->column);
    }
    y->type = x->type; // Moves piece
    x->type = "   "; // Deletes piece from prior placement
    if (y->row == x->row + 2 && y->column == x->column + 2) // If jumping up to right
    {
        z = findNode(x->row+1,x->column+1); // Set z as intermediate, jumped node
    }
    else if (y->row == x->row - 2 && y->column == x->column - 2) // Jumping down to the left
    {
        z = findNode(x->row - 1, x->column - 1);
    }
    else if (y->row == x->row + 2 && y->column == x->column - 2) // Jumping Up to left
    {
        z = findNode(x->row + 1, x->column - 1);
        //cout << z->row << " " << z->column << endl;
    }
    else if (y->row == x->row - 2 && y->column == x->column + 2) // Jumping Down to right
    {
        z = findNode(x->row - 1, x->column + 1);
    }
    // END OF ASSIGNMENT CLAUSES TO Z
    char userInput;
    if (z->type == " W " || z->type == "W K") // If z is white, remove a white piece from count
    {
        cout<<"Black takes a white piece! Would you like to make another jump? (y/n)"<<endl;
        cin>>userInput;
        
        while (userInput != 'y' && userInput != 'n')
        {
            cout << "Invalid Input\n";
            cin >> userInput;
        }
        if (userInput=='y') {
            node* t=new node;
            t=NIL;
            while (t==NIL){
                t=y;
                string r2,c2; // FOR BUG FIX
                int row2,col2; // FOR BUG FIX
                node* d=new node;
                //    BUG FIX
                while (true)
                {
                    cout<<"Enter the destination row of your piece"<<endl;
                    cin >> r2;
                    cout<<"Enter the destination column of your piece"<<endl;
                    cin >> c2;
                    
                    // This code converts from string to number safely.
                    stringstream myStream(r2);
                    stringstream myStream2(c2);
                    if (myStream >> row2 && myStream2 >> col2)
                        break;
                    cout << "Invalid number(s), please try again" << endl;
                }
                d = findNode(row2,col2); // Find destination
                
                if (d != NIL) // If destination is valid node
                {
                    if (t->type==" B "||t->type==" W ") {//If regular piece
                        if (checkValidMove(*t,*d)) // Check if move is legal, if yes, make move for piece
                        {
                            makeMove(t,d);
                        } else { // If invalid move
                            cout << "Invalid move\n";
                            cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                            cin>>userInput;
                            while (userInput != 'y' && userInput != 'n')
                            {
                                cout << "Invalid Input\n";
                                cin >> userInput;
                            }
                            if (userInput=='y') {//IF they want to continue, send them trough loop again
                                t=NIL;
                            }else{//If they dont, break both loops
                                t=y;
                            }
                        }
                    }else if(t->type=="W K" ||t->type == "B K"){//If King
                        if (checkValidMoveKing(*t, *d)) {//Check if move is legal, if yes, make move for king
                            makeMove(t, d);
                        } else { // If invalid move
                            cout << "Invalid move\n";
                            cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                            cin>>userInput;
                            while (userInput != 'y' && userInput != 'n')
                            {
                                cout << "Invalid Input\n";
                                cin >> userInput;
                            }
                            if (userInput=='y') {//IF they want to continue, send them trough loop again
                                t=NIL;
                            }else{//If they dont, break both loops
                                t=y;
                            }
                        }
                    }
                    else { // If invalid move
                        cout << "Invalid move\n";
                        cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                        cin>>userInput;
                        while (userInput != 'y' && userInput != 'n')
                        {
                            cout << "Invalid Input\n";
                            cin >> userInput;
                        }
                        if (userInput=='y') {//IF they want to continue, send them trough loop again
                            t=NIL;
                        }else{//If they dont, break both loops
                            t=y;
                        }
                    }
                }
                else{ // destination square doesn't exist
                    cout << "Invalid destination square\n";
                    cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                    cin>>userInput;
                    while (userInput != 'y' && userInput != 'n')
                    {
                        cout << "Invalid Input\n";
                        cin >> userInput;
                    }
                    if (userInput=='y') {//IF they want to continue, send them trough loop again
                        t=NIL;
                    }else{//If they dont, break both loops&
                        t=y;
                    }
                }
            }
        }
        numWhiteLeft.pop_back();
    }
    else if (z->type == " B " || z->type == "B K")
    {//If z is black, remove a black piece from count
        string p;
        cout<<"White takes a black piece! Would you like to make another jump? (y/n)"<<endl;
        cin>>userInput;
        while (userInput != 'y' && userInput != 'n')//changed to and
        {
            cout << "Invalid Input\n";
            cin >> userInput;
        }
        if (userInput=='y') {
            node* t=new node;
            t=NIL;
            while (t==NIL){
                t=y;
                string r2,c2; // FOR BUG FIX
                int row2,col2; // FOR BUG FIX
                node* d=new node;
                //    BUG FIX
                while (true)
                {
                    cout<<"Enter the destination row of your piece"<<endl;
                    cin >> r2;
                    cout<<"Enter the destination column of your piece"<<endl;
                    cin >> c2;
                    
                    // This code converts from string to number safely.
                    stringstream myStream(r2);
                    stringstream myStream2(c2);
                    if (myStream >> row2 && myStream2 >> col2)
                        break;
                    cout << "Invalid number(s), please try again" << endl;
                }
                d = findNode(row2,col2); // Find destination
                
                if (d != NIL) // If destination is valid node
                {
                    if (t->type==" B "||t->type==" W ") {//If regular piece
                        if (checkValidMove(*t,*d)) // Check if move is legal, if yes, make move for piece
                        {
                            makeMove(t,d);
                        } else { // If invalid move
                            cout << "Invalid move\n";
                            cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                            cin>>userInput;
                            while (userInput != 'y' && userInput != 'n')
                            {
                                cout << "Invalid Input\n";
                                cin >> userInput;
                            }
                            if (userInput=='y') {//IF they want to continue, send them trough loop again
                                t=NIL;
                            }else{//If they dont, break both loops
                                t=y;
                            }
                        }
                    }else if(t->type=="W K" ||t->type == "B K"){//If King
                        if (checkValidMoveKing(*t, *d)) {//Check if move is legal, if yes, make move for king
                            makeMove(t, d);
                        } else { // If invalid move
                            cout << "Invalid move\n";
                            cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                            cin>>userInput;
                            while (userInput != 'y' && userInput != 'n')
                            {
                                cout << "Invalid Input\n";
                                cin >> userInput;
                            }
                            if (userInput=='y') {//IF they want to continue, send them trough loop again
                                t=NIL;
                            }else{//If they dont, break both loops
                                t=y;
                            }
                        }
                    }
                    else { // If invalid move
                        cout << "Invalid move\n";
                        cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                        cin>>userInput;
                        while (userInput != 'y' && userInput != 'n')
                        {
                            cout << "Invalid Input\n";
                            cin >> userInput;
                        }
                        if (userInput=='y') {//IF they want to continue, send them trough loop again
                            t=NIL;
                        }else{//If they dont, break both loops
                            t=y;
                        }
                    }
                }
                else{ // destination square doesn't exist
                    cout << "Invalid destination square\n";
                    cout << "Do you want to continue the double jump function? (y/n)"<<endl;//Give them option to quit
                    cin>>userInput;
                    while (userInput != 'y' && userInput != 'n')
                    {
                        cout << "Invalid Input\n";
                        cin >> userInput;
                    }
                    if (userInput=='y') {//IF they want to continue, send them trough loop again
                        t=NIL;
                    }else{//If they dont, break both loops
                        t=y;
                    }
                }
            }
        }
    numBlackLeft.pop_back();
    }
    z->type = "   "; // Set z to empty
}
/*
 Function prototype:
 void Graph::makeKing(row, column)
 
 Function Description:
 Makes the node with the condinates sent into the funtion into a type king
 
 
 Example:
 int row, column;
 Board Graph;
 Board.makeMove(row, column);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires two non negative numbers that are less than or equal to 7
 Postcondition:
 Changes the type of the node to that of a king
 */
void Graph::makeKing(int row, int column)
{
    node *x =findNode(row, column);
    if (x->type==" W ") {
        x->type="W K";
    }else if (x->type == " B "){
        x->type="B K";
    }
}
/*
 Function prototype:
 bool Graph::checkValidMoveKing(node v1, node v2);
 
 Function Description:
 Check to see if move from node 1 to node 2 is a valid move for a king
 
 Example:
 node v1, v2;
 Board Graph;
 bool isMoveValid = Board.checkValidMoveKing(v1,v2);
 
 Precondition:
 The existance of the class Graph, which is defined in the header and the graph to be built. It also requires two non NIL nodes to be sent to it
 Postcondition:
 Returns 'true' if the move is legal and 'false' if the move is illegal
 */
bool Graph::checkValidMoveKing(node v1, node v2){//Checks to see if king move is valid
    bool validMove = false;
    int r1,r2,c1,c2; // Pull rows, columns of nodes
    r1 = v1.row;
    c1 = v1.column;
    r2 = v2.row;
    c2 = v2.column;
    
    if (r2 == r1+1) // If we jump up a row
    {
        if (c2 == c1+1 || c2 == c1-1) // If we slide over a column
        {
            if (v2.type == "   ") // If dest is empty
            {
                validMove = true; // Good move
            }
            
        }
    }if (r2 == r1-1) // If we jump down a row
    {
        if (c2 == c1+1 || c2 == c1-1) // If we slide over a column
        {
            if (v2.type == "   ")
            {
                validMove = true;
            }
            
        }
    }if (r2==r1+2||r2==r1-2) {//Jumping a piece row is up or down 2
        if (c2==c1+2||c2==c1-2) {//Jumping column move right or left 2
            if (v2.type=="   ") {//Empty square
                validMove=true;
            }
        }
    }
    return validMove;
}
