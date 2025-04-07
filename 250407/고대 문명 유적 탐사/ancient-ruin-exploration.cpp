#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dx4[4] = {-1, 1, 0, 0};
int dy4[4] = {0, 0, -1, 1};
int dxn[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
int dyn[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
queue<int> newNumber;

void printMap(vector<vector<int> > &map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void turn90(vector<vector<int> > &map, int x, int y) {
    vector<vector<int> > temp(3, vector<int>(3, 0));
    for (int i = 0; i < 9; i++) {
        temp[dxn[i]][dyn[i]] = map[x + dx[i]][y + dy[i]];
    }

    int count = 0;
    for (int j = 1; j >= -1; j--) {
        for (int i = -1; i <= 1; i++) {
            map[x + i][y + j] = temp[dxn[count]][dyn[count]];
            count++;
        }
    }
}

void turn180(vector<vector<int> > &map, int x, int y) {
    vector<vector<int> > temp(3, vector<int>(3, 0));
    for (int i = 0; i < 9; i++) {
        temp[dxn[i]][dyn[i]] = map[x + dx[i]][y + dy[i]];
    }

    int count = 0;
    for (int i = 1; i >= -1; i--) {
        for (int j = 1; j >= -1; j--) {
            map[x + i][y + j] = temp[dxn[count]][dyn[count]];
            count++;
        }
    }
}

void turn270(vector<vector<int> > &map, int x, int y) {
    vector<vector<int> > temp(3, vector<int>(3, 0));
    for (int i = 0; i < 9; i++) {
        temp[dxn[i]][dyn[i]] = map[x + dx[i]][y + dy[i]];
    }

    int count = 0;
    for (int j = -1; j <= 1; j++) {
        for (int i = 1; i >= -1; i--) {
            map[x + i][y + j] = temp[dxn[count]][dyn[count]];
            count++;
        }
    }
}

void fillBlank(vector<vector<int> > &map) {
    for (int j = 0; j < 5; j++) {
        for (int i = 4; i >= 0; i--) {
            if (map[i][j] == 0 && !newNumber.empty()) {
                map[i][j] = newNumber.front();
                newNumber.pop();
            }
        }
    }
}

int calcValue_bfs(vector<vector<int> > &map) {
    vector<vector<bool> > visited(5, vector<bool>(5, false));
    int output = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int value = 0;
            queue<pair<pair<int, int>, int> > q;
            queue<pair<int, int> > del;
            if (!visited[i][j]) {
                visited[i][j] = true;
                value = map[i][j];
                q.push(make_pair(make_pair(i, j), value));
                del.push(make_pair(i, j));

                while (!q.empty()) {
                    int x = q.front().first.first;
                    int y = q.front().first.second;
                    int v = q.front().second;
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx4[k];
                        int ny = y + dy4[k];
                        if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5) {
                            if (!visited[nx][ny] && map[nx][ny] == v) {
                                visited[nx][ny] = true;
                                q.push(make_pair(make_pair(nx, ny), v));
                                del.push(make_pair(nx, ny));
                            }
                        }
                    }
                }
                if (del.size() >= 3) {
                    output += del.size();
                    while (!del.empty()) {
                        int del_x = del.front().first;
                        int del_y = del.front().second;
                        del.pop();
                        map[del_x][del_y] = 0;
                    }
                }
            }
        }
    }

    return output;
}

int turnMap(vector<vector<int> > &map) {
    int max_x = 1;
    int max_y = 1;
    int maximum = 0;
    int type = 0;
    int count = 0;
    vector<vector<int> > tempMap = map;
    // 임시 지도를 회전하며 가장 적절한 회전 찾기
    for (int j = 1; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            tempMap = map;
            turn90(tempMap, i, j);
            count = calcValue_bfs(tempMap);
            if (count > maximum) {
                max_x = i;
                max_y = j;
                maximum = count;
                type = 0;
            }
        }
    }

    for (int j = 1; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            tempMap = map;
            turn180(tempMap, i, j);
            count = calcValue_bfs(tempMap);
            if (count > maximum) {
                max_x = i;
                max_y = j;
                maximum = count;
                type = 1;
            }
        }
    }

    for (int j = 1; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            tempMap = map;
            turn270(tempMap, i, j);
            count = calcValue_bfs(tempMap);
            if (count > maximum) {
                max_x = i;
                max_y = j;
                maximum = count;
                type = 2;
            }
        }
    }

    // 가장 값이 큰 것으로 진짜 지도를 회전
    if (type == 0) {
        turn90(map, max_x, max_y);
    } else if (type == 1) {
        turn180(map, max_x, max_y);
    } else {
        turn270(map, max_x, max_y);
    }
    int newOutput = calcValue_bfs(map);
    int output = newOutput;
    while (newOutput > 0) {
        fillBlank(map); // 일단 1회 시행 했으니까 빈거 채우기
        newOutput = calcValue_bfs(map);
        output += newOutput;
    }

    return output;
}

int main() {
    // Please write your code here.
    int K, M;
    cin >> K >> M;
    vector<vector<int> > map(5, vector<int>(5, 0));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int n;
            cin >> n;
            map[i][j] = n;
        }
    }
    for (int i = 0; i < M; i++) {
        int n;
        cin >> n;
        newNumber.push(n);
    }
    //printMap(map);
    for (int i = 0; i < K; i++) {
        int output = turnMap(map);
        if (output == 0) {
            break;
        } else {
            cout << output << " ";
        }
    }

    return 0;
}
