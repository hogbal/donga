#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("fibonacci.inp");
ofstream out("fibonacci.out");

long long M;

vector<vector<long long> > squared (vector<vector<long long> > &mat1, vector<vector<long long> > &mat2) {
    long long n = mat1.size();
    vector<vector<long long> > result(n, vector<long long>(n));
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= M;
        }
    }
    return result;
}

long long fibonacci(long long n, long long M){
    vector<vector<long long> > ans = {{1, 0}, {0, 1}};
    vector<vector<long long> > mat = {{1, 1}, {1, 0}};

    while (n > 0) {
        if (n % 2 == 1) {
            ans = squared(ans, mat);
        }
        mat = squared(mat, mat);
        n /= 2;
    }
    
    return ans[0][1];
}

long long mod_fun(){
    long long a,b,c,d;
    inp >> a >> b >> c >> d >> M;
    a = fibonacci(a, M);
    b = fibonacci(b, M);
    c = fibonacci(c, M);
    d = fibonacci(d, M);
    
    return (((((a%M)*(b%M))%M)%M) + ((((c%M)*(d%M))%M)%M)) % M;
}

int main(void){
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        out << mod_fun() << endl;
    }
}
