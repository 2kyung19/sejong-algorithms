#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

typedef struct robot {
	int x; //x좌표
	int y; //y좌표
	int d; //방향
} ROBOT;

int main() {
	ROBOT* robot; //로봇 배열
	int A, B, N, M; //가로 값, 세로 값, 로봇 수, 명령 수
	int x, y, near, robotN, repeat;
	char d, order;
	int i, j;

	int Xro = 0, Yro = 0; //X로봇, Y로봇 (오류가 났을 경우)

	char dire[4] = { 'N','E','S','W' }; //방향

	scanf("%d %d", &A, &B); //가로 값 , 세로 값
	scanf("%d %d", &N, &M); //로봇 수, 명령 수

	robot = (ROBOT*)malloc(sizeof(ROBOT) * (N + 1));
	robot[0].x = 0; robot[0].y = 0; robot[0].d = 0; //오류 감지에 사용 + 인덱스를 1부터 시작하기 위해

	//로봇 초기화
	for (i = 1; i <= N; i++) {
		scanf("%d %d %c", &x, &y, &d); //x좌표, y좌표, 방향
		getchar();

		robot[i].x = x; robot[i].y = y;

		if (d == 'N') robot[i].d = 0;
		else if (d == 'E') robot[i].d = 1;
		else if (d == 'S') robot[i].d = 2;
		else if (d == 'W') robot[i].d = 3;
	}

	//명령
	for (i = 0; i < M; i++) {
		scanf("%d %c %d", &robotN, &order, &repeat); //작동할 로봇 넘버, 명령, 반복

		if (Xro != 0) continue; //이미 오류가 있다면

		if (order == 'R') { //우회전
			robot[robotN].d = (robot[robotN].d + repeat) % 4;
		}

		else if (order == 'L') { //좌회전
			robot[robotN].d = (robot[robotN].d - repeat) % 4;

			if (robot[robotN].d < 0) {
				robot[robotN].d = robot[robotN].d + 4;
			}
		}

		else if (order == 'F') { //직진
			near = 0; //robotN 로봇과 가장 가까운 로봇 (초기값 0)

			if (robot[robotN].d == 0) { //N
				robot[near].y = B + 1; //y의 최댓값

				for (j = 1; j <= N; j++) { //가까운 로봇 찾기
					if (j == robotN) continue;

					//robotN 로봇이 움직일 방향에서 가장 앞에 있는 로봇 찾기 
					if (robot[j].x == robot[robotN].x && robot[j].y > robot[robotN].y&& robot[j].y < robot[near].y) {
						near = j;
					}
				}

				if (near == 0) { //앞에있는 로봇이 없을 때
					if ((robot[robotN].y + repeat) <= B) { 
						robot[robotN].y = robot[robotN].y + repeat;
					}

					else { //벽에 충돌하는 경우
						Xro = robotN;
					}
				}

				else { //앞에 로봇이 있을 때
					if ((robot[robotN].y + repeat) < robot[near].y) {
						robot[robotN].y = robot[robotN].y + repeat;
					}

					else { //로봇끼리 충돌
						Xro = robotN;
						Yro = near;
					}
				}

			}

			else if (robot[robotN].d == 1) { //E
				robot[near].x = A + 1; //x의 최댓값

				for (j = 1; j <= N; j++) { //가까운 로봇 찾기
					if (j == robotN) continue;

					//robotN 로봇이 움직일 방향에서 가장 앞에 있는 로봇 찾기 
					if (robot[j].y == robot[robotN].y && robot[j].x > robot[robotN].x&& robot[j].x < robot[near].x) {
						near = j;
					}
				}

				if (near == 0) { //앞에있는 로봇이 없을 때
					if ((robot[robotN].x + repeat) <= A) {
						robot[robotN].x = robot[robotN].x + repeat;
					}

					else { //벽에 충돌하는 경우
						Xro = robotN;
					}
				}


				else { //앞에 로봇이 있을 때
					if ((robot[robotN].x + repeat) < robot[near].x) {
						robot[robotN].x = robot[robotN].x + repeat;
					}

					else { //로봇끼리 충돌
						Xro = robotN;
						Yro = near;
					}
				}
			}

			else if (robot[robotN].d == 2) { //S
				robot[near].y = 0; //y의 최솟값

				for (j = 1; j <= N; j++) { //가까운 로봇 찾기
					if (j == robotN) continue;

					//robotN 로봇이 움직일 방향에서 가장 앞에 있는 로봇 찾기 
					if (robot[j].x == robot[robotN].x && robot[j].y < robot[robotN].y && robot[j].y > robot[near].y) {
						near = j;
					}
				}

				if (near == 0) { //앞에있는 로봇이 없을 때
					if ((robot[robotN].y - repeat) > 0) {
						robot[robotN].y = robot[robotN].y - repeat;
					}

					else { //벽에 충돌하는 경우
						Xro = robotN;
					}
				}

				else { //앞에 로봇이 있을 때
					if ((robot[robotN].y - repeat) > robot[near].y) {
						robot[robotN].y = robot[robotN].y - repeat;
					}

					else { //로봇끼리 충돌
						Xro = robotN;
						Yro = near;
					}
				}
			}

			else if (robot[robotN].d == 3) { //W
				robot[near].x = 0; //x의 최솟값
				 
				for (j = 1; j <= N; j++) { //가까운 로봇 찾기
					if (j == robotN) continue;

					//robotN 로봇이 움직일 방향에서 가장 앞에 있는 로봇 찾기 
					if (robot[j].y == robot[robotN].y && robot[j].x < robot[robotN].x && robot[j].x > robot[near].x) {
						near = j;
					}
				}

				if (near == 0) { //앞에있는 로봇이 없을 때
					if ((robot[robotN].x - repeat) > 0) {
						robot[robotN].x = robot[robotN].x - repeat;
					}

					else { //벽에 충돌하는 경우
						Xro = robotN;
					}
				}

				else { //앞에 로봇이 있을 때
					if ((robot[robotN].x - repeat) > robot[near].x) {
						robot[robotN].x = robot[robotN].x - repeat;
					}

					else { //로봇끼리 충돌
						Xro = robotN;
						Yro = near;
					}
				}
			}
		}

	}

	if (Xro == 0) printf("OK"); //오류난 로봇이 없다면
	else if (Xro != 0 && Yro == 0) printf("Robot %d crashes into the wall", Xro); //벽에 충돌한 경우
	else if (Xro != 0 && Yro != 0) printf("Robot %d crashes into robot %d", Xro, Yro); //서로 충돌한 경우

	return 0;
}