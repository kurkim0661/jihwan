#include<iostream>
#include<queue>

using namespace std;

struct RNG {
	unsigned signal;
        //문제 입력에 따라 초기값을 1983 적용
	RNG() : signal(1983u) {}
	unsigned next() {

                //현재 신호를 10000으로 나눈 나머지에 1을 더해서 출력신호 생성
		unsigned out = signal % 10000u + 1;

                //다음 신호 생성
		signal = (signal * 214013u +2531011u);
		return out;
	}
};

int solution(unsigned N, unsigned K) {
	int answer = 0;
	unsigned rangeSum = 0;
	RNG rng;
	queue<int> q;
        //K만큼 순회
	for (int i = 0; i < K; i++) {

                //1. 신호 생성
		auto signal = rng.next();

                //2. 부분합 누적
		rangeSum += signal;

                //3. 큐에도 신호 저장
		q.push(signal);
                //4. 현재 부분합이 N보다 크다면 다음을 반복
		while (rangeSum > N) {

                        //현재 큐의 가장 첫 신호를 부분합에서 제거
			rangeSum -= q.front();

                        //큐에서 제거
			q.pop();
		}
                //5. 4번을 거친 후, 현재 부분합이 N과 같다면 개수 세어줌
		if (rangeSum == N)
			answer += 1;
	}
	
	return answer;
}


int main() {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		unsigned N, K;
		cin >> N >> K;
		cout << solution(N, K) << endl;
	}
	return 0;
}
