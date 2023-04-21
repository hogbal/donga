#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp("allocation.inp");
ofstream out("allocation.out");

typedef struct {
    int PID;
    int request_time;
    int execution_time;
    int size;
}Process;

typedef struct {
    int PID;
    int return_time;
}Process_exe;

typedef struct{
    int address;
    int PID;
    int size;
}Memory;

bool cmp_time(const Process_exe &p1, const Process_exe &p2){    //시간순으로 정렬
    if(p1.return_time < p2.return_time) return true;
    else return false;
}

void delete_vector_mem(vector<Memory>& p, int index) {  //벡터 mem 요소 삭제 함수
    int count = 0;
    for (vector<Memory>::iterator it = p.begin(); it != p.end(); it++) {
        if (count == index) {
            it = p.erase(it);
            break;
        }
        else {
            count++;
        }
    }
}

int mem_allocation_first(Process p, vector<Memory> &mem) {  //First를 위한 메모리 할당 위치 찾기
    int index = -1;
    for(int i=0;i<mem.size();i++) {
        if(mem[i].PID == -1 && p.size <= mem[i].size) {
            index = i;
            break;
        }
    }
    return index;
}

int mem_allocation_best(Process p, vector<Memory> &mem) {   //Best를 위한 메모리 할당 위치 찾기
    int index = -1;
    int min = -1;
    for(int i=0;i<mem.size();i++) {
        if(mem[i].PID == -1 && p.size <= mem[i].size) { //메모리가 비어있고 메모리의 사이즈가 요청 사이즈보다 크거나 같은경우
            index = i;
            if(min == -1) { //아직 최소값이 없는 경우
                min = index;
            }
            else {
                if(mem[min].size > mem[index].size) {   //최소값의 사이즈가 더 큰경우 최소값 갱신
                    min = index;
                }
            }
        }
    }
    return min;
}

int mem_allocation_worst(Process p, vector<Memory> &mem) {  //Worst를 위한 메모리 할당 위치 찾기
    int index = -1;
    int max = -1;
    for(int i=0;i<mem.size();i++) {
        if(mem[i].PID == -1 && p.size <= mem[i].size) {
            index = i;
            if(max == -1) {
                max = index;
            }
            else {
                if(mem[max].size < mem[index].size) {
                    max = index;
                }
            }
        }
    }
    return max;
}

int mem_allocation(Process p, vector<Memory> &mem, int index) { //프로세스를 입력받은 메모리의 위치에 할당
    int address = mem[index].address;
    Memory temp;
    temp.PID = -1;
    temp.address = mem[index].address + p.size;
    temp.size = mem[index].size - p.size;
    //메모리의 크기가 남을수도 있으므로 임시로 만듬
    
    mem[index].PID = p.PID;
    mem[index].size = p.size;
    //메모리 정보 수정
    
    if(temp.size != 0) {    //크기가 남는다면 메모리 추가
        vector<Memory>::iterator it;

        it = mem.begin()+index+1;
        mem.insert(it, temp);
    }
    
    return address;
}

void mem_return(Process_exe p, vector<Memory> &mem) {   //프로세스와 메모리 위치를 찾아서 메모리 반환
    for(int i=0;i<mem.size();i++) {
        if(p.PID == mem[i].PID) {
            mem[i].PID = -1;
            break;
        }
    }
    //메모리 반환 완료
}

void mem_merge(vector<Memory> &mem) {
    for(int i=0;i<mem.size()-1;i++) {
        if(i+1 < mem.size()) {  //mem의 인덱스 번호를 넘지 않으면서
            if(mem[i].PID == -1 && mem[i+1].PID == -1){ //연속된 메모리가 비어있으면
                mem[i].size += mem[i+1].size;
                vector<Memory>::iterator it;

                it = mem.begin()+i+1;
                mem.erase(it);
                i--;
            }
        }
    }
    //빈 메모리가 연속적이면 합병하는 과정
}

bool find_seq(Process *p, Process_exe *exe_p, int index_p, int index_e, int n){
    if(index_p == n) {  //모든 프로세스를 메모리에 적재 or 큐에 저장
        return false;
    }
    else if(index_e == n) { //메모리에 들어간 프로세스가 없음, 모든 프로세스 종료
        return true;
    }
    else if(index_e == -1) {    //메모리에 적재된 프로세스가 없음 시작전
        return true;
    }
    else {
        if(p[index_p].request_time >= exe_p[index_e].return_time) {  //메모리 반환을 요청하는 프로세스의 시간이 더 빠른경우
            return false;
        }
        else {  //메모리 적재를 요청하는 프로세스의 시간이 더 빠른경우
            return true;
        }
    }
}

