#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

ifstream inp("bitmap.inp");
ofstream out("bitmap.out");

/*
 form_B 재귀함수 이용 행렬의 크기가 2 or 4일때 출력 => 시간초과 걱정...?
 form_D 반복문으로 해결될듯
 */

void form_B(int V, int H){
    out << "D " << V << " " << H << endl;
    
    vector<vector<int> > bitmap_all;
    bitmap_all.resize(V);
    int sum = 0;
    for(int i=0;i<V;i++) {
        for(int j=0;j<H;j++) {
            char temp;
            inp >> temp;
            sum += temp-'0';
            bitmap_all[i].push_back(temp-'0');
        }
    }
    if(sum == 0) {
        out << '0' << endl;
    }
    else if(sum == V*H) {
        out << '1' << endl;
    }
    else {
        out << 'D';
        
        int i_max,j_max;
        int size[4];
        if(V % 2 == 1 && H % 2 == 1) {
            size[0] = (H/2+1) * (V/2+1); size[1] = (H/2) * (V/2+1);
            size[2] = (H/2+1) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2+1;
            j_max = H/2;
        }
        else if(V % 2 == 1) {
            size[0] = (H/2) * (V/2+1); size[1] = (H/2) * (V/2+1);
            size[2] = (H/2) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2+1;
            j_max = H/2;
        }
        else if(H % 2 == 1) {
            size[0] = (H/2+1) * (V/2); size[1] = (H/2) * (V/2);
            size[2] = (H/2+1) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2;
            j_max = H/2+1;
        }
        else {
            size[0] = V*H/4; size[1] = V*H/4;
            size[2] = V*H/4; size[3] = V*H/4;
            
            i_max = V/2;
            j_max = H/2;
        }
        
        vector<int> v[4];
        int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
        
        for(int i=0;i<V;i++) {
            for(int j=0;j<H;j++) {
                if(i >= i_max && j >= j_max) {
                    v[3].push_back(bitmap_all[i][j]);
                    sum4 += bitmap_all[i][j];
                }
                else if(i >= i_max) {
                    v[2].push_back(bitmap_all[i][j]);
                    sum3 += bitmap_all[i][j];
                }
                else if(j >= j_max) {
                    v[1].push_back(bitmap_all[i][j]);
                    sum2 += bitmap_all[i][j];
                }
                else {
                    v[0].push_back(bitmap_all[i][j]);
                    sum1 += bitmap_all[i][j];
                }
            }
        }
        
        if(size[0] == sum1 || sum1 == 0) { out << v[0][0]; }
        else {
            out << 'D';
            for(int i=0;i<size[0];i++) { out << v[0][i]; }
        }
        
        if(size[1] == sum2 || sum2 == 0) { out << v[1][0]; }
        else {
            out << 'D';
            for(int i=0;i<size[1];i++) { out << v[1][i]; }
        }
        
        if(size[2] == sum3 || sum3 == 0) { out << v[2][0]; }
        else {
            out << 'D';
            for(int i=0;i<size[2];i++) { out << v[2][i]; }
        }
        
        if(size[3] == sum4 || sum4 == 0) { out << v[3][0]; }
        else {
            out << 'D';
            for(int i=0;i<size[3];i++) { out << v[3][i]; }
        }
        out << endl;
    }
}

void form_D(int V, int H) {
    out << "B " << V << " " << H << endl;
    string st;
    inp >> st;
    if(st[0] == '1' || st[0] == '0') {
        for(int i=0;i<V*H;i++) {
            out << st[0];
        }
        out << endl;
    }
    else {
        int i_max,j_max;
        int size[4];
        if(V % 2 == 1 && H % 2 == 1) {
            size[0] = (H/2+1) * (V/2+1); size[1] = (H/2) * (V/2+1);
            size[2] = (H/2+1) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2+1;
            j_max = H/2;
        }
        else if(V % 2 == 1) {
            size[0] = (H/2) * (V/2+1); size[1] = (H/2) * (V/2+1);
            size[2] = (H/2) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2+1;
            j_max = H/2;
        }
        else if(H % 2 == 1) {
            size[0] = (H/2+1) * (V/2); size[1] = (H/2) * (V/2);
            size[2] = (H/2+1) * (V/2); size[3] = (H/2) * (V/2);
            
            i_max = V/2;
            j_max = H/2+1;
        }
        else {
            size[0] = V*H/4; size[1] = V*H/4;
            size[2] = V*H/4; size[3] = V*H/4;
            
            i_max = V/2;
            j_max = H/2;
        }
        
        vector<int> v[4];
        
        int index = 1;
        for(int i=0;i<4;i++) {
            if(st[index] == 'D') {
                index++;
                for(int j=0;j<size[i];j++) {
                    v[i].push_back(st[index]-'0');
                    index++;
                }
            }
            else {
                for(int j=0;j<size[i];j++) {
                    v[i].push_back(st[index]-'0');
                }
                index++;
            }
        }
        
        int out_index[4];
        for(int i=0;i<4;i++) { out_index[i] = 0; }
        
        for(int i=0;i<V;i++) {
            for(int j=0;j<H;j++) {
                if(i >= i_max && j >= j_max) {
                    out << v[3][out_index[3]];
                    out_index[3]++;
                }
                else if(i >= i_max) {
                    out << v[2][out_index[2]];
                    out_index[2]++;
                }
                else if(j >= j_max) {
                    out << v[1][out_index[1]];
                    out_index[1]++;
                }
                else {
                    out << v[0][out_index[0]];
                    out_index[0]++;
                }
            }
        }
        out << endl;
    }
}

int main(void){
    char form;
    int H,V;
    
    do {
        inp >> form;
        if(form == '#') break;
        if(form == 'B') {
            inp >> V >> H;
            form_B(V,H);
        }
        else {
            inp >> V >> H;
            form_D(V,H);
        }
    }while(form != '#');
}
