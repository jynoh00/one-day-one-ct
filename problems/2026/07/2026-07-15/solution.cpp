#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void init();
bool solve(vector<string> phone_book);
bool solve_2(vector<string> phone_book);
bool solve_3(vector<string> phone_book);
bool my_compare(string left, string right);

bool solution(vector<string> phone_book) {
    init();
    
    // solve, solve_2에서 사용
    sort(phone_book.begin(), phone_book.end());
    
    // bool answer = solve(phone_book); // 실패 -> [12333 124] 이렇게 정렬됨
    bool answer = solve_2(phone_book); // 사전순 정렬 적용
    // bool answer = solve_3(phone_book); // X

    return answer;
}

void init() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
}

// 두 번째 풀이 (성공)
bool solve_2(vector<string> phone_book) {
    if (phone_book.size() == 1) return true;

    for (int i = 0; i < phone_book.size(); i++) {
        if (i == phone_book.size() - 1) continue;
        if (!my_compare(phone_book[i], phone_book[i + 1])) return false;
    }

    return true;
}

// 세 번째 풀이 (x)
bool solve_3(vector<string> phone_book) {
    if (phone_book.size() == 1) return true;

    vector<long long> num_vec;
    for (string s : phone_book) num_vec.emplace_back(stoll(s));

    sort(num_vec.begin(), num_vec.end());

    int left = 0, right = 1;
    while (left <= right) {
        if (right == (phone_book.size() - 1)) {
            return my_compare(phone_book[left], phone_book[right]);
        }

        // if (phone_book[left])
    }
}


// 접두어면 false 반환
bool my_compare(string left, string right) {
    for (int i = 0; i < left.size(); i++) {
        if (left[i] != right[i]) return true;
    }
    
    return false;
}

// 첫 풀이 (실패)
bool solve(vector<string> phone_book) {
    // edge_case
    if (phone_book.size() == 1) return true;
    
    // two-pointer
    int left = 0, right = 1;
    while (left <= right) {
        if ((phone_book.size() - 1) == right) {
            return my_compare(phone_book[left], phone_book[right]);
        }
        
        // left랑 right길이 똑같으면 x
        if (phone_book[left].size() == phone_book[right].size()) {
            right++;
            continue;
        }
        
        // right길이가 더 긴 경우
        if (!my_compare(phone_book[left], phone_book[right])) return false;
        
        left++;
    }
}