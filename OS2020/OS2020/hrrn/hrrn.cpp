#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream inp("hrrn.inp");
ofstream out("hrrn.out");

typedef struct {
    int number;
    int come;
    int use_time;
    double pri;
}Process;

//제일먼저 도착하고 사용시간이 제일 작고 프로세스 넘버가 제일 작은순으로 정렬(도착시간 제외 우선순위 정렬)
bool cmp(const Process& p1, const Process& p2) {
    if (p1.come < p2.come) return true;
    else if (p1.come == p2.come) {
        if (p1.number < p2.number) return true;
        else if (p1.number == p2.number) return p1.use_time < p2.use_time;
        else return false;
    }
    else return false;
}

//hrrn 우선순위 정렬
bool Priority(const Process& p1, const Process& p2) {
    if(p1.pri > p2.pri) return true;
    else if(p1.pri == p2.pri) {
        if(p1.come < p2.come) return true;
        else if(p1.come == p2.come) {
            if(p1.number < p2.number) return true;
            return false;
        }
        else return false;
    }
    else return false;
}

//벡터 요소 삭제 함수
void delete_vector(vector<Process>& p, int index) {
    int count = 0;
    for (vector<Process>::iterator it = p.begin(); it != p.end(); it++) {
        if (count == index) {
            it = p.erase(it);
            break;
        }
        else {
            count++;
        }
    }
}

//도착시간이 제일빠른 프로세스의 도착시간을 0으로 설정, 나머지 프로세스의 도착시간을 그만큼 감소
int start(vector<Process>& p, int num) {
    sort(p.begin(), p.end(), cmp);
    if (p[0].come != 0) {
        int temp = p[0].come;
        for (int i = 0; i < p.size(); i++) {
            p[i].come -= temp;
        }
    }
    return p[0].use_time;
}

void cal_hrrn(vector<Process>& p, int working_time){
    for(int i=0;i<p.size();i++) {
        if(p[i].come <= working_time) {
            p[i].pri = (double)(working_time - p[i].come + p[i].use_time)/p[i].use_time;
        }
        else break;
    }
}

//watiting time 시간 계산
int hrrn(vector<Process>& p, int num) {
    int waiting_time = 0;
    int working_time = 0;

    for (int i = 0; i < num; i++) {
        if (i == 0) {
            working_time += start(p, num);
            delete_vector(p, 0);
        }
        else {
            cal_hrrn(p,working_time);
            sort(p.begin(),p.end(),Priority);
            if(p[0].come > working_time) {
                sort(p.begin(),p.end(),cmp);
                working_time = p[0].come+p[0].use_time;
                delete_vector(p, 0);
            }
            else {
                waiting_time += (working_time - p[0].come);
                working_time += p[0].use_time;
                delete_vector(p, 0);
            }
        }
    }
    return waiting_time;
}

int main(void) {
    int num;
    inp >> num;

    vector<Process> p;

    for (int i = 0; i < num; i++) {
        Process temp;
        inp >> temp.number >> temp.come >> temp.use_time;
        temp.pri = -1;
        p.push_back(temp);
    }

    out << hrrn(p, num) << endl;
}
