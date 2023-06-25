#include <iostream>

using namespace std;

int n; //격자 크기
int map[501][501];

int start_x;
int start_y;
int answer = 0;


void check(int x, int y, int amount) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		map[x][y] += amount;
	}
	else {
		answer += amount;
	}
}
void left() {

	int prev = map[start_x][start_y - 1];
	int one = prev * 0.01;
	int two = prev * 0.02;
	int five = prev * 0.05;
	int seven = prev * 0.07;
	int ten = prev * 0.1;


	//1퍼센트
	check(start_x + 1, start_y, one);
	check(start_x - 1, start_y, one);

	//2퍼센트
	check(start_x - 2, start_y - 1, two);
	check(start_x + 2, start_y - 1, two);


	//7퍼센트
	check(start_x - 1, start_y - 1, seven);
	check(start_x + 1, start_y - 1, seven);

	//10퍼센트
	check(start_x - 1, start_y - 2, ten);
	check(start_x + 1, start_y - 2, ten);

	//5퍼센트
	check(start_x, start_y - 3, five);

	//남은것
	int remain = prev - (one + two + five + seven + ten) * 2 + five;

	check(start_x, start_y - 2, remain);

	//curr
	map[start_x][start_y - 1] = 0;

	start_y -= 1;

}

void down() {

	int prev = map[start_x + 1][start_y];
	int one = prev * 0.01;
	int two = prev * 0.02;
	int five = prev * 0.05;
	int seven = prev * 0.07;
	int ten = prev * 0.1;


	//1퍼센트
	check(start_x, start_y - 1, one);
	check(start_x, start_y + 1, one);

	//2퍼센트
	check(start_x + 1, start_y - 2, two);
	check(start_x + 1, start_y + 2, two);


	//7퍼센트
	check(start_x + 1, start_y - 1, seven);
	check(start_x + 1, start_y + 1, seven);

	//10퍼센트
	check(start_x + 2, start_y - 1, ten);
	check(start_x + 2, start_y + 1, ten);

	//5퍼센트
	check(start_x + 3, start_y, five);

	//남은것
	int remain = prev - (one + two + five + seven + ten) * 2 + five;
	check(start_x + 2, start_y, remain);

	//curr
	map[start_x + 1][start_y] = 0;

	start_x += 1;

}

void right() {

	int prev = map[start_x][start_y + 1];
	int one = prev * 0.01;
	int two = prev * 0.02;
	int five = prev * 0.05;
	int seven = prev * 0.07;
	int ten = prev * 0.1;

	//1퍼센트
	check(start_x - 1, start_y, one);
	check(start_x + 1, start_y, one);


	//2퍼센트
	check(start_x - 2, start_y + 1, two);
	check(start_x + 2, start_y + 1, two);


	//7퍼센트
	check(start_x - 1, start_y + 1, seven);
	check(start_x + 1, start_y + 1, seven);


	//10퍼센트
	check(start_x - 1, start_y + 2, ten);
	check(start_x + 1, start_y + 2, ten);


	//5퍼센트
	check(start_x, start_y + 3, five);

	//남은것
	int remain = prev - (one + two + five + seven + ten) * 2 + five;
	check(start_x, start_y + 2, remain);

	start_y += 1;

}

void up() {


	int prev = map[start_x - 1][start_y];
	int one = prev * 0.01;
	int two = prev * 0.02;
	int five = prev * 0.05;
	int seven = prev * 0.07;
	int ten = prev * 0.1;

	//1퍼센트
	check(start_x, start_y - 1, one);
	check(start_x, start_y + 1, one);


	//2퍼센트
	check(start_x - 1, start_y - 2, two);
	check(start_x - 1, start_y + 2, two);

	//7퍼센트
	check(start_x - 1, start_y - 1, seven);
	check(start_x - 1, start_y + 1, seven);

	//10퍼센트
	check(start_x - 2, start_y - 1, ten);
	check(start_x - 2, start_y + 1, ten);


	//5퍼센트
	check(start_x - 3, start_y, five);



	//남은것
	int remain = prev - (one + two + five + seven + ten) * 2 + five;
	check(start_x - 2, start_y, remain);

	start_x -= 1;

}

void solution() {

	start_x = n / 2 + 1;
	start_y = n / 2 + 1;

	for (int k = 1; k <= n - 2; k += 2) {
		for (int j = 1; j <= k; j++) {
			left();
		}

		for (int j = 1; j <= k; j++) {
			down();
		}

		for (int j = 1; j <= k + 1; j++) {
			right();
		}

		for (int j = 1; j <= k + 1; j++) {
			up();
		}
	}

	for (int k = 1; k < n; k++) {
		left();
	}

	cout <<  answer;
}

void input() {

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}