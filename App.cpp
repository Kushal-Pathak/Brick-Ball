#include <iostream>
#include <conio.h>
#include <windows.h>
#define h 26
#define w 40
using namespace std;

struct hitter {
	int len = 4;
	int pos = w / 2 - len / 2;
};
struct pong {
	int x = w / 2, y = h / 2 + 5;
	int vx = 1, vy = -1;
	char ball = 'o';
};
hitter player;
pong ball;
int game_over = 0;
char buffer[h][w];
char brick = (char)254;
void init_buffer();
void render();
void bind_objects();


int main() {
	init_buffer();
	while (!game_over) {
		bind_objects();
		render();
		Sleep(300);
	}
	return 0;
}

void bind_objects() {
	for (int i = player.pos; i <= player.pos + player.len; i++) {
		buffer[h - 2][i] = brick;
	}
	buffer[ball.y][ball.x] = ball.ball;
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i < h / 2)buffer[i][j] = brick;
			else buffer[i][j] = ' ';
			if (i == 0 || i == h - 1)buffer[i][j] = brick;
			if (j == 0 || j == w - 1)buffer[i][j] = brick;
		}
	}
}
void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout<<buffer[i][j] << " ";
		}
		cout << endl;
	}
}