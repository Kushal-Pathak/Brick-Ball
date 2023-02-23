#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#define h 20
#define w 21
using namespace std;

struct hitter {
	int len = 6;
	int pos = w / 2 - len / 2;
};
struct pong {
	int x = w / 2, y = h / 2 + 5;
	int vx = 1, vy = -1;
	char ball = 'o';
};
hitter player;
pong ball;
char play = 'y';
int score = 0;
int game_over = 0;
char buffer[h][w];
char brick = (char)254;
void init_buffer();
void render();
void bind_objects();
void update_ball();
void detect_collision();
void control();
void game_over_message();
void home_screen();
void reset_game();

int main() {
	home_screen();
	while (play == 'y') {
		init_buffer();
		reset_game();
		while (!game_over) {
			bind_objects();
			render();
			update_ball();
			detect_collision();
			control();
			Sleep(100);
		}
		game_over_message();
	}
	return 0;
}

void game_over_message() {
	cout << "\n\t        Game Over!" << endl;
	cout << "\t      Play Again (y)? ";
	cin >> play;
}
void home_screen() {
	cout << "a: left d: right" << endl;
	cout << "Press any key to start the game...";
	play = _getch();
	play = 'y';
}
void reset_game() {
	game_over = 0;
	score = 1;
	play = 'y';
	ball.x = w / 2; ball.y = h / 2;
	ball.vx = 1; ball.vy = -1;
	player.pos = w / 2 - player.len / 2;
}

void control() {
	if (_kbhit()) {
		char c;
		c = _getch();
		int move = 4;
		switch (c) {
		case 'a':
			player.pos -= move;
			if (player.pos <= 0) player.pos = 1;
			for (int i = 1; i < w - 1; i++) buffer[h - 2][i] = ' ';
			break;
		case 'd': 
			player.pos += move;
			int right = player.pos + player.len - 1;
			int excess = w - 1 - right;
			if (excess <= 0) {
				player.pos -= 1;
				player.pos += excess;
				
			}
			for (int i = 1; i < w - 1; i++) buffer[h - 2][i] = ' ';
			break;
		}
	}
}

void detect_collision() {
	if (ball.y > h - 2) {
		game_over = 1;
	}
	//player collision
	for (int i = player.pos; i < player.pos + player.len; i++) {
		if (ball.y == h - 4 && ball.x == i) ball.vy = -ball.vy;
	}
	//wall collision
	if (ball.x >= w - 2 || ball.x <= 1) {
		ball.vx = -ball.vx;
	}
	if (ball.y <= 1) {
		ball.vy = -ball.vy;
	}

	int flag = 0;
	//brick collision
	if (buffer[ball.y + ball.vy][ball.x] == brick) {
		buffer[ball.y + ball.vy][ball.x] = ' ';
		ball.vy = -ball.vy;
		flag = 1;
		score++;
	}
	 if (buffer[ball.y][ball.x + ball.vx] == brick && !flag) {
		buffer[ball.y][ball.x + ball.vx] = ' ';
		ball.vx = -ball.vx;
		score++;
	}
}

void update_ball() {
	buffer[ball.y][ball.x] = ' ';
	ball.x += ball.vx;
	ball.y += ball.vy;
}

void bind_objects() {
	for (int i = player.pos; i <= player.pos + player.len - 1; i++) {
		buffer[h - 2][i] = brick;
	}
	buffer[ball.y][ball.x] = ball.ball;
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i < h / 4)buffer[i][j] = brick;
			else buffer[i][j] = ' ';
			if (i == 0)buffer[i][j] = 'X';
			if (j == 0 || j == w - 1)buffer[i][j] = 'X';
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
	cout << "\t\tScore: " << score;
}