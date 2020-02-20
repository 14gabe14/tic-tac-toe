/*Name: Gabriela Peralta
Student ID: 110016671
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Q1
void InitializeBoard(int m, int n, char board[][n]){
    int c = 1;
    for(int i =0; i<m; i++){
        for(int j=0; j< n; j++){
            board[i][j] = c+'0';
            c++;
        }
    }
}
//Q2
void PrintBoard(int m, int n, char board[][n]){
    printf("\n     |     |   \n");
    printf("  %c  |  %c  |  %c \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |   \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |   \n\n");
}
//Q3
void CreateBoard(int m, int n, char board[][n]){
    InitializeBoard(m, n, board);
    PrintBoard(m, n, board);
    int c; //cell
    char val; //X or O
    do{ 
        printf("Enter the number of the cell number where you want to insert 'X' or 'O' or enter -1 to exit: ");
        scanf("%d", &c);
    }while((c>9||c<1)&&(c!=-1));
    while(c != -1){
        do{
            printf("Enter X or O: ");
            scanf(" %c", &val);
        }while(val!='X' && val!='O' && val !='x' && val != 'o');
        board[(c-1)/3][(c-1)%3] = toupper(val);
        PrintBoard(m, n, board);
        do{ 
            printf("Enter the number of the cell number where you want to insert 'X' or 'O' or enter -1 to exit: ");
            scanf("%d", &c);
        }while((c>9||c<1)&(c!=-1));
    }
}
//Q4
int IsValidBoard(int m, int n, char board[][n]){
    //counts number of Xs and Os
    int x = 0, o = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] == 'X'){
                x += 1;
            }else if(board[i][j] == 'O'){
                o += 1;
            }
        }
    }
    //If difference between Xs and Os is equal to 0, 1 or -1, the board is valid
    int dif = abs(x - o);
    if(dif == 1 || dif == 0){
        return 1;
    }else{
        return 0;
    }
}
//Q5
//see function ListWinningCells below first
void EvaluateWinningCells(int xo, char blank_cell, int p, int winningCells[][p]){
    //xo is the difference between Xs and Os in a row, column or diagonal
    //xo = #X - #O
    //blank_cell is the empty cell
    if(xo == 2){
        winningCells[0][blank_cell - '0' - 1] = 1;
    }else if(xo == -2){
        winningCells[1][blank_cell - '0' - 1] = 1;
    }
}
void PrintWinningMoves(char XO, int p, int winningCells[][p]){
    //This function prints winning moves for X or O
    int xORo;   //variable used to convert character XO (either 'X' or 'O') to 1 or 0
                //in order to be used in the list of winning cells
    if(XO == 'X'){
        xORo = 0;
    }else if(XO == 'O'){
        xORo = 1;
    }
    int a = 0;
    printf("\nCell ");
    for(int i = 0; i < p; i++){
        if(winningCells[xORo][i] == 1){
            if(a > 0){
                printf("and ");
            }
            printf("# %d ", i + 1);
            a++;
        }
    }
    if(a > 1){
        printf("are winning cells for ");
    }if(a == 1){
        printf("is a winning cell for ");
    }
    printf("player %c.\n", XO);
}

int HasWinningMoves(int p, int winningCells[][p]){
    int x = 0, o = 0;
    for(int i = 0; i < p; i++){
        if(winningCells[0][i] == 1){
            x++;
        }
        if(winningCells[1][i] == 1){
            o++;
        }
    }
    if(x > 0){
        PrintWinningMoves('X', p, winningCells);
    }
    if(o > 0){
        PrintWinningMoves('O', p, winningCells);
    }
    if(x == 0 && o == 0){
        printf("No winning cells for X or O\n");
    }
}

void ListWinningCells(int m, int n, char board[][n]){
    if(IsValidBoard(m, n, board) == 1){
        int winningCells[2][9] = {0};   
        //X is first row
        //O is second row
        //value of 1 indicates index is a winning cell for either X or O
        int xo = 0; //value will change by evaluating each row or column 
                    //positive value indicates there are more Xs than Os
                    //negative value indicates more Os than Xs
                    //0 means equal number
        char blank_cell;
        for(int r = 0; r < m; r++){ //this for loop evaluates every row
            for(int i = 0; i < n; i++){
                if(board[r][i] == 'X'){
                    xo += 1;
                }else if(board[r][i] == 'O'){
                    xo -= 1;
                }else{
                    blank_cell = board[r][i];
                }
            }
            EvaluateWinningCells(xo, blank_cell, 9, winningCells);
            xo = 0;
        }
        for(int c = 0; c < n; c++){ //this for loop evaluates every column
            for(int j = 0; j < m; j++){
                if(board[j][c] == 'X'){
                    xo += 1;
                }else if(board[j][c] == 'O'){
                    xo -= 1;
                }else{
                    blank_cell = board[j][c];
                }
            }
            EvaluateWinningCells(xo, blank_cell, 9, winningCells);
            xo = 0;
        }
        for(int k = 0; k < n; k++){ // this for loop evaluates a diagonal (\)
            if(board[k][k] == 'X'){
                xo += 1;
            }else if(board[k][k] == 'O'){
                xo -= 1;
            }else{
                blank_cell = board[k][k];
            }
        }
        EvaluateWinningCells(xo, blank_cell, 9, winningCells);
        xo = 0;
        for(int k = 0; k < n; k++){//this for loop evaluates another diagonal (/)
            if(board[k][2-k] == 'X'){
                xo += 1;
            }else if(board[k][2-k] == 'O'){
                xo -= 1;
            }else{
                blank_cell = board[k][2-k];
            }
        }
        EvaluateWinningCells(xo, blank_cell, 9, winningCells);
        xo = 0;
        HasWinningMoves(9, winningCells);
    }else{
        printf("We can't predict the winning cells because the board is not valid.\n");
    }
}
//Question 6
int IsTheSameVal(int x_1, int y_1, int x_2, int y_2, int count, int m, int n, char board[][n]){
    //this function determines if there are three same values (X or O) in a line
    //this function only proceeds if two adjacent items are the same
    if(count == 3){
        return 1;
    }else{
        if(board[x_1][y_1] == board[x_2][y_2]){
            return IsTheSameVal(x_2, y_2, x_2 * 2 - x_1, y_2 * 2 - y_1, count + 1, m, n, board);
            //Compares next item in line
        }else{
            return 0;
        }
    }
}

int ThreeInALine(int x, int y, int m, int n, char board[][n]){
    //This function evaluates whether a line has the same value in a row, column or diagonal.
    //Since there are only 8 distinct lines that a player can make to win the game,
    //the function takes only positions 1, 2, 3, 4 and 7 as the starting positions in order to
    //evaluate them as diagonal, column or row

    int count = 1;
    if(x == 0 && y == 0){ //evaluates diagonal (\)
        if(IsTheSameVal(x, y, x + 1, y + 1, count, m, n, board) == 1){
            return 1;
        }
    }
    if(x == 0){ //evaluates all columns
        if(IsTheSameVal(x, y, x + 1, y, count, m, n, board) == 1){
            return 1;
        }
    }
    if(y == 0){ //evaluates all rows
        if(IsTheSameVal(x, y, x, y + 1, count, m, n, board) == 1){
            return 1;
        }
    }
    if(x == 0 && y == 2){//evaluates diagonal (/)
        if(IsTheSameVal(x, y, x + 1, y - 1, count, m, n , board) == 1){
            return 1;
        }
    }
    return 0;
}

char WhoIsTheWinner(int m, int n, char board[][n], int position){
    int x = (position - 1) / 3;
    int y = (position - 1) % 3;
    int result = ThreeInALine(x, y, m, n, board);
    if(result == 1){
        return board[x][y];
    }else{
        if(position > 9){
            return 'D';
        }else{
            return WhoIsTheWinner(m, n, board, position + 1);
        }
    }
}


int main(void){
    char board[3][3];
    char menu;
    char winner;
    while(1){
        printf("press 'p' to print the tic-tac-toe board\n");
        printf("press 'c' to create a tic-tac-toe board with some 'X' and 'O' cells\n");
        printf("press 't' to test if a tic-tac-toe board is a valid or invalid board\n");
        printf("press 'w' to predict winning cell for X or O\n");
        printf("press 'o' to determine the winner\n");
        printf("press 'e' to exit\n");
        scanf(" %c", &menu);
        if(menu == 'e'){
            break;
        }
        switch(menu){
            case 'p':
                PrintBoard(3, 3, board);
                break;
            case 'c':
                CreateBoard(3, 3, board);
                break;
            case 't':
                if(IsValidBoard(3, 3, board) == 1){
                    printf("The board is valid.\n");
                }else{
                    printf("The board is invalid.\n");
                }
                break;
            case 'w':
                ListWinningCells(3, 3, board);
                break;
            case 'o':
                winner = WhoIsTheWinner(3, 3, board, 1);
                if(winner == 'D'){
                    printf("There is no winner\n");
                }else{
                    printf("The winner is %c!!!\n", winner);
                }
                break;
            default:
                printf("Insert valid character.\n");
                break;   
        }

    }
    
}