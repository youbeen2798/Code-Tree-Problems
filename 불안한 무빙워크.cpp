#include <iostream>
#include <deque>

using namespace std;

int n; //������ũ ����
int k; //���� ����

deque<pair<bool, int>> nums;

void moving_walk_rotate() {
	//������ũ�� �� ĭ ȸ���Ѵ�.

	pair<int, int> back = nums.back();
	nums.pop_back(); //������ũ �� pop
	nums.push_front(back); //������ũ ������ �� ĭ ȸ��
}

void all_people_move() {
	//���� ���� ������ũ�� �ö� �������
	//������ũ�� ȸ���ϴ� �������� �� ĭ �̵��� �� ������
	//�̵��Ѵ�.

	//�� ��ĭ�� ����� �ְ�, �� ùĭ�� ����� ����, �� ùĭ�� �������� 0 
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
	//1��ĭ�� ����� ���� �������� 0�� �ƴ϶�� 
	//����� �Ѹ� �� �ø���.

	if (!nums[0].first && nums[0].second > 0) {
		nums[0].first = true;
		nums[0].second -= 1;
	}
}

bool check_finish() {
	//�������� 0�� ĭ�� k�� �̻��̶�� ���� ����

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
	//n�� ĭ ��ġ�� ����� ��ġ�ϸ� �� ��� ������.

	if (nums[n - 1].first) {
		nums[n - 1].first = false;
	}
}
void one_test() {
	//������ �׽�Ʈ 1ȸ

	moving_walk_rotate(); //1. ������ũ�� �� ĭ ȸ���Ѵ�.
	check_again();

	all_people_move(); //2. ������� �̵��Ѵ�.
	check_again();

	three();
	check_again();

}
void solution() {

	for (int i = 0;; i++) {
		one_test();

		if (check_finish()) {
			//������ �� �ִٸ�
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
