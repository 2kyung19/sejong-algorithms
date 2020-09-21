#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<time.h>

int* buildList(int n, int min, int max); //무순리스트 생성
int* copyList(int* L, int n); //무순리스트 L을 복제
void buildHeap(int* H, int n); //무순리스트를 힙으로
int findKthSmallest(int* H, int n, int k); //k번째로 작은 수 찾기
int removeMin(int* H, int n); //최소값 삭제
void downHeap(int* H, int i, int n);
void swapElements(int* H, int i, int j);
void writeList(int* L, int n);

int main(void) {
	int* L, * H;
	int output[5], karray[5] = { 1, 100, 99900, 99999 };
	int e, k;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);
	
	/* n = 10 */
	L = buildList(10, 1, 100);

	writeList(L, 10); //무순리스트 L 출력

	for (k = 1; k <= 3; k++) { //k(=1,2,3) 번째로 작은 수 찾아 출력
		H = copyList(L, 10); //H에 L을 복사
		output[k] = findKthSmallest(H, 10, k);
	}
	writeList(&output, 3);

	free(L); free(H);

	/* n = 100000 */
	L = buildList(100000, 1, 1000000);
	
	for (k = 0; k < 4; k++) { //k(=1,100,99900,99999) 번째로 작은 수 찾아 출력
		H = copyList(L, 100000); //H에 L을 복사

		QueryPerformanceCounter(&start);

		e = findKthSmallest(H, 100000, karray[k]);

		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%-6d  %8.4fms\n",e, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
	}

	free(L); free(H);

	return 0;
}

int* buildList(int n, int min, int max) {
	int *L = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++) { //min ~ max 사이의 rand 값 할당
		L[i] = ((((long)rand() << 15) | rand()) % max) + min;
	}

	return L;
}

int* copyList(int* L, int n) {
	int* H = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++) {
		H[i] = L[i]; //초기 무순리스트 L의 값을 H에 복사
	}

	return H;
}

void buildHeap(int* H, int n) {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(H, i, n); //힙 순서 속성 복구
	}
}

int findKthSmallest(int* H, int n, int k) {
	int smaller = 0;

	buildHeap(H, n); //상향식 힙 생성 : O(n)

	for (int i = 0; i < k; i++) { //k번째로 작은 수 : O(k)
		smaller = removeMin(H, n); //root 삭제 : O(log n)
		n--;
	}//O(k*log n)

	
	return smaller;
}

int removeMin(int* H, int n) {
	int key;
	
	//root에 마지막 노드 값 저장
	key = H[1];
	H[1] = H[n];

	downHeap(H, 1, --n); //마지막 노드 삭제 및 힙순서 속성 복구

	return key; //기존 root 값 반환
}

void downHeap(int *H, int i, int n) {
	int smaller;

	if (i * 2 > n) return; //자식이 없으면

	//왼쪽 자식과 오른쪽 자식 중 작은 값을 저장
	smaller = i * 2;
	if (n >= i * 2 + 1 && H[smaller] > H[i * 2 + 1]) {
		smaller = i * 2 + 1;
	}

	//자식보다 부모가 더 작은 값이면
	if (H[i] <= H[smaller]) return;

	//자식이 부모보다 더 작으면
	swapElements(H, i, smaller);

	downHeap(H, smaller, n);
}

void swapElements(int* H, int i, int j) {
	int temp;

	temp = H[i];
	H[i] = H[j];
	H[j] = temp;
}

void writeList(int* L, int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}