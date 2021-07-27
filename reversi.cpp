#include"reversi.h"


void place_(char x,int y, int isoccupied1,char board[18][35],int chessboard[8][8])
{
    chessboard[y-1][x-'a'] = isoccupied1;
    board[2 * y][4 * (x-'a'+1)-1] =( isoccupied1 > 1 ? 'X' : 'O');
}

void display(char board[18][35],int chessboard[8][8])
{
    char boardtemp[18][35];
    for(int i = 0;i<18;i++){
        for(int j = 0;j<35;j++){
            boardtemp[i][j] = board[i][j];
        }
    }
    mark_playable(boardtemp,chessboard);
    for(int i = 0;i<18;i++){
        for(int j = 0;j<35;j++){
            cout<<boardtemp[i][j];
        }
        cout<<endl;
    }
}
void mark_playable(char board[18][35],int chessboard[8][8]){
    for(int i = 0;i < 8; i++ ){
        for(int j = 0; j < 8; j++){
            if(OK(i,j,1,chessboard)){
                board[2*i+2][4*j+3] = '`';
            }
        }
    }
}
//algorithum
int judge_complete(int r,int c,int p,int chessboard[8][8],int valuegraph[8][8],int step, int whole_step){
    if(step == 0){
        return judge_score(r,c,p,chessboard,valuegraph,whole_step);
    }
    else {
        int nv_chessboard[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                nv_chessboard[i][j] = chessboard[i][j];
            }
        }
        int score_itself = judge_score(r, c, p, chessboard, valuegraph,whole_step);
        change_only_chessboard(r, c, p, nv_chessboard);
        int max_other = -10000;
        for (int i = 0; i < 8; i++) { //别人下棋得分最大值
            for (int j = 0; j < 8; j++) {
                if (OK(i, j, 3 - p, nv_chessboard)) {
                    int score = judge_complete(i, j, 3 - p, nv_chessboard, valuegraph, step - 1,whole_step+1);
                    if (score > max_other) {
                        max_other = score;
                    }
                }
            }
        }
        if (max_other == -10000) {//别人无棋可下或者比赛已经结束
            return 0;
        }
        int score_this_step = score_itself - max_other; //自己这步的价值
        return score_this_step;
    }
}
int judge_weijianzhi(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step,int whole_step){
    if(p == 1){ //自己的turn 用极大值搜索
        if(step == 0){
            return judge_score(r,c,1,chessboard,valuegraph,whole_step);
        }
        else{
            int nv_chessboard[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    nv_chessboard[i][j] = chessboard[i][j];
                }
            }
            change_only_chessboard(r, c, 1, nv_chessboard);
            int min_other = 10000; //因为别人会下对你最不利的子
            for (int i = 0; i < 8; i++) { //别人下棋使你得分最小值
                for (int j = 0; j < 8; j++) {
                    if (OK(i, j, 3 - p, nv_chessboard)) {
                        int score = judge_weijianzhi(i, j, 3 - p, nv_chessboard, valuegraph, step - 1,whole_step+1);
                        if (score < min_other) {
                            min_other = score;
                        }
                    }
                }
            }
            if (min_other == -10000) {//别人无棋可下或者比赛已经结束 必须要~~~ 可以加一个行动力判断修正！！！！！！！！！！！！
                return rand()%1+1 + 100000;
            }
            return min_other;
        }
    }
    else if(p == 2){
        if(step == 0){
            return -judge_score(r,c,2,chessboard,valuegraph,whole_step);
        }
        else{
            int nv_chessboard[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    nv_chessboard[i][j] = chessboard[i][j];
                }
            }
            change_only_chessboard(r, c, 2, nv_chessboard);
            int max_other = -10000; //因为别人会下对你最不利的子
            for (int i = 0; i < 8; i++) { //你下棋，让你的收益最大
                for (int j = 0; j < 8; j++) {
                    if (OK(i, j, 3 - p, nv_chessboard)) {
                        int score = judge_weijianzhi(i, j, 3 - p, nv_chessboard, valuegraph, step - 1,whole_step+1);
                        if (score> max_other) {
                            max_other = score;
                        }
                    }
                }
            }
            if (max_other == -10000) {//自己无棋可下或者比赛已经结束 必须要~~~ 可以加一个行动力判断修正！！！！！！！！！！！！
                return rand()%1+1 - 100000;
            }
            return max_other;
        }
    }
    exit(-1);
}
int judge_jianzhi(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step, int max, int min,int whole_step){
    if(p == 1){ //自己的turn 用极大值搜索
        if(step == 0){
            return judge_score(r,c,1,chessboard,valuegraph,whole_step);
        }
        else{
            int nv_chessboard[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    nv_chessboard[i][j] = chessboard[i][j];
                }
            }
            change_only_chessboard(r, c, 1, nv_chessboard);
            for (int i = 0; i < 8; i++) { //别人下棋使你得分最小值
                for (int j = 0; j < 8; j++) {
                    if (OK(i, j, 3 - p, nv_chessboard)) {
                        int score = judge_jianzhi(i, j, 3 - p, nv_chessboard, valuegraph, step - 1,max,min,whole_step+1);
                        if (score < min) {
                            min = score;
                            if(min <= max){ //剪枝！！！！！
                                return max;
                            }
                        }
                    }
                }
            }
            return min;
        }
    }
    else if(p == 2){
        if(step == 0){
            return -judge_score(r,c,2,chessboard,valuegraph,whole_step);
        }
        else{
            int nv_chessboard[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    nv_chessboard[i][j] = chessboard[i][j];
                }
            }
            change_only_chessboard(r, c, 2, nv_chessboard);
            for (int i = 0; i < 8; i++) { //你下棋，让你的收益最大
                for (int j = 0; j < 8; j++) {
                    if (OK(i, j, 3 - p, nv_chessboard)) {
                        int score = judge_complete(i, j, 3 - p, nv_chessboard, valuegraph, step - 1,whole_step+1);
                        if (score > max) {
                            max = score;
                            if(max >= min){
                                return min;
                            }
                        }
                    }
                }
            }
            return max;
        }
    }
