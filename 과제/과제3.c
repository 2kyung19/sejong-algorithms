#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include<time.h>

#define MAX 50

int H[MAX];
int A[MAX];

int minimum(int x, int y);
int airtelDC(int n, int s, int d);
int rAirtelDC(int s, int d);
int airtelDP(int n, int s, int d);

int main() {
	int mini[3][2] = { {0,4},{2,5},{2,4} }; //mini test (s,d)
	int n, s, d, mincost;
	int i;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	A[0] = 0; A[1] = 1; //항공요금
	for (i = 2; i < MAX; i++) {
		A[i] = A[i - 1] + (A[i - 1] % 5) + 3;
	}

	H[0] = 0; H[1] = 5; //숙박요금
	for (i = 2; i < MAX; i++) {
		H[i] = (H[i - 1] + i) % 9 + 1;
	}

	//header
	printf("%-3c %-3c %-3c %-8s %-8s %-10s\n", 'n', 's', 'd', "mincost", "version", "cputime");

	//Test run for mini input
	n = 6;
	for (i = 0; i < 3; i++) {
		s = mini[i][0];
		d = mini[i][1];

		//DC
		QueryPerformanceCounter(&start);
		mincost = airtelDC(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%-3d %-3d %-3d %-8d %-8s %-10f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		//DP
		QueryPerformanceCounter(&start);
		mincost = airtelDP(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%-3d %-3d %-3d %-8d %-8s %-10f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
	}

	//Main run for big input
	n = MAX / 2;
	s = 1, d = n - 2;

	//DC
	QueryPerformanceCounter(&start);
	mincost = airtelDC(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%-3d %-3d %-3d %-8d %-8s %-10f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	//DP
	QueryPerformanceCounter(&start);
	mincost = airtelDP(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%-3d %-3d %-3d %-8d %-8s %-10f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	return 0;
}

int minimum(int x, int y) {
	if (x < y) return x;
	else return y;
}

int airtelDC(int n, int s, int d) { //분할통치법
	return rAirtelDC(s, d);
}

int rAirtelDC(int s, int d) { //정방향
	int mincost = 99999; //infinite
	int cost;

	if (s == d) return 0;

	for (int k = 0; k < d; k++) {
		cost = rAirtelDC(s, k) + H[k] + A[d - k];
		mincost = minimum(mincost, cost);
	}

	return mincost;
} //O(2^n)

int airtelDP(int n, int s, int d) { //동적프로그래밍-정방향
	int* m = (int*)malloc(sizeof(int) * n);
	int cost;

	m[s] = 0;

	for (int i = s + 1; i <= d; i++) {
		m[i] = 99999; ////infinite

		for (int k = s; k < i; k++) {
			cost = m[k] + H[k] + A[i - k];
			m[i] = minimum(m[i], cost);
		}
	}

	return m[d];
} //O(n^2)
