#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n; //드래곤 커브의 개수
vector<pair<int, int>> v_collections; //드래곤 점들 모음

struct info {
	int x; //시작 점 행
	int y; //시작 점 열
	int d; //시작 방향
	int g; //차수
};

vector<info> input_v;

void make_dragon(info i) {


	vector<pair<int, int>> v; //드래곤 점들 모음

	int x = i.x; //시작점 행
	int y = i.y; //시작점 열
	int d = i.d; //시작방향
	int g = i.g; //차수

	v.push_back({ x,y });

	if (d == 0) { //오른쪽
		v.push_back({ x, y + 1 });
	}
	else if (d == 1) { //위쪽
		v.push_back({ x - 1, y });
	}
	else if (d == 2) { //왼쪽
		v.push_back({ x, y - 1 });
	}
	else { //아래쪽
		v.push_back({ x + 1, y });
	}

	for (int i = 0; i < g; i++) {
		//차수번 동안

		int size = v.size();

		int end_point_x = v[size - 1].first; //1
		int end_point_y = v[size - 1].second; //3

		for (int j = size - 2; j >= 0; j--) {
			int x_diff = v[j].first - end_point_x; //1
			int y_diff = v[j].second - end_point_y; //0
			int new_x = end_point_x + y_diff; //1
			int new_y = end_point_y - x_diff; //2

			v.push_back({ new_x, new_y });
		}

		v.erase(unique(v.begin(), v.end()), v.end());
	}

	for (int i = 0; i < v.size(); i++) {
		v_collections.push_back(v[i]);
	}
}

void check_rectangle() {

	set<pair<int, int>> s;

	for (int i = 0; i < v_collections.size(); i++) {
		int x = v_collections[i].first;
		int y = v_collections[i].second;

		s.insert({ x,y });
	}

	int ans = 0;

	for (auto tmp : s) {
		int x = tmp.first;
		int y = tmp.second;

		if (s.find({ x,y + 1 }) != s.end() && s.find({ x + 1, y }) != s.end() && s.find({ x + 1, y + 1 }) != s.end()) {
			ans++;
		}
	}

	cout << ans;

}
void solution() {

	for (int i = 0; i < input_v.size(); i++) {
		make_dragon(input_v[i]);
	}

	check_rectangle();


}

void input() {

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x, y, d, g; //(x,y): 시작점, d: 시작 방향, g: 차수
		cin >> x >> y >> d >> g;
		input_v.push_back({ x,y,d,g });
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}