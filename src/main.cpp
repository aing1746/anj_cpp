#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>
using namespace std;

class ChessBoard {
private:
    array<array<string, 8>, 8> board;
    array<string, 10> teamW;
    array<string, 10> teamB;
    bool whiteTurn;
    bool whiteKingMoved, blackKingMoved;
    bool whiteRookMoved[2], blackRookMoved[2];
    bool lastMoveWasDoublePawn;
    int lastMovePawnRow, lastMovePawnCol;

public:
    ChessBoard() : whiteTurn(true),
                   whiteKingMoved(false), blackKingMoved(false),
                   lastMoveWasDoublePawn(false) {
        whiteRookMoved[0] = whiteRookMoved[1] = false;
        blackRookMoved[0] = blackRookMoved[1] = false;

        // 초기 보드 세팅
        string firstRowW[] = {"R","N","B","Q","K","B","N","R"};
        string firstRowB[] = {"r","n","b","q","k","b","n","r"};
        for (int i=0;i<8;i++) board[0][i] = firstRowW[i];
        for (int i=0;i<8;i++) board[1][i] = "P";
        for (int i=2;i<6;i++) for (int j=0;j<8;j++) board[i][j] = ".";
        for (int i=0;i<8;i++) board[6][i] = "p";
        for (int i=0;i<8;i++) board[7][i] = firstRowB[i];

        teamW = {"R","N","B","Q","K","P"};
        teamB = {"r","n","b","q","k","p"};
    }

    void printBoard() const {
        for (int r = 7; r >= 0; r--) {
            cout << r+1 << " ";
            for (int c = 0; c < 8; c++) {
                cout << board[r][c] << " ";
            }
            cout << "\n";
        }
        cout << "  1 2 3 4 5 6 7 8\n";
    }

    bool isSameTeam(string piece, string target) {
        if (target == ".") return false;
        return (isupper(piece[0]) && find(teamW.begin(), teamW.end(), target) != teamW.end()) ||
               (islower(piece[0]) && find(teamB.begin(), teamB.end(), target) != teamB.end());
    }

    bool isOpponent(string piece, string target) {
        if (target == ".") return false;
        return (isupper(piece[0]) && find(teamB.begin(), teamB.end(), target) != teamB.end()) ||
               (islower(piece[0]) && find(teamW.begin(), teamW.end(), target) != teamW.end());
    }

    bool isPathClear(int fr, int fc, int tr, int tc) {
        int dr = (tr > fr) ? 1 : (tr < fr) ? -1 : 0;
        int dc = (tc > fc) ? 1 : (tc < fc) ? -1 : 0;
        int r = fr + dr, c = fc + dc;
        while (r != tr || c != tc) {
            if (board[r][c] != ".") return false;
            r += dr; c += dc;
        }
        return true;
    }

    pair<int,int> findKing(bool white) {
        string king = white ? "K" : "k";
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (board[r][c] == king) return make_pair(r,c);
        return make_pair(-1,-1);
    }

