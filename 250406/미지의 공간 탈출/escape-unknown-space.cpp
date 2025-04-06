#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int dx4[4] = {-1, 1, 0, 0};
int dy4[4] = {0, 0, -1, 1};
int dx8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool visitedN[21][21];
bool visitedM[40][40];
int N = 0;
int M = 0;

void printMap(vector<vector<int>> &map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void infectMap(vector<vector<int>> &map, vector<tuple<pair<int, int>, int, int>> &strange, int time){
    for(int i = 0; i < strange.size(); i++){
        tuple<pair<int, int>, int, int> stranger = strange[i];
        int movement = time / get<2>(stranger);
        int x = get<0>(stranger).first;
        int y = get<0>(stranger).second;
        for(int j = 0; j < movement; j++){
            x += dx[get<1>(stranger)];
            y += dy[get<1>(stranger)];
            if(x >= 0 && x < map.size() && y >= 0 && y < map.size()){
                if(map[x][y] == 0){
                    map[x][y] = 5;
                    get<0>(stranger).first = x;
                    get<0>(stranger).second = y;
                }
                else{
                    break;
                }
            }
        }
    }
}

int bfsM(vector<vector<int>> &map, int start_r, int start_c, int goal_r, int goal_c){
    int time = 1;
    queue<tuple<int, int, int>> q;
    visitedM[start_r][start_c] = true;
    q.push(make_tuple(start_r, start_c, time));

    while(!q.empty()){
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int t = get<2>(q.front());
        q.pop();
        for(int i = 0; i < 4; i++){
            int next_x = x + dx4[i];
            int next_y = y + dy4[i];
            if(next_x >= 0 && next_x < map.size() && next_y >= 0 && next_y < map.size()){
                if(next_x == goal_r && next_y == goal_c){
                    visitedM[next_x][next_y] = true;
                    return t + 1;
                }
                if(!visitedM[next_x][next_y] && map[next_x][next_y] == 0){
                    visitedM[next_x][next_y] = true;
                    q.push(make_tuple(next_x, next_y, t + 1));
                }
                if(map[next_x][next_y] == 5){
                    // section 1, 3 -> 원래 x, y 값을 swap
                    if((next_x >= 0 && next_x <= M && next_y >= 0 && next_y <= M) 
                    || (next_x >= 2 * M && next_x <= 3 * M + 2 && next_y >= 2 * M && next_y <= 3 * M + 2)){
                        if(!visitedM[y][x] && map[y][x] == 0){
                            visitedM[y][x] = true;
                            q.push(make_tuple(y, x, t + 1));
                        }
                    }
                    else{
                        if(!visitedM[3 * M + 1 - y][3 * M + 1 - x] && map[3 * M + 1 - y][3 * M + 1 - x] == 0){
                            visitedM[3 * M + 1 - y][3 * M + 1 - x] = true;
                            q.push(make_tuple(3 * M + 1 - y, 3 * M + 1 - x, t + 1));
                        }
                    }
                }
            }
        }
    }

    return -1;
}

int bfsN(vector<vector<int>> &map, vector<tuple<pair<int, int>, int, int>> &strange, int start_r, int start_c, int goal_r, int goal_c, int t){
    int time = t;
    vector<vector<int>> tempMap = map;
    vector<tuple<pair<int, int>, int, int>> tempStrange = strange;
    queue<tuple<int, int, int>> q;

    visitedN[start_r][start_c] = true;
    q.push(make_tuple(start_r, start_c, time));

    while(!q.empty()){
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int t = get<2>(q.front());
        q.pop();
        tempMap = map;
        tempStrange = strange;
        infectMap(tempMap, tempStrange, t);
        for(int i = 0; i < 4; i++){
            int next_x = x + dx4[i];
            int next_y = y + dy4[i];
            if(next_x >= 0 && next_x < tempMap.size() && next_y >= 0 && next_y < tempMap.size()){
                if(next_x == goal_r && next_y == goal_c){
                    visitedN[next_x][next_y] = true;
                    return t;
                }
                if(!visitedN[next_x][next_y] && tempMap[next_x][next_y] == 0){
                    visitedN[next_x][next_y] = true;
                    q.push(make_tuple(next_x, next_y, t + 1));
                }
            }
        }
    }

    return -1;
}

int main() {
    int F;
    cin >> N >> M >> F;

    // 지도 만들기
    vector<vector<int>> map(N, vector<int>(N, 0));
    pair<int, int> floor_target = {0, 0};
    pair<int, int> wall_start = {0, 0};
    pair<int, int> wall_target = {0, 0};
    bool start_wall = false;
    bool first_meet = true;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int n;
            cin >> n;
            map[i][j] = n;
            if(n == 4){
                floor_target.first = i;
                floor_target.second = j;
            }

            // 벽 시작점 찾기
            if(n == 3){
                if(first_meet){
                    wall_start.first = i;
                    wall_start.second = j;
                    first_meet = false;
                }
            }
        }
    }

    // 벽 탈출구 찾기
    for(int i = wall_start.first; i < wall_start.first + M; i++){
        for(int j = wall_start.second; j < wall_start.second + M; j++){
            for(int k = 0; k < 8; k++){
                int x = i + dx8[k];
                int y = j + dy8[k];
                if(map[x][y] == 0){
                    wall_target.first = x;
                    wall_target.second = y;
                    break;
                }
            }
        }
    }
    //printMap(map);

    // 시간의 벽 지도 만들기
    vector<vector<int>> timeMap(3 * M + 2, vector<int>(3 * M + 2, 5));
    pair<int, int> timemachine = {0, 0};
    pair<int, int> changed_walltarget = {0, 0};
    // 동
    for(int j = 0; j < M; j++){
        for(int i = M; i > 0; i--){
            int n;
            cin >> n;
            timeMap[i + M][j + 2 * M + 1] = n;
        }
    }
    //printMap(timeMap);
    // 서
    for(int j = M; j > 0; j--){
        for(int i = 0; i < M; i++){
            int n;
            cin >> n;
            timeMap[i + M + 1][j] = n;
        }
    }
    //printMap(timeMap);
    // 남
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            int n;
            cin >> n;
            timeMap[i + 2 * M + 1][j + M + 1] = n;
        }
    }
    //printMap(timeMap);
    // 북
    for(int i = M; i > 0; i--){
        for(int j = M; j > 0; j--){
            int n;
            cin >> n;
            timeMap[i][j + M] = n;
        }
    }
    //printMap(timeMap);
    // 위
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            int n;
            cin >> n;
            timeMap[i + M + 1][j + M + 1] = n;
            if(n == 2){
                timemachine.first = i + M + 1;
                timemachine.second = j + M + 1;
            }
        }
    }
    // 벽 탈출구 추가
    int x = 0;
    int y = 0;
    if(wall_target.first < wall_start.first){
        x = 0;
    }
    else if(wall_target.first < wall_start.first + M){
        x = M + 1 + (wall_target.first - wall_start.first);
    }
    else{
        x = 3 * M + 1; 
    }
    if(wall_target.second < wall_start.second){
        y = 0;
    }
    else if(wall_target.second < wall_start.second + M){
        y = M + 1 + (wall_target.second - wall_start.second);
    }
    else{
        y = 3 * M + 1; 
    }
    timeMap[x][y] = 4;
    changed_walltarget.first = x;
    changed_walltarget.second = y;

    // 시간 이상 현상
    vector<tuple<pair<int, int>, int, int>> strange;
    for(int i = 0; i < F; i++){
        int r, c, d, v;
        cin >> r >> c >> d >> v;
        map[r][c] = 5;
        strange.push_back(make_tuple(make_pair(r, c), d, v));
    }
    
    int output1 = 0;
    output1 = bfsM(timeMap, timemachine.first, timemachine.second, changed_walltarget.first, changed_walltarget.second);
    
    if(output1 != -1){
        // output1초 동안 벽 입구가 감염되지는 않았는지 확인해야함
        vector<vector<int>> tempMap = map;
        infectMap(tempMap, strange, output1);
        if(tempMap[wall_target.first][wall_target.second] == 1){
            cout << -1;
        }
        else{
            int output2 = 0;
            output2 = bfsN(map, strange, wall_target.first, wall_target.second, floor_target.first, floor_target.second, output1);
            cout << output2;
        }
    }

    return 0;
}