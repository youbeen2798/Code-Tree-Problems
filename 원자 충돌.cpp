#include <iostream>
#include <vector>

using namespace std;

int n; //격자 크기
int m; //원자 개수
int k; //실험 시간

struct info {
	int x;
	int y;
	int m; //질량
	int s; //속도
	int d; //방향
};

vector<info> map[51][51];
vector<info> tmp_map[51][51];
vector<info> wonjas; //원자
vector<info> tmp_wonjas;

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };


pair<int, int> again(int x, int y) {
	int nx = x;
	int ny = y;

	if (n < nx) {
		if (nx % n == 0) {
			nx = n;
		}
		else {
			nx = nx % n;
		}
	}
	else if (nx <= 0) {
		nx = n - abs(nx) % n;
	}

	if (n < ny) {
		if (ny % n == 0) {
			ny = n;
		}
		else {
			ny = ny % n;
		}
	}
	else if (ny <= 0) {
		ny = n - abs(ny) % n;
	}

	return { nx,ny };
}
void one_wonja_move(info i) {
	int x = i.x; //행
	int y = i.y; //열
	int m = i.m; //질량
	int s = i.s; //속도
	int d = i.d; //방향

	int nx = x + s * dx[d];
	int ny = y + s * dy[d];

	pair<int, int> p = again(nx, ny);
	nx = p.first;
	ny = p.second;

	tmp_map[nx][ny].push_back({ nx, ny, m, s, d });

}
void all_wonja_move() {
	//모든 원자는 1초 지날때마다 자신의 방향으로 자신의 속력만큼 이동

	for (int i = 0; i < wonjas.size(); i++) {
		one_wonja_move(wonjas[i]);
	}
}

vector<info> spread(int x, int y) {

	vector<info> before_spread = map[x][y];
	vector<info> after_spread;

	int sum_m = 0; //질량 합
	int sum_s = 0; //속력 합

	bool sangha = false;
	bool deagak = false;

	for (int i = 0; i < before_spread.size(); i++) {
		sum_m += before_spread[i].m;
		sum_s += before_spread[i].s;
		
		if (before_spread[i].d % 2 == 0) {
			sangha = true;
		}
		else {
			deagak = true;
		}
	}

	int average_m = sum_m / 5; //합쳐진 원자의 질량에 5를 나눈 값
	int average_s = sum_s / (before_spread.size()); //원자의 속력에 합쳐진 원자의 개수를 나눈 값

	//질량이 0인 원소라면
	if (average_m == 0) {
		return after_spread;
	}

	//모두 상하좌우 이거나 대각선이라면 상하좌우 값을 가짐
	if ((sangha && !deagak) || (!sangha && deagak)) {
		for (int d = 0; d < 8; d+= 2) {
			after_spread.push_back({ x,y, average_m, average_s, d});
		}
	}
	else {
		for (int d = 1; d < 8; d += 2) {

			after_spread.push_back({ x,y, average_m, average_s, d });
		}
	}

	return after_spread;

}
void plus_wonja() {
	//하나의 칸에 2개 이상의 원자가 있다면 합친다.

	tmp_wonjas.clear();
	vector<info> plus_wonjas; //더해야 하는 원자들

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].size() >= 2) {
				vector<info> v = spread(i, j);
				map[i][j].clear();
				
				for (int i = 0; i < v.size(); i++) {
					plus_wonjas.push_back(v[i]);
					tmp_wonjas.push_back(v[i]); 
				}
			}
			else if(map[i][j].size() == 1) {
				tmp_wonjas.push_back(map[i][j][0]);
			}
		}
	}

	for (int i = 0; i < plus_wonjas.size(); i++) {
		int x = plus_wonjas[i].x;
		int y = plus_wonjas[i].y;
		int m = plus_wonjas[i].m;
		int s = plus_wonjas[i].s;
		int d = plus_wonjas[i].d;

		map[x][y].push_back({ x, y, m,s,d });
	}



	wonjas = tmp_wonjas;
}

void copy() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = tmp_map[i][j];
			tmp_map[i][j].clear();
		}
	}
}

void solution() {

	for (int times = 1; times <= k; times++) {
		all_wonja_move();
		copy();
		plus_wonja();
	}

	int ans = 0;

	for (int i = 0; i < wonjas.size(); i++) {
		ans += wonjas[i].m;
	}
	cout <<  ans;
}

void input() {

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int x, y, m, s, d;
		cin >> x >> y >> m >> s >> d;
		map[x][y].push_back({ m,s,d });
		wonjas.push_back({x, y, m, s, d });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
