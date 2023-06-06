#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n; //�巡�� Ŀ���� ����
vector<pair<int, int>> v_collections; //�巡�� ���� ����

struct info {
	int x; //���� �� ��
	int y; //���� �� ��
	int d; //���� ����
	int g; //����
};

vector<info> input_v;

void make_dragon(info i) {


	vector<pair<int, int>> v; //�巡�� ���� ����

	int x = i.x; //������ ��
	int y = i.y; //������ ��
	int d = i.d; //���۹���
	int g = i.g; //����

	v.push_back({ x,y });

	if (d == 0) { //������
		v.push_back({ x, y + 1 });
	}
	else if (d == 1) { //����
		v.push_back({ x - 1, y });
	}
	else if (d == 2) { //����
		v.push_back({ x, y - 1 });
	}
	else { //�Ʒ���
		v.push_back({ x + 1, y });
	}

	for (int i = 0; i < g; i++) {
		//������ ����

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
		int x, y, d, g; //(x,y): ������, d: ���� ����, g: ����
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