#pragma once

#include <vector>

using namespace std;


class ChessBoard {
private:
    vector<vector<string>> board; 
	
 	char num1;
    char num2;
    char num3;
    char num4;
public:
    ChessBoard() {
        // 8x8 보드 생성 및 초기화
        board = vector<vector<string>>(10, vector<string>(10, " "));

        // 체크무늬 패턴
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 10; ++j) {
                if ((i + j) % 2 == 0)
                    board[i][j] = "."; // 검은색
                else
                    board[i][j] = ","; // 흰색
            }
        }
        //가로, 세로 숫자 구현
        board[0] = {"1", "2", "3", "4", "5", "6", "7", "8","", ""};
        for (int i = 1; i < 9; ++i) {
            board[i+1][9] = std::to_string(i);}

        // _선 표시
        for (int i = 0; i < 10; ++i) board[1][i] = "_";
        
        // |선 표시
        for (int i = 1; i < 10; ++i) board[i][8] = "|";

        // 백 기물 배치
        board[2] = {"R", "N", "B", "Q", "K", "B", "N", "R"};
        for (int i = 0; i < 8; ++i) board[3][i] = "P";


        // 흑 기물 배치
        board[9] = {"r", "n", "b", "k", "q", "b", "n", "r"};
        for (int i = 0; i < 8; ++i) board[8][i] = "p";
        
        
        
    }
    
    void printBoard() {    
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        
		//값 받기
		std::cin >> num1;
        std::cin >> num2;
        std::cin >> num3;
        std::cin >> num4;
        
        std::swap(board[num1][num2], board[num3][num4]);
        cout << board[3][0] << "," << board[5][0] <<"\n";   
    }
    void input() {
    }

};
