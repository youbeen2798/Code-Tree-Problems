#include <iostream>
#include <vector>

using namespace std;

int n, m, k;

struct info {
	int s; //속력
	int d; //이동 방향
	int b; //크기
};

info map[101][101];

struct after_move_info {
	int x;
	int y;
	int s;
	int d;
	int b; //크기
};

int ans = 0;


void print() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j].d == 0) {
				continue;
			}
		}
	}
}

void catch_virus(int column) {
	//column에 있는 바이러스를 잡는다.

	for (int i = 1; i <= n; i++) {
		if (map[i][column].d != 0) {
			//바이러스가 존재하면
			ans += map[i][column].b;
			map[i][column] = { 0,0,0 }; //바이러스를 없앤다.
			break;
		}
	}
}

after_move_info virus_up_down(int x, int y, int s, int d, int b) {
	//(x,y)에 있는 바이러스가 s라는 속력으로 b만큼 "위 / 아래" 움직인다.

	int nx = x;
	int ny = y;

	for (int i = 0; i < s; i++) {

		if (nx == 1) { //위를 찍었으면 방향을 아래로
			d = 2;
		}
		else if (nx == n) { //아래를 찍었으면 방향을 위로
			d = 1;
		}

		if (d == 1) { //위쪽으로 방향이라면
			nx -= 1; 
		}
		else if (d == 2) { //아래로 방향이라면
			nx++;
		}

	
	}

	return{ nx, ny, s, d, b };
}

after_move_info virus_right_left(int x, int y, int s, int d, int b) {

	//(x,y)에 있는 바이러스가 s라는 속력으로 b만큼 "위 / 아래" 움직인다.

	int nx = x;
	int ny = y;


	for (int i = 0; i < s; i++) {

		if (ny == m) { //오른쪽을 찍었으면 방향을 왼쪽으로
			d = 4;
		}
		else if (ny == 1) { //왼쪽을 찍었으면 방향을 오른쪽으로
			d = 3;
		}

		if (d == 3) { //오른쪽으로 방향이라면
			ny++;
		}
		else if (d == 4) { //왼쪽으로 방향이라면
			ny--;
		}
	}

	return{ nx, ny, s, d, b };
}
after_move_info virus_move(int x, int y, int s, int d, int b) {
	//(x,y)에 있는 바이러스가 s라는 속력으로 d방향으로 b만큼 움직인다.

	//움직인 후 위치
	int nx = x;
	int ny = y;

	if (d <= 2) {
		s = s % (2 * n - 2);
	}
	else {
		s = s % (2 * m - 2);
	}

	if (d == 1 || d == 2) {
		//위쪽, 아래쪽으로
		return virus_up_down(x, y, s, d, b);

	}
	else if (d == 3 || d == 4) {
		//오른쪽, 왼쪽으로
		return virus_right_left(x, y, s, d, b);
	}
	
}
void all_virus_move() {
	//모든 바이러스가 움직인다.
	
	info tmp_map[101][101] = { 0,0,0 };
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j].d != 0) {
				after_move_info p = virus_move(i,j,map[i][j].s, map[i][j].d, map[i][j].b);

				//비어 있거나 더 크다면
				if (tmp_map[p.x][p.y].b < p.b || tmp_map[p.x][p.y].d == 0) {
					tmp_map[p.x][p.y] = { p.s, p.d, p.b };
				}
			}
			map[i][j] = { 0,0,0 };
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (tmp_map[i][j].d != 0) {
				map[i][j] = tmp_map[i][j];
			}
		}
	}

	

}
void solution() {


	for (int i = 1; i <= m; i++) {
		catch_virus(i);
		all_virus_move();
	}

	cout << ans;

}

void input() {

	cin >> n >> m >> k;

	for (int i = 0; i < k; i++) {
		int x, y, s, d, b;
		cin >> x >> y >> s >> d >> b;
		map[x][y] = { s,d,b };

	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
//	print();
	solution();
}