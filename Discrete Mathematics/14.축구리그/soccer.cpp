#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

int rank_a = 1;

FILE* inp;
FILE* out;

typedef struct {
   int vp;
   int goal;
   int away_goal_sum;
   int index;
   int rank;
}Team;

bool com(Team &p1, Team &p2) {
   return p1.index < p2.index;
}

bool compare(Team &p1, Team &p2) {
   if (p1.vp > p2.vp) {
      return 1;
   }
   else if (p1.vp == p2.vp) {
      if (p1.goal > p2.goal) {
         return 1;
      }
      else if (p1.goal == p2.goal) {
         if (p1.away_goal_sum > p2.away_goal_sum) {
            return 1;
         }
         else {
            return 0;
         }
      }
      else {
         return 0;
      }
   }
   else {
      return 0;
   }
}

void soccer(int n, int k) {
   Team *team = (Team*)malloc(sizeof(Team)*n);
   rank_a = 1;
   for (int k = 0; k < n; k++) {
      team[k].goal = 0;
      team[k].vp = 0;
      team[k].away_goal_sum = 0;
      team[k].index = k;
      team[k].rank = -1;
   }
   for (int i = 0; i < k; i++) {
      int home, away;
      int home_goal, away_goal;
      for (int k = 0; k < 2 * (n - 1); k++) {
         for (int j = 0; j < n / 2; j++) {
            fscanf(inp, "%d-%d", &away, &home);
            fscanf(inp, "%d %d", &away_goal, &home_goal);

            if (away_goal > home_goal) {
               team[away - 1].vp += 3;
               team[home - 1].vp += 0;
            }
            else if (away_goal == home_goal) {
               team[away - 1].vp += 1;
               team[home - 1].vp += 1;
            }
            else {
               team[away - 1].vp += 0;
               team[home - 1].vp += 3;
            }
            team[away - 1].goal = team[away - 1].goal + away_goal - home_goal;
            team[home - 1].goal = team[home - 1].goal + home_goal - away_goal;
            team[away - 1].away_goal_sum += away_goal;
         }
      }
   }
   
   sort(team, team + n, compare);
   for (int i = 0; i < n - 1; i++) {
      int count = 0;
      if (team[i].vp == team[i + 1].vp && team[i].goal == team[i + 1].goal && team[i].away_goal_sum == team[i + 1].away_goal_sum) {
         for (int j = i; j < n - 1; j++) {
            if (team[j].vp == team[j + 1].vp && team[j].goal == team[j + 1].goal && team[j].away_goal_sum == team[j + 1].away_goal_sum) {
               count++;
            }
            else {
               break;
            }
         }
         for (int j = i; j < count + i + 1; j++) {
            team[j].rank = rank_a;
         }

         i += count;
         rank_a += (count + 1);
      }
      else {
         team[i].rank = rank_a;
         rank_a++;
      }
   }

   if (team[n - 1].rank == -1) {
      team[n - 1].rank = rank_a;
   }
   sort(team, team + n, com);
   for (int i = 0; i < n; i++) {
      fprintf(out, "%d ", team[i].rank);
   }
}

int main(void) {
   inp = fopen("soccer.inp", "rt");
   out = fopen("soccer.out", "wt");

   int Test_Case;
   fscanf(inp, "%d", &Test_Case);
   for (int i = 0; i < Test_Case; i++) {
      int n, k;
      fscanf(inp, "%d %d", &n, &k);
      fprintf(out, "Test Case #%d: ", i + 1);
      soccer(n, k);
      fprintf(out, "\n");
   }
}