// 연속 부분 수열 합의 개수

#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(vector<int> elements) {
    set<int> answer;
    
    for (int i = 0; i < elements.size(); i++) {
        int tmp_sum = elements[i];
        answer.insert(tmp_sum);
        
        for (int j = 1; j <= elements.size() - 1; j++) {
            int idx = i + j;
            if ((i + j) >= elements.size()) {
                idx -= elements.size();
            }
            
            tmp_sum += elements[idx];
            answer.insert(tmp_sum);
        }
        
    }
    
    return answer.size();
}