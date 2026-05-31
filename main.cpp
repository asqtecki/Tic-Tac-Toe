#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

//declarations
const int size=3; //3x3
const int cell = 4; //size of each cell
const int W=size*cell + 1; 
void board(char init[][size]);
int game(char init[][size]);
int winner(char init[][size]);

//defs
void board(char init[][size]) {
    //Drawing Board
    char b[W][W];
    for (int i=0;i<W;i++) {
        for (int j=0;j<W;j++)
            b[i][j] = ' ';
    }
    for (int i=1;i<W-1;i++) {
        for (int j=1;j<W-1;j++) {
            if (i%cell==0 && j%cell==0) b[i][j] = '+';
            else if (i%cell==0) b[i][j] = '-';
            else if (j%cell==0) b[i][j] = '|';
        }
    }
    for (int i=0; i<size; i++) {
        for (int j=0;j<size;j++) {
            int x = i * cell + cell / 2;
            int y = j * cell + cell / 2;
            b[x][y] = init[i][j];
        }
    }
    for (int i=0;i<W;i++) {
        for (int j=0;j<W;j++)
            std::cout << b[i][j];
        std::cout << std::endl;
    }
}

int game(char init[][size]) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) 
            init[i][j] = ' ';
    }
    char inp = 'X';
    int pos, r, c, win=0, counter=0;
    bool cond = false;
    char ask, tar = 'X';;
    std::cout << "Press y to START: ";
    ask = _getche();
    if (ask=='y' || ask=='Y') {
        cond = true;
        std::cout << "\nLoading...";
        Sleep(1000);
        std::cout << "\nPlayer 1: X, Player 2: O\n";
    }
    else {
        std::cout << "\nExiting...";
        Sleep(1000);
        return -1;
    }
    while (cond) {
        for (int i=0;i<2;i++) {
            std::cout << "\nPlayer " << (tar=='X' ? 1 : 2) << ", Enter 1-9 to input: ";
            std::cin >> pos;
            r = (pos-1) / 3;
            c = (pos-1) % 3; 
            if (pos<1 || pos>9 || init[r][c]!=' ')  {
                std::cout << "Invalid Input!, Press Enter to Input again.";
                std::cin.get();
                std::cin.ignore();
                continue;
            }
            init[r][c] = tar;
            counter++;
            tar = (tar=='X') ? 'O' : 'X';
            Sleep(500);
            system("cls");
            board(init);
            win = winner(init);
            if (win != 0) {
                cond = false;
                break;
            }
            if (counter==9 && win==0) {
                cond = false;
                break;
            }
        }
    }
    return win;
}

int winner(char init[][size]) {
    int c=0;
    for (int i=0;i<size;i++) {
        if (init[i][0]!=' ' && init[i][0]==init[i][1] && init[i][1]==init[i][2]) return (init[i][0]=='X') ? 1 : 2;
    }
    for (int j=0;j<size;j++) {
        if (init[0][j]!=' ' && init[0][j]==init[1][j] && init[1][j]==init[2][j]) return (init[0][j]=='X') ? 1 : 2;
    }
    if (init[0][0]!=' ' && init[0][0]==init[1][1] && init[1][1]==init[2][2]) return (init[0][0]=='X') ? 1 : 2;
    if (init[0][2]!=' ' && init[0][2]==init[1][1] && init[1][1]==init[2][0]) return (init[0][2]=='X') ? 1 : 2;
    return 0;
}

int main() {
    std::cout << "\t\t\t\tWelcome to Tic Tac Toe!\n";
    char init[size][size] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };
    board(init);
    int win = game(init);
    if (win == 1) std::cout << "\nPlayer 1 (X) Wins!";
    else if (win == 2) std::cout << "\nPlayer 2 (O) Wins!";
    else if (win==0) std::cout << "\nGame Drawn!";
}
