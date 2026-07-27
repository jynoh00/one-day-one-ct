#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

int solution(string message, vector<vector<int>> spoiler_ranges) {
    int answer = 0;
    vector<string> words;
    
    stringstream ss(message);
    
    // init
    map<int, bool> isSpoilerIdx;
    for (vector<int> range : spoiler_ranges) {
        for (int i = range[0]; i <= range[1]; i++) {
            isSpoilerIdx[i] = true;
        }
    }
    
    map<string, bool> default_words;
    map<string, bool> special_words;
    
    int now_idx = message[0] == ' ' ? 1 : 0;
    string tmp_word;
    while (ss >> tmp_word) {
        words.emplace_back(tmp_word);
        int start_idx = now_idx;
        int end_idx = now_idx + (tmp_word.size() - 1);
        
        bool isSpoilerWord = false;
        for (int i = start_idx; i <= end_idx; i++) {
            if (isSpoilerIdx[i]) {
                isSpoilerWord = true;
                break;
            }
        }
        
        if (isSpoilerWord) {
            // 스포 방지 단어 처리
            special_words[tmp_word] = true;
            
            // idx 증가
            now_idx += tmp_word.size() + 1;
            continue;
        }
        // 일반 단어 처리
        default_words[tmp_word] = true;
        
        // idx 증가 <- 공백 1칸 (공백은 연속해서 등장하지 않습니다)
        now_idx += tmp_word.size() + 1;
    }
    
    // 카운트 과정
    // 일반 단어인지 확인 후 카운트 제거    
    map<string, bool> already_count_special;
    for (string tmp_word : words) {
        if (special_words[tmp_word] && !default_words[tmp_word] && !already_count_special[tmp_word]) {
            already_count_special[tmp_word] = true;
            
            answer++;
        }
    }
    
    return answer;
}