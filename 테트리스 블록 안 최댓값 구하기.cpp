#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> v[19] = {
	{{0,0},{0,1},{0,2}, {0,3}},
	{{0,0}, {1,0}, {2,0},{3,0}},
	{{0,0}, {0,1}, {1,0}, {1,1}},
	{{0,0}, {1,0}, {2,0}, {2,1}},
	{{0,0}, {0,1}, {0,2}, {-1,2}},
	{{0,0}, {0,1}, {1,1}, {2,1}},
	{{0,0}, {1,0}, {0,1}, {0,2}},
	{{0,0}, {0,1}, {-1,1}, {-2,1}},
	{{0,0}, {1,0}, {1,1}, {1,2}},
	{{0,0}, {0,1}, {1,0}, {2,0}},
	{{0,0}, {0,1}, {0,2}, {1,2}},
	{{0,0}, {1,0}, {1,1}, {2,1}},
	{{0,0}, {0,1}, {-1,1}, {1,0}},
	{{0,0}, {0,1}, {-1,1}, {-1,2}},
	{{0,0}, {0,1}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {1,1}, {2,0}},
	{{0,0}, {0,1}, {0,2}, {-1,1}},
	{{0,0}, {0,1}, {-1,1}, {1,1}},
	{{0,0}, {0,1}, {0,2}, {1,1}}
};

int n; //가로크기
int m; //세로크기
int map[201][201]; 
int ans = 0;

bool inrange(int x, int y) {
	if (0 <= x && x < n && 0 <= y && y < m) {
		return true;
	}
	return false;
}

void start_left(int x, int y) {
	//(x,y)부터 시작한다.

	for (int i = 0; i < 19; i++) {

		int tmp_num = 0;
		bool possible = true;
		for (int j = 0; j < 4; j++) {
			int nx = x + v[i][j].first;
			int ny = y + v[i][j].second;

			if (!inrange(nx, ny)) {
				possible = false;
				break;
			}

			tmp_num += map[nx][ny];
		}
		if (possible) {
			ans = max(ans, tmp_num);
		}

	}
}
void solution() {


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			start_left(i, j);
		}
	}

	cout << ans << "\n"; 

}
void input() {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
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