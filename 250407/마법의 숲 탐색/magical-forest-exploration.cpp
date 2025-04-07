#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 북동남서
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
// 상하좌우
int dxf[4] = { -1, 1, 0, 0 };
int dyf[4] = { 0, 0, -1, 1 };
int R = 0;
int C = 0;

void printMap(vector<vector<int> >& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool rangeCheck(int a, int b, int c, int d, int e, int f) {
    if (a >= -1 && a < R && c >= -1 && c < R && e >= -1 && e < R
        && b >= 0 && b < C && d >= 0 && d < C && f >= 0 && f < C) {
        return true;
    }
    return false;
}

int clockwise(int d) {
    if (d == 0) {
        return 1;
    }
    else if (d == 1) {
        return 2;
    }
    else if (d == 2) {
        return 3;
    }
    else {
        return 0;
    }
}

int counterclockwise(int d) {
    if (d == 0) {
        return 3;
    }
    else if (d == 1) {
        return 0;
    }
    else if (d == 2) {
        return 1;
    }
    else {
        return 2;
    }
}

void clearMap(vector<vector<int> >& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            map[i][j] = -1;
        }
    }
}

int moveFairy(vector<vector<int> >& map, pair<int, int> fairy) {
    int output = fairy.first; // 현재 x 좌표
    queue<pair<pair<int, int>, int>> q; // 좌표, 땅의 값
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    int value = map[fairy.first][fairy.second];
    int first_value = value;
    visited[fairy.first][fairy.second] = true;
    q.push(make_pair(fairy, value));

    while (!q.empty()) { // 갈 수 있는 값을 전부 탐색하고, x 좌표의 최댓값 저장하기
        int x = q.front().first.first;
        int y = q.front().first.second;
        int v = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dxf[i];
            int ny = y + dyf[i];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
                if (v >= 10000) { // 현재 출구에 있다면 어디든 갈 수 있음
                    if (!visited[nx][ny] && map[nx][ny] >= 0) {
                        visited[nx][ny] = true;
                        q.push(make_pair(make_pair(nx, ny), map[nx][ny]));
                        output = max(output, nx);
                    }
                }
                else {
                    if (!visited[nx][ny] && (map[nx][ny] == v || (map[nx][ny] / 10000 == v))) {
                        visited[nx][ny] = true;
                        q.push(make_pair(make_pair(nx, ny), map[nx][ny]));
                        output = max(output, nx);
                    }
                }
            }
        }
    }

    return output + 1; // 좌표 시작점이 1이므로 1더해서 리턴 
}

int moveGolem(vector<vector<int> >& map, int c, int d, int order) {
    bool movable = true;
    pair<int, int> center = make_pair(-2, c - 1);

    while (movable) {
        // 남쪽 이동
        int left_x = center.first + 1;
        int left_y = center.second - 1;
        int front_x = center.first + 2;
        int front_y = center.second;
        int right_x = center.first + 1;
        int right_y = center.second + 1;
        if (rangeCheck(left_x, left_y, front_x, front_y, right_x, right_y)) {
            if ((left_x < 0 || map[left_x][left_y] == -1) && map[front_x][front_y] == -1 && (right_x < 0 || map[right_x][right_y] == -1)) {
                center.first += 1;
                continue;
            }
        }
        // 서쪽 이동
        left_x = center.first + 1;
        left_y = center.second - 1;
        front_x = center.first;
        front_y = center.second - 2;
        right_x = center.first - 1;
        right_y = center.second - 1;
        pair<int, int> temp_center = center;
        int temp_d = d;
        if (rangeCheck(left_x, left_y, front_x, front_y, right_x, right_y)) {
            if ((left_x < 0 || map[left_x][left_y] == -1) && map[front_x][front_y] == -1 && (right_x < 0 || map[right_x][right_y] == -1)) {
                temp_center.second -= 1;
                temp_d = counterclockwise(temp_d);

                left_x = temp_center.first + 1;
                left_y = temp_center.second - 1;
                front_x = temp_center.first + 2;
                front_y = temp_center.second;
                right_x = temp_center.first + 1;
                right_y = temp_center.second + 1;
                if (rangeCheck(left_x, left_y, front_x, front_y, right_x, right_y)) {
                    if ((left_x < 0 || map[left_x][left_y] == -1) && map[front_x][front_y] == -1 && (right_x < 0 || map[right_x][right_y] == -1)) {
                        temp_center.first += 1;
                        center = temp_center;
                        d = temp_d;
                        continue;
                    }
                }
            }
        }
        // 동쪽 이동
        left_x = center.first - 1;
        left_y = center.second + 1;
        front_x = center.first;
        front_y = center.second + 2;
        right_x = center.first + 1;
        right_y = center.second + 1;
        temp_center = center;
        temp_d = d;
        if (rangeCheck(left_x, left_y, front_x, front_y, right_x, right_y)) {
            if ((left_x < 0 || map[left_x][left_y] == -1) && map[front_x][front_y] == -1 && (right_x < 0 || map[right_x][right_y] == -1)) {
                temp_center.second += 1;
                temp_d = clockwise(temp_d);

                left_x = temp_center.first + 1;
                left_y = temp_center.second - 1;
                front_x = temp_center.first + 2;
                front_y = temp_center.second;
                right_x = temp_center.first + 1;
                right_y = temp_center.second + 1;
                if (rangeCheck(left_x, left_y, front_x, front_y, right_x, right_y)) {
                    if ((left_x < 0 || map[left_x][left_y] == -1) && map[front_x][front_y] == -1 && (right_x < 0 || map[right_x][right_y] == -1)) {
                        temp_center.first += 1;
                        center = temp_center;
                        d = temp_d;
                        continue;
                    }
                }
            }
        }
        movable = false;
    }

    int moveCount = 0;
    // 이동 다 했는데 지도 밖으로 벗어나 있으면 지도 지우기
    if (center.first <= 0) {
        clearMap(map);
    }
    else {
        // 가능 범위 이면 지도에 반영하기
        map[center.first][center.second] = order;
        for (int i = 0; i < 4; i++) {
            if (i == d) {
                map[center.first + dx[i]][center.second + dy[i]] = order * 10000;
            }
            else {
                map[center.first + dx[i]][center.second + dy[i]] = order;
            }
        }
        //cout << "골렘 다 쌓은 지도" << "\n";
        //printMap(map);
        moveCount = moveFairy(map, center);
    }

    return moveCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    cin >> R >> C >> K;
    vector<vector<int> > map(R, vector<int>(C, -1));

    int output = 0;
    for (int i = 1; i <= K; i++) {
        int c, d;
        cin >> c >> d;
        output += moveGolem(map, c, d, i);
        //cout << "중간 값: " << output << "\n";
        //printMap(map);
    }

    cout << output;

    return 0;
}
