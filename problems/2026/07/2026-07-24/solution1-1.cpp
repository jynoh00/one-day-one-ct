#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}

int solution(vector<vector<int>> signals) {
    long long limit = 1;

    for (const auto& signal : signals) {
        long long period = signal[0] + signal[1] + signal[2];
        limit = lcm(limit, period);
    }

    for (long long time = 1; time <= limit; time++) {
        bool allGreen = true;

        for (const auto& signal : signals) {
            int period = signal[0] + signal[1] + signal[2];
            int index = (time - 1) % period;

            // 초록불 구간이 아니면
            if (index < signal[0] ||
                index >= signal[0] + signal[1]) {
                allGreen = false;
                break;
            }
        }

        if (allGreen) {
            return time;
        }
    }

    return -1;
}