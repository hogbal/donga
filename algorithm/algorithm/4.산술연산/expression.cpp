#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

ifstream inp("expression.inp");
ofstream out("expression.out");

struct oper{
    int prior; // 연산자 우선순위
    char oper; // 연산자
};

int calc(stack<int> &num, stack<oper> &op){
    int a, b, result;
    b = num.top();
    num.pop();
    a = num.top();
    num.pop();
    char oper = op.top().oper;
    op.pop();
    
    if (oper == '*') {
        result =  a * b;
    }
    else if(oper == '/') {
        if(b == 0) {
            out << "Error!" << endl;
            return -1;
        }
        result = a / b;
    }
    else if(oper == '%') {
        if(b == 0) {
            out << "Error!" << endl;
            return -1;
        }
        result = a % b;
    }
    else if(oper == '+') {
        result = a + b;
    }
    else {
        result = a - b;
    }
    num.push(result);
    return 1;
}


void expression(){
    string str;
    stack<int> num;
    stack<oper> op;
    int num_cal;
    char oper;
    
    bool check = true;
    
    while (1) {
        if(check) {
            inp >> num_cal;
            num.push(num_cal);
            check = false;
        }
        else {
            inp >> oper;
            if(oper == '=') break;
            int prior; // 연산자 우선순위
            if(oper == '*') {
                prior = 2;
            }
            else if(oper == '/') {
                prior = 2;
            }
            else if(oper == '%') {
                prior = 2;
            }
            else if(oper == '+') {
                prior = 1;
            }
            else {
                prior = 1;
            }
            while (!op.empty() && prior <= op.top().prior) {
                int ch = calc(num, op);
                if(ch == -1) {
                    if(oper != '=') {
                        while(1) {
                            char ch;
                            inp >> ch;
                            if(ch == '=') break;
                        }
                    }
                    return;
                }
            }
            op.push({prior,oper});
            check = true;
        }
    }
       // 남은 연산자 계산
    while (!op.empty()) {
        int ch = calc(num, op);
        if(ch == -1) {
            return;
        }
    }
    out << num.top() << endl;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        expression();
    }
}
