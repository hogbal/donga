#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream inp("srtf.inp");
ofstream out("srtf.out");

typedef struct {
    int number;
    int come;
    int use_time;
}Process;

//cpu사용시간이 제일작은순, 그다음으로 도착시간, 그다음 프로세스 번호(우선순위 정렬)
bool cmp(const Process& p1, const Process& p2) {
    if (p1.use_time < p2.use_time) return true;
    else if (p1.use_time == p2.use_time) {
        if (p1.come < p2.come) return true;
        else if (p1.come == p2.come) return p1.number < p2.number;
        else return false;
    }
    else return false;
}

//제일먼저 도착하고 사용시간이 제일 작고 프로세스 넘버가 제일 작은순으로 정렬(도착시간 제외 우선순위 정렬)
bool first(const Process& p1, const Process& p2) {
    if (p1.come < p2.come) return true;
    else if (p1.come == p2.come) {
        if (p1.use_time < p2.use_time) return true;
        else if (p1.use_time == p2.use_time) return p1.number < p2.number;
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
void start(vector<Process>& p) {
    sort(p.begin(), p.end(), first);
    if (p[0].come != 0) {
        int temp = p[0].come;
        for (int i = 0; i < p.size(); i++) {
            p[i].come -= temp;
        }
    }
}

int find(vector<Process>& p, Process temp, int working_time) {  //temp 프로세스 작업중에 다음실행할 프로세스 찾는 함수
    int index = -1;
    sort(p.begin(),p.end(),first);
    for(int i=0;i < p.size();i++) {
        if(p[i].number == temp.number && index == -1) {
            index = i;
            continue;
        }
        else {
            if(p[i].come <= working_time) { //이미 도착해있는 경우
                if(p[i].use_time < temp.use_time) {
                    index = i;
                    break;
                }
            }
            else { //temp 프로세스 진행중에 도착할경우
                if(p[i].come < (working_time+temp.use_time) && p[i].use_time < (temp.use_time - (p[i].come - working_time))) {
                    index = i;
                    break;
                }
            }
        }
    }
    
    int num = p[index].number;
    sort(p.begin(),p.end(),cmp);
    for(index=0;p.size();index++) {
        if(num == p[index].number) break;
    }
    return index;
}

void next_find(vector<Process>& p, Process *temp, int *working_time, int *waiting_time) {  //프로세스가 삭제된후 다음 실행한 프로세스 찾는 함수
    bool check = false;
    
    for(int i=0;i<p.size();i++) {
        if(p[i].come <= (*working_time)) {
            temp->number = p[i].number;
            temp->come = p[i].come;
            temp->use_time = p[i].use_time;
            check = true;
            break;
        }
    }
    if(check == false) {
        sort(p.begin(),p.end(),first);
        temp->number = p[0].number;
        temp->come = p[0].come;
        temp->use_time = p[0].use_time;
        (*working_time) = temp->come;
    }
}

//watiting time 시간 계산
int srtf(vector<Process>& p, int num) {
    int waiting_time = 0;
    int working_time = 0;
    Process temp;   //작업중인 프로세스
    
    start(p);
    temp.number = p[0].number;
    temp.come = p[0].come;
    temp.use_time = p[0].use_time;
    
    while(p.size() != 0) {
        int index = find(p,temp,working_time);  //새로 시작할 프로세스
        
        if(p[index].number == temp.number) {    //작업중인 프로세스를 그대로 사용
            int temp_use_temp = p[index].use_time;
            delete_vector(p, index);
            
            working_time += temp_use_temp;
            next_find(p, &temp, &working_time, &waiting_time);
            waiting_time += working_time - temp.come;
        }
        else {  //새로운 프로세스를 실행해야 할때
            int temp_work = working_time;
            working_time += (p[index].come - working_time);
            waiting_time += (working_time - p[index].come);
            
            int i;
            for(i=0;i<p.size();i++) {
                if(p[i].number == temp.number) {
                    p[i].come = working_time;
                    p[i].use_time -= (working_time - temp_work);
                    break;
                }
            }
            
            temp.number = p[index].number;
            temp.come = p[index].come;
            temp.use_time = p[index].use_time;
            
            if(p[i].use_time == 0) {
                delete_vector(p, i);
                next_find(p, &temp, &working_time, &waiting_time);
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
        p.push_back(temp);
    }
    out << srtf(p, num) << endl;
}
