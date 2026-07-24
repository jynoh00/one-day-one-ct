#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}

int solution(vector<vector<int>> signals) {
    vector<vector<bool>> states;
    
    // init
    for (vector<int> vec : signals) {
        vector<bool> tmp;
        for (int i = 0; i < vec[0]; i++) {
            tmp.emplace_back(false);
        }
        
        for (int j = 0; j < vec[1]; j++) {
            tmp.emplace_back(true);
        }
        
        for (int k = 0; k < vec[2]; k++) {
            tmp.emplace_back(false);
        }
        states.emplace_back(tmp);
    }
    
    // 길이 순 정렬 -> 내림차순
    sort(states.begin(), states.end(), [](const vector<bool>& a, const vector<bool>& b) {
        return a.size() > b.size();
    });
    
    vector<vector<bool>> ans_vec;
    

    bool diffLength = false;
    int counter = 0;
    vector<bool> before;
    for (vector<bool> now : states) {
        counter++;
        
        if (counter == 1) {
            before = now;
            
            continue;
        }
        
        // 길이 동일 & 연산
        if (before.size() == now.size()) {
            for (int i = 0; i < before.size(); i++) {
                before[i] = before[i] & now[i];
            }
            
            // 마지막 원소 엣지 케이스
            if (counter == states.size()) {
                ans_vec.emplace_back(before);
            }
            
            continue;
        }
        
        // 길이 불일치 => now가 더 작다.
        ans_vec.emplace_back(before);
        before.clear();
        before = now;
        
        // 마지막 원소 엣지 케이스
        if (counter == states.size()) {
            ans_vec.emplace_back(now);
            continue;
        }
    }
    
    vector<bool> real_ans_vec;

    for (int i = 0; i < ans_vec.size(); i++) {
        if (i == 0) {
            real_ans_vec = ans_vec[0];
            continue;
        }
        
        int a_size = real_ans_vec.size();
        int b_size = ans_vec[i].size();
        
        int lcmNum = lcm(a_size, b_size);
        
        vector<bool> aBack(real_ans_vec);
        vector<bool> bBack(ans_vec[i]);
        
        for (int j = 1; j < (lcmNum / a_size); j++) real_ans_vec.insert(real_ans_vec.end(), aBack.begin(), aBack.end());
        
        for (int j = 1; j < (lcmNum / b_size); j++) ans_vec[i].insert(ans_vec[i].end(), bBack.begin(), bBack.end());
        
        for (int j = 0; j < lcmNum; j++) real_ans_vec[j] = real_ans_vec[j] & ans_vec[i][j];
    }
    
    for (int i = 0; i < real_ans_vec.size(); i++) {
        if (real_ans_vec[i]) return (i + 1);
    }
    
    return -1;
}