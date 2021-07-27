#ifndef REVERSI_NEW_REVERSI_H
#define REVERSI_NEW_REVERSI_H

#include <iostream>
#include <time.h>

using namespace std;

const int dr[8] = {0,0,1,1,1,-1,-1,-1}, dc[8] = {1,-1,0,1,-1,0,1,-1};

void place_(char x,int y, int isoccupied1,char board[18][35],int chessboard[8][8]);
void display(char board[18][35],int chessboard[8][8]);
void mark_playable(char board[18][35],int chessboard[8][8]);

//int **generate_chessboard(int r_chessboard[8][8]);
int judge_complete(int r,int c,int p,int chessboard[8][8],int valuegraph[8][8],int step, int whole_step);
int judge_weijianzhi(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step,int whole_step);
int judge_jianzhi(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step, int max, int min,int whole_step);

int judge_heihei(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step,int whole_step);

int judge_score(int r, int c,int p, int v_chessboard[8][8],int valuegraph[8][8],int whole_step);
int count_point_wholeboard(int v_chessboard[8][8],int valuegraph[8][8],int p);

int judge_avaliable(int v_chessboard[8][8],int p);

void change_valuegraph(int valuegraph[8][8],int v_chessboard[8][8]);

bool playOK(int x, int c, int dr, int dc,int p, int chessboard[8][8]);
bool OK(int r, int c,int p, int chessboard[8][8]);
void change(int r,int c, int p,char board[18][35],int chessboard[8][8]); // r, c start from 0;
void change_only_chessboard(int r,int c,int p,int chessboard[8][8]);

//void judge_change(int board[8][8]);

#endif //REVERSI_NEW_REVERSI_H
