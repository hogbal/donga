#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("primefactor.inp");
ofstream out("primefactor.out");

int prime(){
    int num;
    int sum = 0;
    int start = 2;
    inp >> num;
    
    while(num != 1) {
        if(num % start == 0) {
            if(sum == 0 && start == num) {
                return -1;
            }
            num /= start;
            sum += start;
        }
        else {
            start++;
        }
    }
    return sum;
}

int main(void) {
    int count;
    inp >> count;
    for(int i=0;i<count;i++) {
        int result = prime();
        if(result == -1) {
            out << "Prime Number" << endl;
        }
        else {
            out << result << endl;
        }
    }
}
