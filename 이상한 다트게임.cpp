#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int n; //원판의 개수
int m; //원판 내의 숫자의 개수
int q; //회전 횟수 

deque<int> map[51];

struct info {
	int x; //원판의 종류
	int d; //방향(0: 시계방향, 1: 반시계방향)
	int k; //회전하는 칸 수
};

vector<info> v;


void rotate(info i) {
	int x = i.x;
	int d = i.d;
	int k = i.k;

	if (d == 0) {
		//시계방향이라면

		for (int dart = x; dart <= n; dart+= x) {
			for (int i = 0; i < k; i++) {
				int num = map[dart].back();
				map[dart].pop_back();
				map[dart].push_front(num);
			}
		}
		
	}
	else {
		//반시계방향이라면
		for (int dart = x; dart <= n; dart += x) {
			for (int i = 0; i < k; i++) {
				int num = map[dart].front();
				map[dart].pop_front();
				map[dart].push_back(num);
			}
		}
	}

}

void erase() {

	bool changed = false;

	deque<int> tmp_map[51];
	
	for (int i = 1; i <= n; i++) {
		tmp_map[i] = map[i];
	}

	int sum = 0;
	int cnt = 0;

	//옆
	for (int i = 1; i <= n; i++) {

		for (int j = 0; j < m - 1; j++) {

			if (map[i][j] == -1) {
				continue;
			}

			sum += map[i][j];
			cnt++;

			if (map[i][j] == map[i][j + 1]) {
				changed = true;
				tmp_map[i][j] = -1;
				tmp_map[i][j + 1] = -1;
			}
		}

		if (map[i][m - 1] != -1) {
			cnt++;
			sum += map[i][m - 1];
		}
		if (map[i][0] == map[i][m - 1] && map[i][0] != -1) {
			changed = true;
			tmp_map[i][0] = -1;
			tmp_map[i][m - 1] = -1;
		}
	}

	//위 아래
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == map[i + 1][j] && map[i][j] != -1) {
				changed = true;
				tmp_map[i][j] = -1;
				tmp_map[i + 1][j] = -1;
			}
		}
	}


	if (changed) {
		for (int i = 1; i <= n; i++) {
			map[i] = tmp_map[i];
		}
	}
	else {

		int average = sum / cnt;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {

				if (map[i][j] == -1) {
					continue;
				}
				if (average > map[i][j]) {
					map[i][j]++;
				}
				else if(average < map[i][j]) {
					map[i][j]--;
				}
			}
		}
	}

}
void solution() {

	for (int i = 0; i < q; i++) {
		rotate(v[i]);
		erase();
	}
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] != -1) {
				ans += map[i][j];
			}
		}
	}

	cout << ans;
}

void input() {

	cin >> n >> m >> q;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int num;
			cin >> num;
			map[i].push_back(num);
		}
	}

	for (int i = 0; i < q; i++) {
		int x, d, k;
		cin >> x >>  d >> k;
		v.push_back({ x,d,k });
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
