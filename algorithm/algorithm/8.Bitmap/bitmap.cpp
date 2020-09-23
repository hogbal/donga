#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("bitmap.inp");
ofstream out("bitmap.out");

int output_count;

void output_check(){
    output_count++;
    if(output_count == 50) {
        out << endl;
        output_count = 0;
    }
}

void form_input_B(int *mat, int V, int H, int *sum){
    for(int i=0;i<V*H;i++) {
        char temp;
        temp = inp.get();
        if(temp == ' ') break;
        else if(temp == '\n') {
            i--;
            continue;
        }
        else {
            mat[i] = temp-'0';
            *sum += mat[i];
        }
    }
}

void form_B(int *mat, int sum, int V, int H){
    if(sum == V*H || sum == 0) {   //전체를 보고 1인지 0인지 확인
        out << mat[0];
        output_check();
    }
    else if(V == 1 || H == 1) {
        out << 'D';
        output_check();
        for(int i=0;i<V*H;i++) {
            out << mat[i];
            output_check();
        }
    }
    else {
        out << 'D';
        output_check();
        
        int *mat_div[4];
        int V_temp[4], H_temp[4];
                    
        for(int i=0;i<4;i++) {
            V_temp[i] = V/2;
            H_temp[i] = H/2;
        }
        
        if(V%2==1 && H%2==1) {
            V_temp[0] += 1; H_temp[0] += 1;
            V_temp[1] += 1;
            H_temp[2] += 1;
        }
        else if(V%2==1) {
            V_temp[0] += 1;
            V_temp[1] += 1;
        }
        else if(H%2==1) {
            H_temp[0] += 1;
            H_temp[2] += 1;
        }
        
        for(int i=0;i<4;i++) {
            mat_div[i] = new int[V_temp[i]*H_temp[i]];
        }
        int index1 = 0, index2 = 0, index3 = 0, index4 = 0;
        int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
        
        for(int i=0;i<V;i++) {
            for(int j=0;j<H;j++) {
                if(i<((V/2) + (V%2))) { //1,2사분면
                    if(j<((H/2) + (H%2))) { //1사분면
                        mat_div[0][index1] = mat[i*H+j];
                        sum1 += mat[i*H+j];
                        index1++;
                    }
                    else {  //2사분면
                        mat_div[1][index2] = mat[i*H+j];
                        sum2 += mat[i*H+j];
                        index2++;
                    }
                }
                else {  //3,4사분면
                    if(j<((H/2) + (H%2))) { //3사분면
                        mat_div[2][index3] = mat[i*H+j];
                        sum3 += mat[i*H+j];
                        index3++;
                    }
                    else {  //4사분면
                        mat_div[3][index4] = mat[i*H+j];
                        sum4 += mat[i*H+j];
                        index4++;
                    }
                }
            }
        }
        
        form_B(mat_div[0],sum1,V_temp[0],H_temp[0]);
        form_B(mat_div[1],sum2,V_temp[1],H_temp[1]);
        form_B(mat_div[2],sum3,V_temp[2],H_temp[2]);
        form_B(mat_div[3],sum4,V_temp[3],H_temp[3]);
    }
}

void form_D(){
    
}

int main(void) {
    int V,H;
    char form;
    string st;
    
    inp >> form;
    
    while(1){
        if(form == '#') break;
        else if(form == 'B') {
            output_count = 0;
            
            inp >> V >> H;
            int *mat = new int[V*H];
            int sum = 0;
            form_input_B(mat,V,H,&sum);
            
            out << 'D' << ' ' << V << ' ' << H << endl;
            form_B(mat,sum,V,H);
            inp >> form;
        }
        else {
            inp >> V >> H;
            //st = form_input(&form);
            
            break;
            form_D();
        }
        out << endl;
    }
}
