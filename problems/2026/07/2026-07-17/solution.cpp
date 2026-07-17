#include <iostream>
#include <stdio.h>

#define MAX 4
#define endl "\n"

using namespace std;

pair<int, int> fishes[17]; 
pair<int, int> map[MAX][MAX];
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
int x_pos = 0, y_pos = 0;
int ans = 0;

int max(int a, int b){ return a > b ? a : b; }
void input(); void solution(int sx, int sy, int sd, int sum);
void fish_move(int idx);
vector<int> calcu_distance(int sx, int sy, int sd);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    ans += map[0][0].first; 
    fishes[map[0][0].first].first = -1;
    map[0][0].first = -1;
    

    solution(x_pos, y_pos, map[0][0].second, ans);

    cout << ans << endl;

    return 0;
}

void input(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            int a, b;
            cin >> a >> b;
            map[i][j] = make_pair(a, b);
            fishes[a] = make_pair(i, j);
        }
    }

}
void solution(int sx, int sy, int sd, int sum){
    for (int i = 1; i <= 16; i++){
        fish_move(i);
    }

    vector<int> calcu_distances = calcu_distance(sx, sy, sd);
    if (calcu_distances.size() == 0){ // 이동 불가
        ans = max(ans, sum);
        return;
    }

    for (int i = 0; i < calcu_distances.size(); i++){
        // 현재 위치 빈칸으로
        map[sx][sy].first = 0;
        map[sx][sy].second = 0;
        
        int tmp_x = sx, tmp_y = sy;
        int tmp_d = sd;

        int nx = sx + dx[sd]*calcu_distances[i];
        int ny = sy + dy[sd]*calcu_distances[i];

        int fish_tmp_i = map[nx][ny].first;
        int fish_tmp_d = map[nx][ny].second;

        int nd = fish_tmp_d;

        fishes[fish_tmp_i].first = -1; // 죽은 물고기
        fishes[fish_tmp_i].second = -1;

        sum += fish_tmp_i;
        map[nx][ny].first = -1;
        
        solution(nx, ny, nd, sum);
        
        sum -= fish_tmp_i;
        map[nx][ny].first = fish_tmp_i;
        
        fishes[fish_tmp_i].first = nx;
        fishes[fish_tmp_i].second = ny;        
    }
}

void fish_move(int fish){
    if (fishes[fish].first == -1) return; // 죽은 물고기 : 죽은 물고기 좌표는 -1, -1로 저장

    int tmp_x = fishes[fish].first, tmp_y = fishes[fish].second;
    int tmp_d = map[tmp_x][tmp_y].second;
    for (int i = 0; i < 7; i++){ // +0, +1, +2, +3, +4, +5, +6
        int nd = (tmp_d + i)%8;
        int nx = tmp_x + dx[nd], ny = tmp_y + dy[nd];

        if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX){ // 00 ~ 33
            if (map[nx][ny].first == -1){ // 상어면
                continue; // 다음 방향
            }else if (map[nx][ny].first == 0){ //빈칸
                map[tmp_x][tmp_y].first = 0;
                map[tmp_x][tmp_y].second = 0; // 빈칸으로
                map[nx][ny].first = fish;
                map[nx][ny].second = nd;
                fishes[fish].first = nx;
                fishes[fish].second = ny;

                return;
            }else{ // 물고기 교체
                map[tmp_x][tmp_y].first = map[nx][ny].first;
                map[tmp_x][tmp_y].second = map[nx][ny].second;
                fishes[map[nx][ny].first].first = tmp_x;
                fishes[map[nx][ny].first].second = tmp_y;

                map[nx][ny].first = fish;
                map[nx][ny].second = nd;
                fishes[fish].first = nx;
                fishes[fish].second = ny;

                return;
            }
        }
    }
    
    return;
}

vector<int> calcu_distance(int sx, int sy, int sd){
    vector<int> ans_v;
    int direction = sd; // 상어 방향

    for (int i = 1; i <= 3; i++){
        int nx = sx + dx[direction]*i, ny = sy + dy[direction]*i;

        if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX){ // 맵 내부
            if (map[nx][ny].first > 0) ans_v.emplace_back(i);
        }
    }

    return ans_v;
}