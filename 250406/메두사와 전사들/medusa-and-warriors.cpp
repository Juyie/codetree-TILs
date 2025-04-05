#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

bool visited[51][51];
// 상하좌우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
// 좌우상하
int dx2[4] = {0, 0, -1, 1};
int dy2[4] = {-1, 1, 0, 0};
int N = 0;

void killKnights(vector<tuple<int, int, bool>> &knights, int curr_r, int curr_c){
    for(auto iter = knights.begin(); iter != knights.end(); iter++){
        if(get<0>(*iter) == curr_r && get<1>(*iter) == curr_c){
            get<2>(*iter) = true;
        }
    }
}

void resetFreeze(vector<vector<pair<int, bool>>> &maps){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            maps[i][j].second = false;
        }
    }
}

int rewriteMap(vector<vector<pair<int, bool>>> &maps, vector<tuple<int, int, bool>> &knights, int curr_r, int curr_c, int dir){
    int freeze = 0;

    if(dir == 0){ // 상
        for(int i = curr_r - 1; i >= 0; i--){
            for(int j = 0; j < N; j++){
                if(j == curr_c){
                    maps[i][j].second = true;
                }
                else if(j < curr_c){
                    if((i + 1 == curr_r && j + 1 == curr_c) || maps[i + 1][j + 1].second){
                        maps[i][j].second = true;
                    }
                }
                else{
                    if((i + 1 == curr_r && j - 1 == curr_c) || maps[i + 1][j - 1].second){
                        maps[i][j].second = true;
                    }
                }
            }
        }
        sort(knights.begin(), knights.end(), [](const auto &a, const auto &b){
            return get<0>(a) > get<0>(b);
        });
        for(auto iter = knights.begin(); iter != knights.end(); iter++){
            if(maps[get<0>(*iter)][get<1>(*iter)].second && get<2>(*iter) == false){ // 살아있고 언 경우
                freeze++;
                for(int i = get<0>(*iter) - 1; i >= 0; i--){
                    for(int j = 0; j < N; j++){
                        if(j == get<1>(*iter)){
                            maps[i][j].second = false;
                        }
                        else if(j < get<1>(*iter) && get<1>(*iter) < curr_c){
                            if((i + 1 == get<0>(*iter) && j + 1 == get<1>(*iter)) || !maps[i + 1][j + 1].second){
                                maps[i][j].second = false;
                            }
                        }
                        else if(j > get<1>(*iter) && get<1>(*iter) > curr_c){
                            if((i + 1 == get<0>(*iter) && j - 1 == get<1>(*iter)) || !maps[i + 1][j - 1].second){
                                maps[i][j].second = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(dir == 1){ // 하
        for(int i = curr_r + 1; i < N; i++){
            for(int j = 0; j < N; j++){
                if(j == curr_c){
                    maps[i][j].second = true;
                }
                else if(j < curr_c){
                    if((i - 1 == curr_r && j + 1 == curr_c) || maps[i - 1][j + 1].second){
                        maps[i][j].second = true;
                    }
                }
                else{
                    if((i - 1 == curr_r && j - 1 == curr_c) || maps[i - 1][j - 1].second){
                        maps[i][j].second = true;
                    }
                }
            }
        }
        sort(knights.begin(), knights.end(), [](const auto &a, const auto &b){
            return get<0>(a) < get<0>(b);
        });
        for(auto iter = knights.begin(); iter != knights.end(); iter++){
            if(maps[get<0>(*iter)][get<1>(*iter)].second && get<2>(*iter) == false){
                freeze++;
                for(int i = get<0>(*iter) + 1; i < N; i++){
                    for(int j = 0; j < N; j++){
                        if(j == get<1>(*iter)){
                            maps[i][j].second = false;
                        }
                        else if(j < get<1>(*iter) && get<1>(*iter) < curr_c){
                            if((i - 1 == get<0>(*iter) && j + 1 == get<1>(*iter)) || !maps[i - 1][j + 1].second){
                                maps[i][j].second = false;
                            }
                        }
                        else if(j > get<1>(*iter) && get<1>(*iter) > curr_c) {
                            if((i - 1 == get<0>(*iter) && j - 1 == get<1>(*iter)) || !maps[i - 1][j - 1].second){
                                maps[i][j].second = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(dir == 2){ // 좌
        for(int j = curr_c - 1; j >= 0; j--){
            for(int i = 0; i < N; i++){
                if(i == curr_r){
                    maps[i][j].second = true;
                }
                else if(i < curr_r){
                    if((i + 1 == curr_r && j + 1 == curr_c) || maps[i + 1][j + 1].second){
                        maps[i][j].second = true;
                    }
                }
                else{
                    if((i - 1 == curr_r && j + 1 == curr_c) || maps[i - 1][j + 1].second){
                        maps[i][j].second = true;
                    }
                }
            }
        }
        sort(knights.begin(), knights.end(), [](const auto &a, const auto &b){
            return get<1>(a) > get<1>(b);
        });
        for(auto iter = knights.begin(); iter != knights.end(); iter++){
            if(maps[get<0>(*iter)][get<1>(*iter)].second && get<2>(*iter) == false){
                freeze++;
                for(int j = get<1>(*iter) - 1; j >= 0; j--){
                    for(int i = 0; i < N; i++){
                        if(i == get<0>(*iter)){
                            maps[i][j].second = false;
                        }
                        else if(i < get<0>(*iter) && get<0>(*iter) < curr_r){
                            if((i + 1 == get<0>(*iter) && j + 1 == get<1>(*iter)) || !maps[i + 1][j + 1].second){
                                maps[i][j].second = false;
                            }
                        }
                        else if(i > get<0>(*iter) && get<0>(*iter) > curr_r) {
                            if((i - 1 == get<0>(*iter) && j + 1 == get<1>(*iter)) || !maps[i - 1][j + 1].second){
                                maps[i][j].second = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else{ // 우
        for(int j = curr_c + 1; j < N; j++){
            for(int i = 0; i < N; i++){
                if(i == curr_r){
                    maps[i][j].second = true;
                }
                else if(i < curr_r){
                    if((i + 1 == curr_r && j - 1 == curr_c) || maps[i + 1][j - 1].second){
                        maps[i][j].second = true;
                    }
                }
                else{
                    if((i - 1 == curr_r && j - 1 == curr_c) || maps[i - 1][j - 1].second){
                        maps[i][j].second = true;
                    }
                }
            }
        }
        sort(knights.begin(), knights.end(), [](const auto &a, const auto &b){
            return get<1>(a) < get<1>(b);
        });
        for(auto iter = knights.begin(); iter != knights.end(); iter++){
            if(maps[get<0>(*iter)][get<1>(*iter)].second && get<2>(*iter) == false){
                freeze++;
                for(int j = get<1>(*iter) + 1; j < N; j++){
                    for(int i = 0; i < N; i++){
                        if(i == get<0>(*iter)){
                            maps[i][j].second = false;
                        }
                        else if(i < get<0>(*iter) && get<0>(*iter) < curr_r){
                            if((i + 1 == get<0>(*iter) && j - 1 == get<1>(*iter)) || !maps[i + 1][j - 1].second){
                                maps[i][j].second = false;
                            }
                        }
                        else if(i > get<0>(*iter) && get<0>(*iter) > curr_r) {
                            if((i - 1 == get<0>(*iter) && j - 1 == get<1>(*iter)) || !maps[i - 1][j - 1].second){
                                maps[i][j].second = false;
                            }
                        }
                    }
                }
            }
        }
    }
    return freeze;
}

int calcFreeze(vector<vector<pair<int, bool>>> &maps, vector<tuple<int, int, bool>> &knights, int curr_r, int curr_c){
    int dir = 0;
    int freeze = 0;
    int max_freeze = 0;
    vector<vector<pair<int, bool>>> temp_maps = maps;
    vector<tuple<int, int, bool>> temp_knights = knights;

    resetFreeze(maps);
    // 메두사 입장에서 걸리는 전사 수 세기, 가장 많은 방향 찾기
    // 상
    max_freeze = rewriteMap(temp_maps, temp_knights, curr_r, curr_c, 0);
    // 하
    temp_maps = maps;
    temp_knights = knights;
    freeze = rewriteMap(temp_maps, temp_knights, curr_r, curr_c, 1);
    if(freeze > max_freeze){
        max_freeze = freeze;
        dir = 1;
    }
    // 좌
    temp_maps = maps;
    temp_knights = knights;
    freeze = rewriteMap(temp_maps, temp_knights, curr_r, curr_c, 2);
    if(freeze > max_freeze){
        max_freeze = freeze;
        dir = 2;
    }
    // 우
    temp_maps = maps;
    temp_knights = knights;
    freeze = rewriteMap(temp_maps, temp_knights, curr_r, curr_c, 3);
    if(freeze > max_freeze){
        max_freeze = freeze;
        dir = 3;
    }

    // 가장 많은 방향으로 확정
    rewriteMap(maps, knights, curr_r, curr_c, dir);
    return max_freeze;
}

pair<int, int> moveKnights(vector<vector<pair<int, bool>>> &maps, vector<tuple<int, int, bool>> &knights, int curr_r, int curr_c, int n){
    int movement = 0;
    int attack = 0;

    for (auto iter = knights.begin(); iter != knights.end(); iter++){
        if(maps[get<0>(*iter)][get<1>(*iter)].second == false && !get<2>(*iter)){ // 살아 있는 굳지 않은 애들만 이동
            // first movement 상하좌우
            for(int i = 0; i < 4; i++){ 
                int x = get<0>(*iter) + dx[i];
                int y = get<1>(*iter) + dy[i];
                if(x >= 0 && x < n && y >= 0 && y < n){
                    if(abs(get<0>(*iter) - curr_r) + abs(get<1>(*iter) - curr_c) > abs(x - curr_r) + abs(y - curr_c) && maps[x][y].second == false){
                        get<0>(*iter) = x;
                        get<1>(*iter) = y;
                        movement++;
                        if(x == curr_r && y == curr_c){
                            attack++;
                            get<2>(*iter) = true;
                        }
                        break;
                    }
                }
            }
            // second movement 좌우상하
            for(int i = 0; i < 4; i++){ 
                int x = get<0>(*iter) + dx2[i];
                int y = get<1>(*iter) + dy2[i];
                if(x >= 0 && x < n && y >= 0 && y < n){
                    if(abs(get<0>(*iter) - curr_r) + abs(get<1>(*iter) - curr_c) > abs(x - curr_r) + abs(y - curr_c) && maps[x][y].second == false){
                        get<0>(*iter) = x;
                        get<1>(*iter) = y;
                        movement++;
                        if(x == curr_r && y == curr_c){
                            attack++;
                            get<2>(*iter) = true;
                        }
                        break;
                    }
                }
            }
        }
    }

    pair<int, int> output = make_pair(movement, attack);
    return output;
}

void bfs(vector<vector<pair<int, bool>>> &maps, vector<tuple<int, int, bool>> &knights, int curr_r, int curr_c, int er, int ec, int n, vector<tuple<int, int, int>> &answers, vector<pair<int, int>> &route) {
    fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
    visited[curr_r][curr_c] = true;
    queue<pair<int, int>> bq;
    bq.push({curr_r, curr_c});

    pair<int, int> parent[51][51];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            parent[i][j] = {-1, -1};

    bool found = false;
    while (!bq.empty()) {
        auto [x, y] = bq.front(); bq.pop();
        if (x == er && y == ec) {
            found = true;
            break;
        }
        for (int i = 0; i < 4; ++i) {
            int r = x + dx[i], c = y + dy[i];
            if (r >= 0 && r < n && c >= 0 && c < n && !visited[r][c] && maps[r][c].first == 0) {
                visited[r][c] = true;
                bq.push({r, c});
                parent[r][c] = {x, y};
            }
        }
    }

    if (!found) return;

    vector<pair<int, int>> reversed;
    pair<int, int> curr = {er, ec};
    while (curr != make_pair(curr_r, curr_c)) {
        reversed.push_back(curr);
        curr = parent[curr.first][curr.second];
    }
    reversed.push_back({curr_r, curr_c});
    reverse(reversed.begin(), reversed.end());
    route = reversed;

    for (size_t i = 1; i < route.size() - 1; ++i) {
        int x = route[i].first;
        int y = route[i].second;
        resetFreeze(maps);                  // 1. 시야 초기화
        int stone = calcFreeze(maps, knights, x, y);        // 2. 시야 계산 (석화)
        killKnights(knights, x, y);         // 3. 현재 위치 병사 제거
        auto [m, a] = moveKnights(maps, knights, x, y, n);     // 4. 병사 이동 및 공격
        answers.emplace_back(m, stone, a);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> N >> M;

    int sr, sc, er, ec;
    cin >> sr >> sc >> er >> ec;

    vector<tuple<int, int, bool>> knights(M);
    for (int i = 0; i < M; ++i) {
        int ar, ac;
        cin >> ar >> ac;
        knights[i] = {ar, ac, false};
    }

    vector<vector<pair<int, bool>>> maps(N, vector<pair<int, bool>>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int road;
            cin >> road;
            maps[i][j] = {road, false};
        }

    vector<tuple<int, int, int>> answers;
    vector<pair<int, int>> route;
    bfs(maps, knights, sr, sc, er, ec, N, answers, route);

    if (!visited[er][ec]) {
        cout << "-1\n";
    } else {
        for (auto &[a, b, c] : answers) {
            cout << a << " " << b << " " << c << "\n";
        }
        cout << 0 << "\n";
    }
    return 0;
}