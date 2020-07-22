#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)

int main(void) {
	FILE* inp = fopen("timeline.inp", "rt");
	FILE* out = fopen("timeline.out", "wt");

	int num;
	int count;
	int year_first, month_first, day_first;
	int year_second, month_second, day_second;

	int* start;
	int* end;
	int* sum;
	int result = 0;

	fscanf(inp, "%d", &num);
	for (int i = 0; i < num; i++) {
		result = 0;
		fscanf(inp, "%d", &count);
		start = (int*)malloc(sizeof(int) * count);
		end = (int*)malloc(sizeof(int) * count);
		sum = (int*)malloc(sizeof(int) * count * 2);
		for (int j = 0; j < count; j++) {
			fscanf(inp, "%d.%d.%d %d.%d.%d", &year_first, &month_first, &day_first, &year_second, &month_second, &day_second);
			int start1 = year_first * 10000 + month_first * 100 + day_first;
			int end1 = year_second * 10000 + month_second * 100 + day_second;
			start[j] = start1;
			end[j] = end1;
		}

		sort(start, start + count);
		sort(end, end + count);
		copy(start, start + count, sum);
		copy(end, end + count, sum + count);
		sort(sum, sum + count * 2);

		int s_index = 0;
		int e_index = 0;
		int max = result;

		for (int i = 0; i < count * 2; i++) {
			if (end[e_index] == sum[i]) {
				e_index++;
				result--;
				if (result > max) max = result;
			}
			else if (start[s_index] == sum[i]) {
				s_index++;
				result++;
				if (result > max) max = result;
			}
		}
		fprintf(out, "%d\n", max);
	}
	fclose(inp);
	fclose(out);
}