#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct error {
public:
    int x;
    int y;
    int d;
    int v;
    void setError(int _x, int _y, int _d, int _v) {
        x = _x;
        y = _y;
        d = _d;
        v = _v;
    }
};

int N = 0;
int M = 0;
// 동서남북
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

void printMap(vector<vector<int>> map) {
    cout << "\n";
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void moveError(vector<vector<int>>& map, vector<error>& errors, int time) {
    for (int i = 0; i < errors.size(); i++) {
        for (int j = 1; j <= time; j++) {
            if (j % errors[i].v == 0) {
                int nx = errors[i].x + dx[errors[i].d];
                int ny = errors[i].y + dy[errors[i].d];
                if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map.size()) {
                    if (map[nx][ny] == 0) {
                        map[nx][ny] = 1;
                        errors[i].x = nx;
                        errors[i].y = ny;
                    }
                }
            }
        }
    }
}

int escapeTimewall(vector<vector<int>>& timeMap, pair<int, int> start, pair<int, int> goal) {
    queue<pair<pair<int, int>, int>> q;
    vector<vector<bool>> visited(timeMap.size(), vector<bool>(timeMap.size(), false));
    q.push(make_pair(start, 0));
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int t = q.front().second;
        //cout << x << ", " << y << ", " << t << "\n";
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < timeMap.size() && ny >= 0 && ny < timeMap.size()) {
                if (nx == goal.first && ny == goal.second) {
                    return t + 1;
                }
                if (!visited[nx][ny] && timeMap[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    q.push(make_pair(make_pair(nx, ny), t + 1));
                }
                else if (!visited[nx][ny] && timeMap[nx][ny] == 5) { // 빈공간이라면? 대칭점 찾고 이동 가능한지 확인하기
                    if ((x < (3 * M + 2) / 2 && y < (3 * M + 2) / 2) || (x > (3 * M + 2) / 2 && y > (3 * M + 2) / 2)) { // 1, 3 사분면
                        //cout << "reverse1: " << y << ", " << x << "\n";
                        if (!visited[y][x] && timeMap[y][x] == 0) { // 대칭점이 이동 가능하다면
                            visited[y][x] = true;
                            q.push(make_pair(make_pair(y, x), t + 1));
                        }
                    }
                    else { // 2, 4 사분면
                        //cout << "reverse2: " << -y + 3 * M + 1 << ", " << -x + 3 * M + 1 << "\n";
                        if (!visited[-y + 3 * M + 1][-x + 3 * M + 1] && timeMap[-y + 3 * M + 1][-x + 3 * M + 1] == 0) {
                            visited[-y + 3 * M + 1][-x + 3 * M + 1] = true;
                            q.push(make_pair(make_pair(-y + 3 * M + 1, -x + 3 * M + 1), t + 1));
                        }

                    }
                }
            }
        }
    }

    return -1;
}

int escapeSpace(vector<vector<int>>& map, vector<error>& errors, pair<int, int> start, pair<int, int> goal, int time) {
    queue<pair<pair<int, int>, int>> q;
    vector<vector<bool>> visited(map.size(), vector<bool>(map.size(), false));
    q.push(make_pair(start, time));
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        vector<vector<int>> temp = map;
        vector<error> tempError = errors;
        int x = q.front().first.first;
        int y = q.front().first.second;
        int t = q.front().second;
        moveError(temp, tempError, t + 1); // 에러가 t + 1초만큼 번진 상태에서 가능한 경로 찾기
        //cout << t << ": ";
        //printMap(temp);
        //cout << x << ", " << y << ", " << t << "\n";
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map.size()) {
                if (nx == goal.first && ny == goal.second) {
                    return t + 1;
                }
                if (!visited[nx][ny] && temp[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    q.push(make_pair(make_pair(nx, ny), t + 1));
                }
            }
        }
    }

    return -1;
}

