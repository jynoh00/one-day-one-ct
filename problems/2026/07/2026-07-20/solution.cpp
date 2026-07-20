#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> targets) {
    int answer = 1;
    pair<int, int> range;

    sort(targets.begin(), targets.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return a[1] > b[1];
        }
    );

    range.first = targets[0][0];
    range.second = targets[0][1];

    for (int i = 1; i < targets.size(); i++) {
        int tmpLeft = targets[i][0];
        int tmpRight = targets[i][1];
        
        if (range.first < tmpRight) { // 중복 킬 가능 영역, 마지막 원소가 아닌 경우
            range.second = tmpRight;
            range.first = range.first <= tmpLeft ? tmpLeft : range.first;

            continue;
        }

        answer++;
        range.first = tmpLeft;
        range.second = tmpRight;
    }
    
    
    return answer; 
}