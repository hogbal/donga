#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

ifstream inp("rr.inp");
ofstream out("rr.out");
typedef struct {
    int num;
    int come;
    vector<int> burst;
    int start;
    bool qu;
    bool end;
    int wait_time;
}Process;

typedef struct{
    int num;
    int wait_time;
}Answer;

bool cmp_num(const Process &p1, const Process &p2) {
    if(p1.num < p2.num) return true;
    else return false;
}

bool cmp_come_pro(const Process &p1, const Process &p2) {
    if(p1.come < p2.come) return true;
    else if(p1.come == p2.come) {
        if(p1.start < p2.start) return true;
        else if(p1.start == p2.start) {
            return p1.num < p2.num;
        }
        else return false;
    }
    else {
        return false;
    }
}

bool cmp_ans_num(const Answer &p1, const Answer &p2) {
    if(p1.num < p2.num) return true;
    else return false;
}

void delete_vector(vector<Process>& p, int index, int total_time) {
    int count = 0;
    for (vector<int>::iterator it = p[index].burst.begin(); it != p[index].burst.end(); it++) {
        if (count == 0) {
            it = p[index].burst.erase(it);
            break;
        }
        else {
            count++;
        }
    }
    //CPU burst 하나 삭제
    
    if(p[index].burst.size() > 0) {
        p[index].come = total_time + p[index].burst[0];
        for (vector<int>::iterator it = p[index].burst.begin(); it != p[index].burst.end(); it++) {
            if (count == 0) {
                it = p[index].burst.erase(it);
                break;
            }
            else {
                count++;
            }
        }
        //사이즈가 0이 아니면 하나더 삭제
    }
    if(p[index].burst.size() == 0) {
        p[index].end = true;
    }
}

void push_pro(vector<Process> &p, queue<int> &ready_q, int total_time, int num, int index) {
    for(int i=0;i<num;i++) {
        if(p[i].end == true) continue;
        if(p[i].start == 0 && p[i].qu == false && p[i].come <= total_time && p[i].num != index) {
            p[i].start = 1;
            p[i].qu = true;
            ready_q.push(p[i].num);
        }
        else if(p[i].start == 1 && p[i].qu == false && p[i].come <= total_time && p[i].num != index) {
            p[i].qu = true;
            ready_q.push(p[i].num);
        }
        else if(total_time < p[i].come) {
            break;
        }
    }
}

void RR(int num, int q, vector<Process> &p) {
    int total_time;
    vector<Answer> answer;
    if(p[0].come == 0) {
        total_time = 0;
    }
    else {
        total_time = p[0].come;
    }
    //시작시간 설정
    
    queue<int> ready_q;
    for(int i=0;i<num;i++) {
        if(p[i].come == total_time) {
            p[i].start = 1;
            p[i].qu = true;
            ready_q.push(p[i].num);
        }
        else break;
    }
    //시작전 큐에 대기중인 프로세스 push
    
    int exit_num = 0;
    while(exit_num != num){
        if(ready_q.empty()) {
            sort(p.begin(),p.end(),cmp_come_pro);
            bool check = false;
            for(int i=0;i<num;i++) {
                if(p[i].end != true && check == false && p[i].qu == false) {
                    p[i].qu = true;
                    ready_q.push(p[i].num);
                    total_time = p[i].come;
                    check = true;
                }
                else if(p[i].end != true && p[i].come == total_time && check == true && p[i].qu == false) {
                    p[i].qu = true;
                    ready_q.push(p[i].num);
                }
                else if(p[i].end != true){
                    break;
                }
            }
            //도착시간이 제일 작은 놈을 전체시간으로 설정후 그 시간과 같은 애들을 준비큐에 push
        }
        else {
            int index = ready_q.front();
            ready_q.pop();
            sort(p.begin(),p.end(),cmp_num);
            p[index].qu = false;
            
            if(p[index].end == true) continue;
            //큐 제일앞에 있는 놈 index에 번호 저장
            if(p[index].burst[0] <= q){ //타임 슬라이스보다 실행시간이 작거나 같은경우
                p[index].wait_time += (total_time - p[index].come);
                total_time += p[index].burst[0];
                
                delete_vector(p, index, total_time);
                
                if(p[index].end == true) {  //하나 종료시
                    Answer temp;
                    temp.num = p[index].num;
                    temp.wait_time = p[index].wait_time;
                    
                    answer.push_back(temp);
                    exit_num++;
                }
                
                sort(p.begin(),p.end(),cmp_come_pro);
                push_pro(p, ready_q, total_time, num, index);
            }
            else {  //타임 슬라이스보다 실행시간이 큰경우
                p[index].wait_time += (total_time - p[index].come);
                total_time += q;
                
                p[index].burst[0] -= q;
                p[index].come = total_time;
                
                p[index].qu = true;
                sort(p.begin(),p.end(),cmp_come_pro);
                push_pro(p, ready_q, total_time, num, index);
                ready_q.push(index);
            }
        }
    }
    
    sort(answer.begin(),answer.end(),cmp_ans_num);
    for(int i=0;i<num;i++) {
        out << i+1 << " " << answer[i].wait_time << endl;
    }
}

int main(void) {
    int num,q;
    inp >> num >> q;
    
    vector<Process> p;
    
    for(int i=0;i<num;i++) {
        Process temp_pro;
        temp_pro.num = i;
        int t,k;
        inp >> t >> k;
        temp_pro.come = t;
        for(int j=0;j<k;j++) {
            int temp;
            inp >> temp;
            temp_pro.burst.push_back(temp);
        }
        temp_pro.wait_time = 0;
        temp_pro.start = 0;
        temp_pro.end = false;
        temp_pro.qu = false;
        p.push_back(temp_pro);
    }
    
    RR(num,q,p);
}
