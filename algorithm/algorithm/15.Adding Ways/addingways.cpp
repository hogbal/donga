#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("addingways.inp");
ofstream out("addingways.out");

int case_addingways;
int *arr_case;
int n,k;

void addingways(int index){
    if(index <= k-1) {
        case_addingways++;
        int give = 0;
        int take = 1;
        
        while(1){
            
        }
        
        int sum = 0;
        index++;
        
        for(int i=k-1;i>=0;i--) {
            if(i == 0) {
                arr_case[i] = n - sum;
            }
            else if(i <= index) {
                arr_case[i] = 2;
            }
            else {
                arr_case[i] = 1;
            }
            sum += arr_case[i];
        }
        
        if(arr_case[0] >= arr_case[1]) {
            addingways(index);
        }
    }
}

int main(void) {
    while(1) {
        inp >> n >> k;
        if(n == 0 && k == 0) {
            break;
        }
        else if(n < k) {
            out << "0" << endl;
        }
        else if(k == 1) {
            out << "1" << endl;
        }
        else {
            case_addingways = 0;
            arr_case = new int[k];
            
            for(int i=k-1;i>=0;i--) {
                if(i == 0) {
                    arr_case[i] = n - (k-1);
                }
                else {
                    arr_case[i] = 1;
                }
            }
            
            addingways(1);
            
            out << case_addingways << endl;
            
            delete[] arr_case;
        }
    }
}
