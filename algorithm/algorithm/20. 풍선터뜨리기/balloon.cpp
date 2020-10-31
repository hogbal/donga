#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

ifstream inp("balloon.inp");
ofstream out("balloon.out");

typedef struct {
    int st;
    int num;
}LCSArr;

typedef struct {
    int case_num;
    int num;
}LCSCase;

bool cmp(const LCSArr &a1, const LCSArr &a2) {
    if(a1.num < a2.num) return true;
    else if(a1.num == a2.num) {
        return a1.st > a2.st;
    }
    else return false;
}

void balloon(int n){
    LCSArr *a = new LCSArr[n];
    LCSArr *b = new LCSArr[n];
    pair<int,int> *save = new pair<int,int>[n];
    
    int ch = 50001;
    for(int i=0;i<n;i++) {
        inp >> a[i].num;
        a[i].st = ch;
        ch++;
        b[i] = a[i];
    }
    
    sort(b,b+n,cmp);
    
    int **lcs = new int*[n+1];
    for(int i=0;i<n+1;i++) {
        lcs[i] = new int[n+1];
    }
    
    int index = 0;
    for(int i=0;i<n+1;i++) {
        for(int j=0;j<n+1;j++) {
            if(i == 0 || j == 0) {
                lcs[i][j] = 0;
            }
            else {
                if(a[j-1].st == b[i-1].st) {
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                    
                    save[index++] = make_pair(j-1, lcs[i][j]);
                }
                else {
                    lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
                }
            }
        }
    }
    
    int len_max = lcs[n][n];
    int sum = 0;
    LCSCase *c = new LCSCase[n];
    
    for(int i=0;i<n;i++) {
        c[i].case_num=0;
        c[i].num=0;
    }
    
    for(int i=0;i<n;i++) {
        int save_index = save[i].first;
        int save_num = save[i].second;
        if(save_num == 1) {
            c[save_index].num = 1;
            c[save_index].case_num = 1;
        }
        else {
            int case_sum = 0;
            for(int j=0;j<save_index;j++) {
                if(save_num-1 == c[j].num) {
                    case_sum += c[j].case_num;
                }
            }
            c[save_index].case_num = case_sum;
            c[save_index].num = save_num;
        }
        if(c[save_index].num == len_max) {
            sum += c[save_index].case_num;
        }
    }
    
    out << len_max << " " << sum << endl;
}

int main(void) {
    int n;
    inp >> n;
    
    while(n != 0) {
        balloon(n);
        inp >> n;
    }
}
