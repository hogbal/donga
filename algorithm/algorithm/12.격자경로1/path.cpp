#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("path.inp");
ofstream out("path.out");

bool if_find(int sc,int dc,int test){
    if(test%10 < sc%10 || test%10 > dc%10) {    //sc보다 왼쪽 or dc 보다 오른쪽
        return false;
    }
    else {
        if(sc < dc) {
            if(test/10 < sc/10 || test/10 > dc/10) {
                return false;
            }
            else return true;
        }
        else {
            if(test/10 < dc/10 || test/10 > sc/10) {
                return false;
            }
            else return true;
        }
    }
}


int path(int sc, int dc, int *no, int count) {
    if(sc%10 > dc%10) {
        int temp = dc;
        dc = sc;
        sc = temp;
    }
    //sc가 무조건 왼쪽에 가게 배치
    
    int horizontal = dc%10 - sc%10;
    int vertical = sc/10 - dc/10;
    
    if(horizontal < 0) horizontal = 0 - horizontal;
    if(vertical < 0) vertical = 0 - vertical;
    
    horizontal++;
    vertical++;
    //가로 세로 계산
    
    int **mat = new int*[vertical]();
    for(int i=0;i<vertical;i++) {
        mat[i] = new int[horizontal]();
    }
    //동적할당완료
    
    for(int i=0;i<vertical;i++) {
        for(int j=0;j<horizontal;j++) {
            mat[i][j]=0;
        }
    }
    //초기값 세팅
    
    if(sc < dc) {   //sc가 왼쪽 위일때
        for(int i=0;i<horizontal;i++) {
            mat[0][i] = 1;
        }
        for(int i=0;i<vertical;i++) {
            mat[i][0] = 1;
        }
        
        for(int i=0;i<count;i++) {
            if(if_find(sc, dc, no[i])) {
                mat[no[i]/10-sc/10][no[i]%10-sc%10] = -1;
            }
        }
        //막힌곳 -1할당
        
        //계산시작
        for(int j=1;j<horizontal;j++) {
            for(int i=1;i<vertical;i++) {
                if(mat[i][j] == -1) continue;
                if(mat[i-1][j]==-1 && mat[i][j-1]==-1) {
                    mat[i][j] = -1;
                }
                else if(mat[i-1][j]==-1){
                    mat[i][j] = mat[i][j-1];
                }
                else if(mat[i][j-1]==-1) {
                    mat[i][j] = mat[i-1][j];
                }
                else {
                    mat[i][j] = mat[i-1][j] + mat[i][j-1];
                }
            }
        }
    }
    else {  //sc가 왼쪽 아래일때
        for(int i=0;i<count;i++) {
            if(if_find(sc, dc, no[i])) {
                mat[(vertical-1)-(sc/10-no[i]/10)][no[i]%10-sc%10] = -1;
            }
        }
        mat[vertical-1][0] = 1;
        for(int i=1;i<horizontal;i++) {
            if(mat[vertical-1][i-1]==-1 || mat[vertical-1][i]==-1){
                mat[vertical-1][i] = -1;
            }
            else {
                mat[vertical-1][i] = 1;
            }
        }
        for(int i=vertical-2;i>=0;i--) {
            if(mat[i+1][0]==-1 || mat[i][0]==-1) {
                mat[i][0] = -1;
            }
            else {
                mat[i][0] = 1;
            }
        }
        //막힌곳 -1할당

        //계산시작
        for(int j=1;j<horizontal;j++) {
            for(int i=vertical-2;i>=0;i--) {
                if(mat[i][j] == -1) continue;
                if(mat[i+1][j]==-1 && mat[i][j-1]==-1) {
                    mat[i][j] = -1;
                }
                else if(mat[i+1][j]==-1){
                    mat[i][j] = mat[i][j-1];
                }
                else if(mat[i][j-1]==-1) {
                    mat[i][j] = mat[i+1][j];
                }
                else {
                    mat[i][j] = mat[i+1][j] + mat[i][j-1];
                }
            }
        }
    }
    
    if(sc < dc) {
        if(mat[vertical-1][horizontal-1] == -1) return 0;
        else return mat[vertical-1][horizontal-1];
    }
    else {
        if(mat[0][horizontal-1] == -1) return 0;
        else return mat[0][horizontal-1];
    }
}

int main(void) {
    int sc, dc, count;
    inp >> sc >> dc >> count;
    
    int *no = new int[count]();
    
    for(int i=0;i<count;i++) {
        inp >> no[i];
    }
    out << path(sc,dc,no,count);
}
