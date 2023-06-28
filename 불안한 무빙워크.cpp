#include <iostream>
#include <deque>

using namespace std;

int n; //무빙워크 길이
int k; //핀의 개수

deque<pair<bool, int>> nums;

void moving_walk_rotate() {
	//무빙워크가 한 칸 회전한다.

	pair<int, int> back = nums.back();
	nums.pop_back(); //무빙워크 뒤 pop
	nums.push_front(back); //무빙워크 앞으로 한 칸 회전
}

void all_people_move() {
	//가장 먼저 무빙워크에 올라간 사람부터
	//무빙워크가 회전하는 방향으로 한 칸 이동할 수 있으면
	//이동한다.

	//맨 뒷칸에 사람이 있고, 맨 첫칸에 사람이 없고, 맨 첫칸에 안정성이 0 
	pair<bool, int> back = nums[nums.size() - 1];

	if (back.first && !nums[0].first && back.second > 0) {
		nums[nums.size() - 1].first = false;
		nums[0].first = true;
		nums[nums.size() - 1].second -= 1;
	}

	for (int i = nums.size() - 2; i >= 0; i--) {
		pair<bool, int> before = nums[i];
		pair<bool, int> after = nums[i + 1];

		if (before.first && !after.first && after.second > 0) {
			nums[i].first = false;
			nums[i + 1].first = true;
			nums[i + 1].second -= 1;
		}
	}

}

void three() {
	//1번칸에 사람이 없고 안정성이 0이 아니라면 
	//사람을 한명 더 올린다.

	if (!nums[0].first && nums[0].second > 0) {
		nums[0].first = true;
		nums[0].second -= 1;
	}
}

bool check_finish() {
	//안정성이 0인 칸이 k개 이상이라면 과정 종료

	int size = nums.size();
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (nums[i].second == 0) {
			cnt++;
		}
	}

	if (cnt >= k) {
		return true;
	}

	return false;

}

void check_again() {
	//n번 칸 위치에 사람이 위치하면 그 즉시 내린다.

	if (nums[n - 1].first) {
		nums[n - 1].first = false;
	}
}
void one_test() {
	//안정성 테스트 1회

	moving_walk_rotate(); //1. 무빙워크가 한 칸 회전한다.
	check_again();

	all_people_move(); //2. 사람들이 이동한다.
	check_again();

	three();
	check_again();

}
void solution() {

	for (int i = 0;; i++) {
		one_test();

		if (check_finish()) {
			//종료할 수 있다면
			cout << i + 1;
			break;
		}
	}

}

void input() {

	cin >> n >> k;

	for (int i = 1; i <= 2 * n; i++) {
		int num;
		cin >> num;
		nums.push_back({ false, num });
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