    bool isSquareAttacked(int r, int c, bool byWhite) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                string p = board[i][j];
                if (p == ".") continue;
                if (byWhite && !isupper(p[0])) continue;
                if (!byWhite && isupper(p[0])) continue;
                int dr = abs(r-i), dc = abs(c-j);
                char pt = toupper(p[0]);
                if (pt == 'P') {
                    if (byWhite && dr == 1 && dc == 1 && r > i) return true;
                    if (!byWhite && dr == 1 && dc == 1 && r < i) return true;
                } else if (pt == 'R') {
                    if ((dr==0 || dc==0) && isPathClear(i,j,r,c)) return true;
                } else if (pt == 'B') {
                    if (dr == dc && isPathClear(i,j,r,c)) return true;
                } else if (pt == 'Q') {
                    if ((dr==0 || dc==0 || dr==dc) && isPathClear(i,j,r,c)) return true;
                } else if (pt == 'N') {
                    if ((dr==2 && dc==1) || (dr==1 && dc==2)) return true;
                } else if (pt == 'K') {
                    if (dr <= 1 && dc <= 1) return true;
                }
            }
        }
        return false;
    }

    bool inCheck(bool white) {
        pair<int,int> kingPos = findKing(white);
        int kr = kingPos.first;
        int kc = kingPos.second;
        return isSquareAttacked(kr,kc,!white);
    }

    bool canCastle(bool white, bool kingSide) {
        int row = white ? 0 : 7;
        if (inCheck(white)) return false;
        if (kingSide) {
            if ((white && whiteKingMoved) || (!white && blackKingMoved)) return false;
            if ((white && whiteRookMoved[1]) || (!white && blackRookMoved[1])) return false;
            if (!isPathClear(row,4,row,7)) return false;
            if (isSquareAttacked(row,5,!white) || isSquareAttacked(row,6,!white)) return false;
        } else {
            if ((white && whiteKingMoved) || (!white && blackKingMoved)) return false;
            if ((white && whiteRookMoved[0]) || (!white && blackRookMoved[0])) return false;
            if (!isPathClear(row,4,row,0)) return false;
            if (isSquareAttacked(row,3,!white) || isSquareAttacked(row,2,!white)) return false;
        }
        return true;
    }

    bool hasAnyLegalMove(bool white) {
        for (int fr = 0; fr < 8; fr++) {
            for (int fc = 0; fc < 8; fc++) {
                string p = board[fr][fc];
                if (p == ".") continue;
                if (white && !isupper(p[0])) continue;
                if (!white && isupper(p[0])) continue;
                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {
                        string saveFrom = board[fr][fc];
                        string saveTo = board[tr][tc];
                        if (!isSameTeam(p, board[tr][tc])) {
                            board[tr][tc] = p;
                            board[fr][fc] = ".";
                            bool safe = !inCheck(white);
                            board[fr][fc] = saveFrom;
                            board[tr][tc] = saveTo;
                            if (safe) return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    void makeMove(int fr,int fc,int tr,int tc) {
        board[tr][tc] = board[fr][fc];
        board[fr][fc] = ".";
    }

    bool isLegalMove(string piece, int fr, int fc, int tr, int tc) {
        int dr = tr-fr, dc = tc-fc;
        int adr = abs(dr), adc = abs(dc);

        if (toupper(piece[0]) == 'P') {
            bool whitePawn = isupper(piece[0]);
            int dir = whitePawn ? 1 : -1;
            int startRow = whitePawn ? 1 : 6;
            if (dc == 0 && board[tr][tc]==".") {
                if (dr==dir) return true;
                if (fr==startRow && dr==2*dir && board[fr+dir][fc]==".") return true;
            } else if (adc==1 && dr==dir && isOpponent(piece, board[tr][tc])) return true;
            else if (adc==1 && dr==dir && board[tr][tc]=="." && lastMoveWasDoublePawn &&
                     tr==lastMovePawnRow+dir && tc==lastMovePawnCol) return true;
        } else if (toupper(piece[0])=='R') return (dr==0||dc==0)&&isPathClear(fr,fc,tr,tc);
        else if (toupper(piece[0])=='B') return (adr==adc)&&isPathClear(fr,fc,tr,tc);
        else if (toupper(piece[0])=='Q') return (dr==0||dc==0||adr==adc)&&isPathClear(fr,fc,tr,tc);
        else if (toupper(piece[0])=='N') return (adr==2 && adc==1)||(adr==1 && adc==2);
        else if (toupper(piece[0])=='K') return adr<=1 && adc<=1;
        return false;
    }

    void Move_mal() {
        while(true) {
            printBoard();
            cout << (whiteTurn?"white":"black")<<" turn. (c1 r1 c2 r2): ";
            int c1,r1,c2,r2;
            if (!(cin>>c1>>r1>>c2>>r2)) { cout<<"Input error. Shutdown\n"; break; }
            int fr=r1-1, fc=c1-1, tr=r2-1, tc=c2-1;
            string piece = board[fr][fc];
            if (piece=="."||(whiteTurn&&!isupper(piece[0]))||(!whiteTurn&&isupper(piece[0]))) {
                cout<<"Invalid property selection\n"; continue;
            }

            // 캐슬링
            if (toupper(piece[0])=='K' && abs(fc-tc)==2) {
                bool kingSide = (tc>fc);
                if (canCastle(whiteTurn, kingSide)) {
                    int row = whiteTurn?0:7;
                    if (kingSide) { makeMove(row,4,row,6); makeMove(row,7,row,5);}
                    else { makeMove(row,4,row,2); makeMove(row,0,row,3);}
                    whiteTurn=!whiteTurn;
                    continue;
                } else { cout<<"Can't castling\n"; continue;}
            }

            if (!isLegalMove(piece,fr,fc,tr,tc)) { cout<<"Invalid movement\n"; continue;}

            // 앙파상
            if (toupper(piece[0])=='P' && tc!=fc && board[tr][tc]==".") board[lastMovePawnRow][lastMovePawnCol]=".";

            // 더블폰 기록
            lastMoveWasDoublePawn=(toupper(piece[0])=='P' && abs(tr-fr)==2);
            if (lastMoveWasDoublePawn) { lastMovePawnRow=tr; lastMovePawnCol=tc;}

            string savedFrom=board[fr][fc], savedTo=board[tr][tc];
            makeMove(fr,fc,tr,tc);
            if (inCheck(!whiteTurn)) { board[fr][fc]=savedFrom; board[tr][tc]=savedTo; continue;}

            whiteTurn=!whiteTurn;

            // 체크/체크메이트
            if (inCheck(whiteTurn)) {
                if (!hasAnyLegalMove(whiteTurn)) { cout<<(whiteTurn?"white":"black")<<" Checkmate! Game over\n"; break;}
                else cout<<(whiteTurn?"white":"black")<<" check!\n";
            } else if (!hasAnyLegalMove(whiteTurn)) { cout<<"Stalemate! It's a draw\n"; break;}
        }
    }
};

int main() {
    ChessBoard game;
    game.Move_mal();
}