void First_fit(Process *p, Process_exe *exe_p, int n) {
    vector<Memory> mem;
    queue<int> q;   //PID가 저장 PID == p의 인덱스 번호
    
    Memory start;
    start.PID = -1;
    start.address = 0;
    start.size = 1000;
    mem.push_back(start);
    
    int index_p = 0;    //실행하지 않은 프로세스 인덱스 번호
    int index_e_push = -1;  //메모리 적재한 프로세스의 마지막에 넣은 인덱스 번호
    int index_e = -1;   //메모리 적재한 프로세스 번호
    
    bool while_exit = true;
    int address;
    while(while_exit){
        bool next_check = find_seq(p, exe_p, index_p, index_e, n);
        if(next_check) {    //메모리에 프로세스를 적재할 경우
            int index = mem_allocation_first(p[index_p], mem);
            if(index == -1) {   //메모리에 적재할곳이 없는 경우!
                q.push(p[index_p].PID);
                index_p++;
            }
            else {
                address = mem_allocation(p[index_p], mem, index);
                //찾아놓은 메모리 위치에 프로세스 적재후 address에 주소 반환
                if(p[index_p].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                    out << address  << endl;
                    while_exit = false;
                }
                else {
                    index_e_push++;
                    exe_p[index_e_push].PID = p[index_p].PID;
                    exe_p[index_e_push].return_time = (p[index_p].request_time + p[index_p].execution_time);
                    //메모리를 할당받았으니 exe_p에 push_back;
                    index_p++;
                    sort(exe_p,exe_p+index_e_push+1,cmp_time);
                    if(index_e == -1) index_e++;
                }
            }
        }
        else {  //메모리를 반환할 경우
            int time = exe_p[index_e].return_time;
            for(int i=index_e;i<n;i++) {
                if(exe_p[i].return_time == time) {
                    mem_return(exe_p[i],mem);
                }
                else {
                    index_e = i;
                    mem_merge(mem);
                    break;
                }
            }
            //메모리 반환 및 합병
            long count = q.size();
            for(int i=0;i<count;i++) {
                int q_PID = q.front();
                q.pop();
                //큐에서 PID를 꺼내옴
                
                int index = mem_allocation_first(p[q_PID], mem);
                if(index == -1) {   //만약 적재할 공간이 없으면
                    q.push(q_PID);
                    continue;
                    //다시 푸시후 continue
                }
                else {  //적재할 공간이 있으면
                    address = mem_allocation(p[q_PID], mem, index);
                    if(p[q_PID].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                        out << address  << endl;
                        while_exit = false;
                    }
                    else {
                        index_e_push++;
                        exe_p[index_e_push].PID = p[q_PID].PID;
                        exe_p[index_e_push].return_time = (time + p[q_PID].execution_time);
                        //메모리를 할당받았으니 exe_p에 push_back;
                        sort(exe_p,exe_p+index_e_push+1,cmp_time);
                        if(index_e == -1) index_e++;
                    }
                }
            }
        }
    }
}

void Best_fit(Process *p, Process_exe *exe_p, int n) {
    vector<Memory> mem;
    queue<int> q;   //PID가 저장 PID == p의 인덱스 번호
    
    Memory start;
    start.PID = -1;
    start.address = 0;
    start.size = 1000;
    mem.push_back(start);
    
    int index_p = 0;
    int index_e_push = -1;
    int index_e = -1;
    
    bool while_exit = true;
    int address;
    while(while_exit){
        bool next_check = find_seq(p, exe_p, index_p, index_e, n);
        if(next_check) {    //메모리에 프로세스를 적재할 경우
            int index = mem_allocation_best(p[index_p], mem);
            if(index == -1) {   //메모리에 적재할곳이 없는 경우!
                q.push(p[index_p].PID);
                index_p++;
            }
            else {
                address = mem_allocation(p[index_p], mem, index);
                //찾아놓은 메모리 위치에 프로세스 적재후 address에 주소 반환
                if(p[index_p].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                    out << address  << endl;
                    while_exit = false;
                }
                else {
                    index_e_push++;
                    exe_p[index_e_push].PID = p[index_p].PID;
                    exe_p[index_e_push].return_time = (p[index_p].request_time + p[index_p].execution_time);
                    //메모리를 할당받았으니 exe_p에 push_back;
                    index_p++;
                    sort(exe_p,exe_p+index_e_push+1,cmp_time);
                    if(index_e == -1) index_e++;
                }
            }
        }
        else {  //메모리를 반환할 경우
            int time = exe_p[index_e].return_time;
            for(int i=index_e;i<n;i++) {
                if(exe_p[i].return_time == time) {
                    mem_return(exe_p[i],mem);
                }
                else {
                    index_e = i;
                    mem_merge(mem);
                    break;
                }
            }
            long count = q.size();
            for(int i=0;i<count;i++) {
                int q_PID = q.front();
                q.pop();
                //큐에서 PID를 꺼내옴
                
                int index = mem_allocation_best(p[q_PID], mem);
                if(index == -1) {   //만약 적재할 공간이 없으면
                    q.push(q_PID);
                    continue;
                    //다시 푸시후 continue
                }
                else {  //적재할 공간이 있으면
                    address = mem_allocation(p[q_PID], mem, index);
                    if(p[q_PID].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                        out << address  << endl;
                        while_exit = false;
                    }
                    else {
                        index_e_push++;
                        exe_p[index_e_push].PID = p[q_PID].PID;
                        exe_p[index_e_push].return_time = (time + p[q_PID].execution_time);
                        //메모리를 할당받았으니 exe_p에 push_back;
                        sort(exe_p,exe_p+index_e_push+1,cmp_time);
                        if(index_e == -1) index_e++;
                    }
                }
            }
        }
    }
}

