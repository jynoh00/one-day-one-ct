#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<pair<int, int>> answers;
    vector<int> answer;
    
    // edge
    for (int i = 0; i < sequence.size(); i++) {
        if (sequence[i] == k) {
            answer.emplace_back(i);
            answer.emplace_back(i);
            return answer;
        }
    }
    
    int sum = sequence[0], startIdx = 0, endIdx = 1;
    while ((endIdx <= sequence.size()) && (startIdx <= endIdx)) {
        if (sum > k) {
            sum -= sequence[startIdx++];
            continue;
        }
        
        if (sum == k) {
            answers.emplace_back(make_pair(startIdx, endIdx - 1));
            sum -= sequence[startIdx++];
            sum += sequence[endIdx++];
            continue;
        }
        
        // sum < k
        sum += sequence[endIdx++];
    }
    
    // 마지막 원소가 부분 수열에 들어가는 경우
    if (sum == k) {
        answers.emplace_back(make_pair(startIdx, endIdx - 1));
    }

    // 정렬 pair.second - pair.first -> pair.first
    sort(answers.begin(), answers.end(), [] (const pair<int, int>& a, const pair<int, int>& b) {
        int diffA = a.second - a.first;
        int diffB = b.second - b.first;

        if (diffA == diffB) {
            return a.first < b.first;
        }

        return diffA < diffB;
    });

    answer.emplace_back(answers[0].first);
    answer.emplace_back(answers[0].second);

    return answer;
}