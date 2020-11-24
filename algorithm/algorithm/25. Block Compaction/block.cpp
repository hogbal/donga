#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("block.inp");
ofstream out("block.out");

typedef struct {
    long long x;
    long long y;
    long long p;
    long long q;
}Block;

int N;

void block(){
    inp >> N;
    Block *b = new Block[N];
    
    for(int i=0;i<N;i++) {
        inp >> b[i].x >> b[i].y >> b[i].p >> b[i].q;
    }
}

int main(void) {
    int T;
    
    inp >> T;
    for(int i=0;i<T;i++) {
        block();
    }
}
