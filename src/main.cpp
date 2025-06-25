#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "chessfild.h"
#include "chess_system.h"
using namespace std;



class Chessmove {

    class p_move {
        

    };
};



int main() {
    ChessBoard chess_game_board;
    chess_game_board.printBoard();

    
    return 0;
}












// // 스왚 테스트
// int board[3][3] = {
// {1, 2, 3},
// {4, 5, 6},
// {7, 8, 9}};

// cout << board[1][0] << "," << board[2][2] <<"\n";       
// std::swap(board[1][0], board[2][2]);
// cout << board[1][0] << "," << board[2][2] <<"\n";   

// // (0, 0) 위치의 string 객체 주소 출력
// for (int i = 0; i< 3; ++i) {
    // cout << "board[0][0] 주소: " << &board[i][0] << "\n";
    // }