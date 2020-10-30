#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("card.inp");
ofstream out("card.out");

typedef struct {
    int value;
    int max;
}Card;

int find_max_23(Card card[], int index){
    int max_index = index-2;
    if(index-3 >= 0) {
        if(card[index-3].max >= card[max_index].max) {
            max_index = index-3;
        }
    }
    return max_index;
}

int find_max_34(Card card[], int index){
    int max_index = index-3;
    if(index-4 >= 0) {
        if(card[index-4].max >= card[max_index].max) {
            max_index = index-4;
        }
    }
    return max_index;
}

int find_max_56(Card card[], int index){
    int max_index = index-5;
    if(index-6 >=0) {
        if(card[index-6].max >= card[max_index].max) {
            max_index = index-6;
        }
    }
    return max_index;
}

void card(){
    int size;
    inp >> size;
    Card *card = new Card[size];
    
    for(int i=0;i<size;i++) {
        inp >> card[i].value;
        card[i].max = 0;
    }
    
    for(int i=0;i<size;i++) {
        if(i<3) {
            card[i].max = card[i].value;
        }
        else if(i==3 || i==4 || i==5) {
            if(i==3) {
                int index = find_max_23(card,i);
                card[i].max = card[index].max + card[i].value;
            }
            else if(i==4) {
                int index1 = i-2;
                int index2 = find_max_34(card, i);
                card[i].max = max(card[index1].max, card[index2].max) + card[i].value;
                
            }
            else {
                int index1 = i-5;
                int index2 = find_max_34(card, i);
                card[i].max = max(card[index1].max + card[i-2].value, card[index2].max) + card[i].value;
            }
        }
        else {
            int index1 = find_max_34(card,i);
            int index2 = find_max_56(card,i);
            card[i].max = max(card[index1].max, card[index2].max+card[i-2].value) + card[i].value;
        }
    }
    out << card[size-1].max << endl;
}

int main(void){
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        card();
    }
}
