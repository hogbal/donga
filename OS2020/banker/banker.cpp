#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

ifstream inp("banker.inp");
ofstream out("banker.out");

typedef struct {
    int number;
    vector<int> Max;
    vector<int> Allocation;
    bool end;
}Process;

typedef struct {
    int process_num;
    vector<int> play;
}Command;

bool cmp_need(vector<int> &Available, vector<Process> &p, int m, int num) {
    int i;
    for (i = 0; i < m; i++) {
        if ((p[num].Max[i] - p[num].Allocation[i]) > Available[i]) //Need가 현재 자원보다 크면
            return false;
    }
    return true;
}

bool request(vector<Process> p, int n, int m, vector<int> Available, int process_num, vector<int> play) {
    for (int i = 0; i < m; i++) {
        if (play[i] > Available[i]) return false;
    }
    //요청한 자원이 남아있는 자원보다 큰경우

    for (int i = 0; i < m; i++) {
        Available[i] -= play[i];
        p[process_num].Allocation[i] += play[i];
    }

    bool check = true;
    for (int i = 0; i < m; i++) {
        if (p[process_num].Max[i] != p[process_num].Allocation[i]) {
            check = false;
            break;
        }
    }
    //요청한 자원을 할당했을때 MAX값과 같아졌을때 check = true

    if (check) {
        p[process_num].end = true;
    }
    //check == true이면 end를 true로 바꾼다

    int Next = 1;
    while (Next) {
        Next = 0;
        for (int i = 0; Next == 0 && i < n; i++) {
            if (p[i].end == false) { //확인 안했다면
                if (cmp_need(Available, p, m, i)) { //Need와 Av비교
                    Next = 1; //i번째 프로세스가 수락됨
                    for (int j = 0; j < m; j++)
                        Available[j] += p[i].Allocation[j]; // i는 할당 받고 푸는 작업을 해야함
                    p[i].end = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (p[i].end == false) {
            //불안정 상태임
            return false;
        }
    }

    return true;
}

void banker(vector<Process> &p, int n, int m, vector<int> &Available) {
    queue<Command> q;

    while (1) {
        string s;
        inp >> s;
        if (s.compare("quit") == 0) {
            break;
        }
        else {
            int process_num;
            vector<int> play;

            inp >> process_num;

            for (int i = 0; i < m; i++) {
                int temp;
                inp >> temp;
                play.push_back(temp);
            }

            if (s.compare("request") == 0) {    //request일 경우
                bool check = false;
                for (int i = 0; i < m; i++) {
                    if (play[i] > (p[process_num].Max[i] - p[process_num].Allocation[i])) {
                        check = true;
                        break;
                        //Need보다 request가 더크다 할당할수 없는 경우이므로 큐에 저장도 안하고 종료
                    }
                }
                if (!check) {  //안정상태일때 실행
                    check = request(p, n, m, Available, process_num, play);
                    if (check) {
                        for (int i = 0; i < m; i++) {
                            Available[i] -= play[i];
                            p[process_num].Allocation[i] += play[i];
                        }
                    }
                    else {  //요청한 자원이 보유중인 자원보다 큰경우, 불안정 상태일경우 큐에 저장
                        Command c;
                        c.play = play;
                        c.process_num = process_num;
                        q.push(c);
                    }
                }

                //출력
                for (int i = 0; i < m; i++) {
                    out << Available[i] << " ";
                }
                out << endl;
            }
            else {
                for (int i = 0; i < m; i++) {
                    Available[i] += play[i];
                    p[process_num].Allocation[i] -= play[i];
                }
                //자원을 일단 반환받음

                int count = q.size();

                for (int i = 0; i < count; i++) {
                    vector<int> temp_play = q.front().play;
                    int temp_num = q.front().process_num;
                    q.pop();
                    //대기큐에 제일앞에있는놈을 pop

                    bool check = false;
                    for (int i = 0; i < m; i++) {
                        if (temp_play[i] > (p[temp_num].Max[i] - p[temp_num].Allocation[i])) {
                            check = true;
                            break;
                            //Need보다 request가 더크다 할당할수 없는 경우이므로 큐에 저장도 안하고 종료
                        }
                    }
                    if (!check) {
                        check = request(p, n, m, Available, temp_num, temp_play);
                        //Need보다 request인 경우는 없으므로
                        if (check) {
                            for (int j = 0; j < m; j++) {
                                Available[j] -= temp_play[j];
                                p[temp_num].Allocation[j] += temp_play[j];
                            }
                        }
                        else {
                            Command com_temp;
                            com_temp.play = temp_play;
                            com_temp.process_num = temp_num;
                            q.push(com_temp);
                        }
                    }
                }

                for (int i = 0; i < m; i++) {
                    out << Available[i] << " ";
                }
                out << endl;
            }
        }
    }
}

int main(void) {
    int n, m; //n = 총 프로세스의 수, m = 자원의 종류
    inp >> n >> m;

    vector<int> Available;
    vector<Process> p;

    for (int i = 0; i < m; i++) {
        int temp;
        inp >> temp;
        Available.push_back(temp);
    }

    for (int i = 0; i < n; i++) {
        Process temp;
        temp.number = i;
        temp.end = false;
        for (int j = 0; j < m; j++) {
            int num;
            inp >> num;
            temp.Max.push_back(num);
        }
        p.push_back(temp);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num;
            inp >> num;
            p[i].Allocation.push_back(num);
            Available[j] -= num;
        }
    }
    //입력끝
    banker(p, n, m, Available);
}
