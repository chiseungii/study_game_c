#include <iostream>
#include <ctime>
using namespace std;

#define ERASE 125

int main() {
	srand((unsigned int)time(0));

	// AI 빙고판 준비
	int AI_number[25];
	for (int i = 0; i < 25; i++)
		AI_number[i] = i + 1;

	int tmp, index1, index2;
	for (int i = 0; i < 100; i++) {
		index1 = rand() % 25;
		index2 = rand() % 25;

		tmp = AI_number[index1];
		AI_number[index1] = AI_number[index2];
		AI_number[index2] = tmp;
	}

	// user 빙고판 준비
	int user_number[25];
	for (int i = 0; i < 25; i++)
		user_number[i] = i + 1;

	for (int i = 0; i < 100; i++) {
		index1 = rand() % 25;
		index2 = rand() % 25;

		tmp = user_number[index1];
		user_number[index1] = user_number[index2];
		user_number[index2] = tmp;
	}

	// 시작 알림
	cout << "게임을 시작하려면 Enter를 누르세요.";
	cin.get();

	int AI_bingo = 0, user_bingo = 0;	// 빙고 개수 카운트
	int cnt_AI_h, cnt_AI_w, cnt_user_h, cnt_user_w;		// 빙고 체크용 숫자 카운트
	bool check[26] = { false, };		// 숫자 체크용. 썼으면 true, 안 썼으면 false
	while (1) {
		system("cls");

		// ---------- AI 턴
		// 숫자 고르기
		int AI_choice = rand() % 25 + 1;
		while (check[AI_choice]) AI_choice = rand() % 25 + 1;
		check[AI_choice] = true;

		// 양 플레이어 빙고판에 표시
		for (int i = 0; i < 25; i++)
			if (AI_number[i] == AI_choice) {
				AI_number[i] = ERASE;
				break;
			}
		for(int i=0;i<25;i++)
			if (user_number[i] == AI_choice) {
				user_number[i] = ERASE;
				break;
			}

		// 양 플레이어 빙고 개수 카운트
		AI_bingo = 0; user_bingo = 0;
		for (int i = 0; i < 5; i++) {
			cnt_AI_h = 0, cnt_AI_w = 0, cnt_user_h = 0, cnt_user_w = 0;
			for (int j = 0; j < 5; j++) {
				if (AI_number[i * 5 + j] == ERASE) cnt_AI_w++;			// AI 가로 체크
				if (user_number[i * 5 + j] == ERASE) cnt_user_w++;		// user 가로 체크
				if (AI_number[j * 5 + i] == ERASE) cnt_AI_h++;			// AI 세로 체크
				if (user_number[j * 5 + i] == ERASE) cnt_user_h++;		// user 세로 체크
			}

			if (cnt_AI_w == 5) AI_bingo++;
			if (cnt_AI_h == 5) AI_bingo++;
			if (cnt_user_w == 5) user_bingo++;
			if (cnt_user_h == 5) user_bingo++;
		}
		cnt_AI_h = 0; cnt_user_h = 0;
		for (int i = 0; i < 25; i += 6) {
			if (AI_number[i] == ERASE) cnt_AI_h++;		// AI \ 대각선 체크
			if (user_number[i] == ERASE)cnt_user_h++;	// user \ 대각선 체크
		}
		cnt_AI_w = 0; cnt_user_w = 0;
		for (int i = 4; i < 21; i += 4) {
			if (AI_number[i] == ERASE) cnt_AI_w++;		// AI / 대각선 체크
			if (user_number[i] == ERASE) cnt_user_w++;	// user / 대각선 체크
		}
		if (cnt_AI_w == 5) AI_bingo++;
		if (cnt_AI_h == 5) AI_bingo++;
		if (cnt_user_w == 5) user_bingo++;
		if (cnt_user_h == 5) user_bingo++;

		// 빙고판 출력
		cout << "---------- AI Bingo ----------\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
				cout << "*\t";
			cout << '\n';
		}
		cout << "\nAI choice " << AI_choice << ".\n";
		cout << "AI have " << AI_bingo << " bingo.\n";

		cout << "\n---------- USER Bingo ----------\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (user_number[i * 5 + j] == ERASE) cout << "*\t";
				else cout << user_number[i * 5 + j] << '\t';
			}
			cout << '\n';
		}
		cout << "\nUSER have " << user_bingo << " bingo.\n";

		// 승리 조건 확인
		if (AI_bingo >= 5) {
			cout << "\nAI WIN!!\n";
			break;
		}
		if (user_bingo >= 5) {
			cout << "\nUSER WIN!!\n";
			break;
		}

		// ---------- USER 턴
		cout << "\nPlease choice number >> ";

		// 숫자 입력
		int user_choice; cin >> user_choice;
		while (check[user_choice]) {
			cout << "Already choiced number >> ";
			cin >> user_choice;
		}
		check[user_choice] = true;
		if (user_choice == 0) break;		// 0 입력 시 종료

		// 양 플레이어 빙고판 표시
		for (int i = 0; i < 25; i++)
			if (AI_number[i] == user_choice) {
				AI_number[i] = ERASE;
				break;
			}
		for (int i = 0; i < 25; i++)
			if (user_number[i] == user_choice) {
				user_number[i] = ERASE;
				break;
			}

		// 양 플레이어 빙고 개수 카운트
		AI_bingo = 0; user_bingo = 0;
		for (int i = 0; i < 5; i++) {
			cnt_AI_h = 0, cnt_AI_w = 0, cnt_user_h = 0, cnt_user_w = 0;
			for (int j = 0; j < 5; j++) {
				if (AI_number[i * 5 + j] == ERASE) cnt_AI_w++;			// AI 가로 체크
				if (user_number[i * 5 + j] == ERASE) cnt_user_w++;		// user 가로 체크
				if (AI_number[j * 5 + i] == ERASE) cnt_AI_h++;			// AI 세로 체크
				if (user_number[j * 5 + i] == ERASE) cnt_user_h++;		// user 세로 체크
			}

			if (cnt_AI_w == 5) AI_bingo++;
			if (cnt_AI_h == 5) AI_bingo++;
			if (cnt_user_w == 5) user_bingo++;
			if (cnt_user_h == 5) user_bingo++;
		}
		cnt_AI_h = 0; cnt_user_h = 0;
		for (int i = 0; i < 25; i += 6) {
			if (AI_number[i] == ERASE) cnt_AI_h++;		// AI \ 대각선 체크
			if (user_number[i] == ERASE)cnt_user_h++;	// user \ 대각선 체크
		}
		cnt_AI_w = 0; cnt_user_w = 0;
		for (int i = 4; i < 21; i += 4) {
			if (AI_number[i] == ERASE) cnt_AI_w++;		// AI / 대각선 체크
			if (user_number[i] == ERASE) cnt_user_w++;	// user / 대각선 체크
		}
		if (cnt_AI_w == 5) AI_bingo++;
		if (cnt_AI_h == 5) AI_bingo++;
		if (cnt_user_w == 5) user_bingo++;
		if (cnt_user_h == 5) user_bingo++;

		system("cls");

		// 빙고판 출력
		cout << "---------- AI Bingo ----------\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
				cout << "*\t";
			cout << '\n';
		}
		cout << "\nAI choice " << AI_choice << ".\n";
		cout << "AI have " << AI_bingo << " bingo.\n";

		cout << "\n---------- USER Bingo ----------\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (user_number[i * 5 + j] == ERASE) cout << "*\t";
				else cout << user_number[i * 5 + j] << '\t';
			}
			cout << '\n';
		}
		cout << "\nUSER have " << user_bingo << " bingo.\n";

		// 승리 조건 확인
		if (AI_bingo >= 5) {
			cout << "\nAI WIN!!\n";
			break;
		}
		if (user_bingo >= 5) {
			cout << "\nUSER WIN!!\n";
			break;
		}

		// 다음 라운드 진행
		cin.ignore();
		cout << "\nPlease push ENTER to go to next round.";
		cin.get();
	}
}