int main() {
    int F;
    cin >> N >> M >> F;

    vector<vector<int>> map(N, vector<int>(N, 0));
    pair<int, int> start;
    pair<int, int> goal;
    pair<int, int> first_timeWall;
    bool find = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int n;
            cin >> n;
            map[i][j] = n;
            if (n == 4) {
                goal.first = i;
                goal.second = j;
            }
            if (n == 3 && !find) {
                find = true;
                first_timeWall.first = i;
                first_timeWall.second = j;
            }
        }
    }
    //printMap(map);

    vector<vector<int>> timeMap(3 * M + 2, vector<int>(3 * M + 2, 5));
    pair<int, int> timeGoal;
    pair<int, int> timeMachine;
    // 동
    for (int j = 2 * M + 1; j <= 3 * M; j++) {
        for (int i = 2 * M; i >= M + 1; i--) {
            int n;
            cin >> n;
            timeMap[i][j] = n;
        }
    }
    int j = 3 * M + 1;
    int ori_i = first_timeWall.first;
    int ori_j = first_timeWall.second + M;
    for (int i = M + 1; i <= 2 * M; i++) {
        timeMap[i][j] = map[ori_i][ori_j];
        if (map[ori_i][ori_j] == 0) {
            timeGoal.first = i;
            timeGoal.second = j;
            timeMap[i][j] = 4;
            start.first = ori_i;
            start.second = ori_j;
        }
        ori_i++;
    }
    // 서
    for (int j = M; j >= 1; j--) {
        for (int i = M + 1; i <= 2 * M; i++) {
            int n;
            cin >> n;
            timeMap[i][j] = n;
        }
    }
    j = 0;
    ori_i = first_timeWall.first;
    ori_j = first_timeWall.second - 1;
    for (int i = M + 1; i <= 2 * M; i++) {
        timeMap[i][j] = map[ori_i][ori_j];
        if (map[ori_i][ori_j] == 0) {
            timeGoal.first = i;
            timeGoal.second = j;
            timeMap[i][j] = 4;
            start.first = ori_i;
            start.second = ori_j;
        }
        ori_i++;
    }
    // 남
    for (int i = 2 * M + 1; i <= 3 * M; i++) {
        for (int j = M + 1; j <= 2 * M; j++) {
            int n;
            cin >> n;
            timeMap[i][j] = n;
        }
    }
    int i = 0;
    ori_i = first_timeWall.first - 1;
    ori_j = first_timeWall.second;
    for (int j = M + 1; j <= 2 * M; j++) {
        timeMap[i][j] = map[ori_i][ori_j];
        if (map[ori_i][ori_j] == 0) {
            timeGoal.first = i;
            timeGoal.second = j;
            timeMap[i][j] = 4;
            start.first = ori_i;
            start.second = ori_j;
        }
        ori_j++;
    }
    // 북
    for (int i = M; i >= 1; i--) {
        for (int j = 2 * M; j >= M + 1; j--) {
            int n;
            cin >> n;
            timeMap[i][j] = n;
        }
    }
    i = 3 * M + 1;
    ori_i = first_timeWall.first + M;
    ori_j = first_timeWall.second;
    for (j = M + 1; j <= 2 * M; j++) {
        timeMap[i][j] = map[ori_i][ori_j];
        if (map[ori_i][ori_j] == 0) {
            timeGoal.first = i;
            timeGoal.second = j;
            timeMap[i][j] = 4;
            start.first = ori_i;
            start.second = ori_j;
        }
        ori_j++;
    }
    // 위
    for (int i = M + 1; i <= 2 * M; i++) {
        for (int j = M + 1; j <= 2 * M; j++) {
            int n;
            cin >> n;
            timeMap[i][j] = n;
            if (n == 2) {
                timeMachine.first = i;
                timeMachine.second = j;
            }
        }
    }
    //printMap(timeMap);

    vector<error> errors(F);
    for (int i = 0; i < F; i++) {
        int r, c, d, v;
        cin >> r >> c >> d >> v;
        errors[i].setError(r, c, d, v);
        map[r][c] = 1;
    }

    int time = 0;
    time = escapeTimewall(timeMap, timeMachine, timeGoal);
    if (time == -1) {
        //cout << "time wall ";
        cout << -1;
        return 0;
    }
    moveError(map, errors, time);
    int time2 = 0;
    time2 = escapeSpace(map, errors, start, goal, time);
    //printMap(map);
    if (time2 == -1) {
        cout << -1;
        return 0;
    }

    cout << time2;

    return 0;
}