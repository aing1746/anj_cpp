#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>


using namespace std;


class ChessBoard {
private:
    vector<vector<string>> board;
    int num1, num2, num3, num4;
    int menu;
    vector<string> teamW;
    vector<string> teamB;

    public:
    ChessBoard() {
        // 8x8 보드 생성 및 초기화
        board = vector<vector<string>>(10, vector<string>(10, " "));

        /*
        R N B Q K B N R | 1 
        P P P P P P P P | 2 
        . . . . . . . . | 3     
        . . . . . . . . | 4 
        . . . . . . . . | 5 
        . . . . . . . . | 6 
        p p p p p p p p | 7 
        r n b k q b n r | 8 
        - - - - - - - - | - 
        1 2 3 4 5 6 7 8 |  
        */

       // 체크무늬 패턴
       for (int i = 0; i < 10; ++i) {
           for (int j = 0; j < 10; ++j) {
               if ((i + j) % 2 == 0)
               board[i][j] = "."; // 검은색
               else
               board[i][j] = "."; // 흰색
            }
        }
        //가로, 세로 숫자 구현
        board[9] = {"1", "2", "3", "4", "5", "6", "7", "8","", ""};
        for (int i = 1; i < 9; ++i) {
            board[i - 1][9] = std::to_string(i);}

            // _선 표시
            for (int i = 0; i < 10; ++i) board[8][i] = "-";

            // |선 표시
            for (int i = 0; i < 10; ++i) board[i][8] = "|";

            // 백 기물 배치
            board[0] = {"R", "N", "B", "Q", "K", "B", "N", "R"};
            for (int i = 0; i < 8; ++i) board[1][i] = "P";


            // 흑 기물 배치
            board[7] = {"r", "n", "b", "q", "k", "b", "n", "r"};
            for (int i = 0; i < 8; ++i) board[6][i] = "p";

            teamW = {"R", "N", "B", "Q", "K", "P"};
            teamB = {"r", "n", "b", "q", "k", "p"};

        }

        void printBoard() {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    cout << board[i][j] << " ";
                }
                cout << "\n";
            }    
        }

        void Move_mal() {

    while (true) {
        cout << "1. print board: \n2. choose space:\n ";
        cin >> menu;
        if (menu == 1) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    cout << board[i][j] << " ";
                }   
                cout << "\n";
            }
        } else if (menu == 2) {
            cout << "The space you want.\n";


            if (cin >> num2 >> num1 >> num4 >> num3) {

                // 말끼리 서로 바뀌지 않게하기 
                if (board[num3-1][num4-1] != ".") {}

                // P의 자리 이동
                if (board[num1] == board[2] && "P") {              //P인지 아닌지 구별하기 "R","N","B","Q","K

                    if (2 < num3 && num3 < 5) {      // 이동 거리 제한
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]); 
                    } else {
                        if (num3 - num1 == 1) {
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]); 
                        }
                    }
                     
                    } else {}
                        
                if (std::find(teamB.begin(), teamB.end(), board[num3-1][num4-1]) == teamB.end()) {            //상대 말 구별하기
                    std::swap(board[num1-1][num2-1], board[num3-1][num4-1]);
                    if (board[num1-1][num2-1] == ".") {
                        board.at(num1-1).at(num2-1) = '.';
                    }
                } else {}
                
                } else {} 


                // R의 자리 이동                
                if (board[num1-1][num2-1] == "R") {
                    if (num1 == num3 || num2 == num4) {
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]); 
                    } else {}

                } else {}


                // //N의 자리 이동 [-2, -1, 1, 2] =! [-2, -1, 1, 2]
                // if (board[num1-1][num2-1] == "N") {
                //     if () {
                //     } else {
                //         std::swap(board[num1-1][num2-1], board[num3-1][num4-1]); 
                //     }
                // } else {}

                //B의 자리 이동
                if (board[num1-1][num2-1] == "B") {
                    if (num1 - num3 == num2 - num4 || num3 - num1 == num4 - num2) {
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]); 
                    } else {}
                }

                //Q의 자리 이동
                if (board[num1-1][num2-1] == "Q") {
                    if ((num1 == num3 || num2 == num4) || (num1 - num3 == num2 - num4 || num3 - num1 == num4 - num2)) {
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]);
                    }
                }

                //K의 자리 이동
                if (board[num1-1][num2-1] == "K") {
                    if (num3 && num4 < 2) {
                        std::swap(board[num1-1][num2-1], board[num3-1][num4-1]);
                    } else {}
                }

                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 10; ++j) {
                        cout << board[i][j] << " ";
                    }
                    cout << "\n";
                }
            } else {
                cout << "string! try again." << endl;

                // cin의 쓰래기값을 지움
                cin.clear();
                cin.ignore(numeric_limits<long long>::max(), '\n');
            }


        }
    }


};


int main() {
    ChessBoard chess_game_board;
    chess_game_board.printBoard();
    chess_game_board.Move_mal();

    return 0;
}