exit(-1);
}

int judge_heihei(int r,int c,int p, int chessboard[8][8], int valuegraph[8][8], int step,int whole_step) {
    int nv_chessboard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            nv_chessboard[i][j] = chessboard[i][j];
        }
    }
    change_only_chessboard(r, c, 1, nv_chessboard);
    int max = 0;
    for (int i = 0; i < 8; i++) { //你下棋，让你的收益最大
        for (int j = 0; j < 8; j++) {
            if (OK(i, j, 3 - p, nv_chessboard)) {
                int score = judge_avaliable(nv_chessboard, 2);
                if (score > max) {
                    max = score;
                }
            }
        }
    }
    return max;
}



int judge_score(int r, int c,int p, int v_chessboard[8][8],int valuegraph[8][8],int whole_step){ //当前步对当前玩家的分数变化
    int total = 0;
    int nv_chessboard[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j< 8; j++){
            nv_chessboard[i][j] = v_chessboard[i][j];
        }
    }

    int point_before = count_point_wholeboard(nv_chessboard,valuegraph,p);
    int avaliable_before = judge_avaliable(nv_chessboard,p);
    change_only_chessboard(r,c,p,nv_chessboard);
    //子的估值分变化
    int point_change = count_point_wholeboard(nv_chessboard,valuegraph,p) - point_before;
    //行动力分变化
    int avaliable_change = judge_avaliable(nv_chessboard,p) - avaliable_before;

    total = point_change + 3*avaliable_change*whole_step;
    return total;

}
int count_point_wholeboard(int v_chessboard[8][8],int valuegraph[8][8], int p){
    int total = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j< 8; j++){
            if(v_chessboard[i][j] == p){
                total+=valuegraph[i][j];
            }
        }
    }
    return total;
}

int judge_avaliable(int v_chessboard[8][8], int p){
    int count = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j< 8; j++){
            if(OK(i,j,p,v_chessboard))
                count++;
        }
    }
    return count;
}

void change_valuegraph(int valuegraph[8][8],int v_chessboard[8][8]){}


bool playOK(int r, int c, int dr, int dc, int p, int chessboard[8][8])
{
    int tr = r, tc = c;
    while (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && chessboard[tr + dr][tc + dc] == 3 - p)
    {
        tr += dr, tc += dc;
    }
    if (tr == r && tc == c)return false;
    if (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && chessboard[tr + dr][tc + dc] == p)
        return true;

    return false;
}

bool OK(int r, int c,int p,int chessboard[8][8])
{
    if (chessboard[r][c]!=0)return false;
    for (int i = 0; i < 8; i++) {
        if (playOK(r, c, dr[i], dc[i], p, chessboard))
            return true;
    }
    return false;
}
void change(int r,int c, int p,char board[18][35],int chessboard[8][8]){
    place_(c+'a',r+1,p,board,chessboard);
    for (int i = 0; i < 8; i++) {
        int tr = r, tc = c, count = 0;
        while (tr + dr[i] >= 0 && tr + dr[i] < 8 && tc + dc[i] >= 0 && tc + dc[i] < 8 && chessboard[tr + dr[i]][tc + dc[i]] == 3 - p)
        {
            tr += dr[i], tc += dc[i], count++;
        }
        if (tr == r && tc == c) continue;//in case it is at the bound.
        //tr += dr[i], tc += dc[i], count++;
        if (tr + dr[i] >= 0 && tr + dr[i] < 8 && tc + dc[i] >= 0 && tc + dc[i] < 8 && chessboard[tr + dr[i]][tc + dc[i]] == p){
            place_(tc+'a',tr+1,p,board,chessboard);
            for(int k = 0; k < count-1; k++){
                place_(tc - dc[i] + 'a',tr - dr[i] + 1,p,board,chessboard);
                tc -= dc[i];
                tr -= dr[i];
                //chessboard[tr - dr[i]][tc - dc[i]] = p;
            }
        }
    }
}

void change_only_chessboard(int r,int c,int p,int chessboard[8][8]){
    chessboard[r][c] = p;
    for (int i = 0; i < 8; i++) {
        int tr = r, tc = c, count = 0;
        while (tr + dr[i] >= 0 && tr + dr[i] < 8 && tc + dc[i] >= 0 && tc + dc[i] < 8 && chessboard[tr + dr[i]][tc + dc[i]] == 3 - p)
        {
            tr += dr[i], tc += dc[i], count++;
        }
        if (tr == r && tc == c) continue;//in case it is at the bound.
        //tr += dr[i], tc += dc[i], count++;
        if (tr + dr[i] >= 0 && tr + dr[i] < 8 && tc + dc[i] >= 0 && tc + dc[i] < 8 && chessboard[tr + dr[i]][tc + dc[i]] == p){
            chessboard[tr][tc] = p;
            for(int k = 0; k < count-1; k++){
                chessboard[tr-dr[i]][tc-dc[i]] = p;
            }
        }
    }
}




