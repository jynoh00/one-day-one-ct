#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    
    map<int, int> m;
    for (int i : tangerine) {
        m[i] = m[i] + 1; // 개수 추가
    }
    
    vector<pair<int, int>> vec;
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        vec.emplace_back(make_pair(iter->first, iter->second));
    }
    
    sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // 내림차순
    });
    
    int ggg = 0; // 담은 귤
    for (pair<int, int> p : vec) {
        ggg += p.second;
        answer++;
        if (ggg >= k) break;
    }
    
    return answer;
}