void Worst_fit(Process *p, Process_exe *exe_p, int n) {
    vector<Memory> mem;
    queue<int> q;   //PID가 저장 PID == p의 인덱스 번호
    
    Memory start;
    start.PID = -1;
    start.address = 0;
    start.size = 1000;
    mem.push_back(start);
    
    int index_p = 0;
    int index_e_push = -1;
    int index_e = -1;
    
    bool while_exit = true;
    int address;
    while(while_exit){
        bool next_check = find_seq(p, exe_p, index_p, index_e, n);
        if(next_check) {    //메모리에 프로세스를 적재할 경우
            int index = mem_allocation_worst(p[index_p], mem);
            if(index == -1) {   //메모리에 적재할곳이 없는 경우!
                q.push(p[index_p].PID);
                index_p++;
            }
            else {
                address = mem_allocation(p[index_p], mem, index);
                //찾아놓은 메모리 위치에 프로세스 적재후 address에 주소 반환
                if(p[index_p].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                    out << address  << endl;
                    while_exit = false;
                }
                else {
                    index_e_push++;
                    exe_p[index_e_push].PID = p[index_p].PID;
                    exe_p[index_e_push].return_time = (p[index_p].request_time + p[index_p].execution_time);
                    //메모리를 할당받았으니 exe_p에 push_back;
                    index_p++;
                    sort(exe_p,exe_p+index_e_push+1,cmp_time);
                    if(index_e == -1) index_e++;
                }
            }
        }
        else {  //메모리를 반환할 경우
            int time = exe_p[index_e].return_time;
            for(int i=index_e;i<n;i++) {
                if(exe_p[i].return_time == time) {
                    mem_return(exe_p[i],mem);
                }
                else {
                    index_e = i;
                    mem_merge(mem);
                    break;
                }
            }
            long count = q.size();
            for(int i=0;i<count;i++) {
                int q_PID = q.front();
                q.pop();
                //큐에서 PID를 꺼내옴
                
                int index = mem_allocation_worst(p[q_PID], mem);
                if(index == -1) {   //만약 적재할 공간이 없으면
                    q.push(q_PID);
                    continue;
                    //다시 푸시후 continue
                }
                else {  //적재할 공간이 있으면
                    address = mem_allocation(p[q_PID], mem, index);
                    if(p[q_PID].PID == (n-1)) {   //마지막 프로세스를 메모리에 적재했으면
                        out << address  << endl;
                        while_exit = false;
                    }
                    else {
                        index_e_push++;
                        exe_p[index_e_push].PID = p[q_PID].PID;
                        exe_p[index_e_push].return_time = (time + p[q_PID].execution_time);
                        //메모리를 할당받았으니 exe_p에 push_back;
                        sort(exe_p,exe_p+index_e_push+1,cmp_time);
                        if(index_e == -1) index_e++;
                    }
                }
            }
        }
    }
}


int main(void) {
    int n;
    inp >> n;
    
    Process *p;
    p = new Process[n];
    
    Process_exe *exe_first;
    exe_first = new Process_exe[n];
    
    Process_exe *exe_best;
    exe_best = new Process_exe[n];
    
    Process_exe *exe_worst;
    exe_worst = new Process_exe[n];
    
    for(int i=0;i<n;i++) {
        p[i].PID = i;
        exe_first[i].return_time = -1; exe_best[i].return_time = -1; exe_worst[i].return_time = -1;
        inp >> p[i].request_time >> p[i].execution_time >> p[i].size;
    }
    
    First_fit(p, exe_first, n);
    Best_fit(p, exe_best, n);
    Worst_fit(p, exe_worst, n);
}
