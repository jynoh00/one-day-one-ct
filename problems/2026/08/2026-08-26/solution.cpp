#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    if (progresses.empty()) {
        return answer;
    }

    int releaseDay = (100 - progresses[0] + speeds[0] - 1) / speeds[0];
    int count = 1;

    for (int i = 1; i < progresses.size(); ++i) {
        int completionDay = (100 - progresses[i] + speeds[i] - 1) / speeds[i];

        if (completionDay <= releaseDay) {
            count++;
            continue;
        }
        answer.push_back(count);
        releaseDay = completionDay;
        count = 1;
    }

    answer.push_back(count);

    return answer;
}