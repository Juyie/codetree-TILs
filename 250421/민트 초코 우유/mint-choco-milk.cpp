#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int N = 0;
// 상하좌우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct cell {
public:
    char color;
    int power;
    // T, C, M: 0, TC, TM, CM: 1, TCM: 2
    int group = 0;
    bool attacked = false;
};

void printMap(vector<vector<cell> > map) {
    cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "(" << map[i][j].color << ", " << map[i][j].power << ") ";
        }
        cout << "\n";
    }
}

bool comp(pair<pair<int, int>, pair<int, int> > a, pair<pair<int, int>, pair<int, int> > b) {
    if (a.first.first != b.first.first) {
        // 그룹 (낮은순)
        return a.first.first < b.first.first;
    } else {
        if (a.first.second != b.first.second) {
            // 신앙심 (높은순)
            return a.first.second > b.first.second;
        } else {
            if (a.second.first != b.second.first) {
                // 행 (낮은순)
                return a.second.first < b.second.first;
            } else {
                if (a.second.second != b.second.second) {
                    // 열 (낮은순)
                    return a.second.second < b.second.second;
                }
            }
        }
    }
}

void resetAttack(vector<vector<cell> > &map) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j].attacked = false;
        }
    }
}

void combine(int x1, int y1, int x2, int y2, vector<vector<cell> > &map) {
    char c1 = map[x1][y1].color;
    char c2 = map[x2][y2].color;

    if (c1 == c2) {
        return;
    } else if ((c1 == 'T' && c2 == 'C') || (c2 == 'T' && c1 == 'C')) {
        map[x2][y2].color = 'D';
        map[x2][y2].group = 1;
    } else if ((c1 == 'T' && c2 == 'M') || (c2 == 'T' && c1 == 'M')) {
        map[x2][y2].color = 'B';
        map[x2][y2].group = 1;
    } else if ((c1 == 'M' && c2 == 'C') || (c2 == 'M' && c1 == 'C')) {
        map[x2][y2].color = 'A';
        map[x2][y2].group = 1;
    } else if ((c1 == 'T' && c2 == 'B') || (c2 == 'T' && c1 == 'B') || (c1 == 'M' && c2 == 'B') || (
                   c2 == 'M' && c1 == 'B')) {
        map[x2][y2].color = 'B';
        map[x2][y2].group = 1;
    } else if ((c1 == 'T' && c2 == 'D') || (c2 == 'T' && c1 == 'D') || (c1 == 'C' && c2 == 'D') || (
                   c2 == 'C' && c1 == 'D')) {
        map[x2][y2].color = 'D';
        map[x2][y2].group = 1;
    } else if ((c1 == 'C' && c2 == 'A') || (c2 == 'C' && c1 == 'A') || (c1 == 'M' && c2 == 'A') || (
                   c2 == 'M' && c1 == 'A')) {
        map[x2][y2].color = 'A';
        map[x2][y2].group = 1;
    } else {
        map[x2][y2].color = 'F';
        map[x2][y2].group = 2;
    }
}

void morning(vector<vector<cell> > &map) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j].power++;
        }
    }
}

void dinner(vector<vector<cell> > &map, vector<pair<pair<int, int>, pair<int, int> > > &attacker) {
    for (int i = 0; i < attacker.size(); i++) {
        //cout << "Attacker: " << i + 1 << "\n";
        int x = attacker[i].second.first;
        int y = attacker[i].second.second;
        int power = map[x][y].power;

        if (!map[x][y].attacked) {
            map[x][y].power = 1;
            int raser_power = power - 1;
            int dir = power % 4;
            //cout << dir << "\n";
            int nx = x;
            int ny = y;
            while (raser_power > 0) {
                nx += dx[dir];
                ny += dy[dir];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                    if (map[x][y].color != map[nx][ny].color) {
                        if (raser_power > map[nx][ny].power) {
                            // 강한 전파
                            //cout << "(" << nx << ", " << ny << "): strong" << "\n";
                            map[nx][ny].color = map[x][y].color;
                            raser_power -= map[nx][ny].power + 1;
                            map[nx][ny].power++;
                            map[nx][ny].attacked = true;
                        } else {
                            // 약한 전파
                            //cout << "(" << nx << ", " << ny << "): weak" << "\n";
                            combine(x, y, nx, ny, map);
                            map[nx][ny].power += raser_power;
                            raser_power = 0;
                            map[nx][ny].attacked = true;
                        }
                    }
                } else {
                    raser_power = 0;
                }
            }
            //printMap(map);
        }
    }
}

void lunch(vector<vector<cell> > &map) {
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    vector<pair<pair<int, int>, pair<int, int> > > attacker;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                queue<pair<int, int> > q;
                vector<pair<int, int> > group;
                visited[i][j] = true;
                char color = map[i][j].color;
                int max_power = map[i][j].power;
                int max_x = i;
                int max_y = j;
                q.push({i, j});
                group.push_back({i, j});

                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                            if (!visited[nx][ny] && map[nx][ny].color == color) {
                                visited[nx][ny] = true;
                                if (map[nx][ny].power > max_power) {
                                    max_power = map[nx][ny].power;
                                    max_x = nx;
                                    max_y = ny;
                                }
                                q.push({nx, ny});
                                group.push_back({nx, ny});
                            }
                        }
                    }
                }

                // group에 같은 그룹 인덱스 모두 들어있음.
                attacker.push_back({{map[max_x][max_y].group, max_power}, {max_x, max_y}});
                int n = group.size();
                for (int i = 0; i < n; i++) {
                    if (group[i].first == max_x && group[i].second == max_y) {
                        map[group[i].first][group[i].second].power += n - 1;
                    } else {
                        map[group[i].first][group[i].second].power--;
                    }
                }
            }
        }
    }
    //printMap(map);

    sort(attacker.begin(), attacker.end(), comp);

    dinner(map, attacker);
}

void printResult(vector<vector<cell> > map) {
    int F = 0;
    int D = 0;
    int B = 0;
    int A = 0;
    int M = 0;
    int C = 0;
    int T = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j].color == 'T') {
                T += map[i][j].power;
            } else if (map[i][j].color == 'C') {
                C += map[i][j].power;
            } else if (map[i][j].color == 'M') {
                M += map[i][j].power;
            } else if (map[i][j].color == 'A') {
                A += map[i][j].power;
            } else if (map[i][j].color == 'B') {
                B += map[i][j].power;
            } else if (map[i][j].color == 'D') {
                D += map[i][j].power;
            } else if (map[i][j].color == 'F') {
                F += map[i][j].power;
            }
        }
    }

    cout << F << " " << D << " " << B << " " << A << " " << M << " " << C << " " << T << "\n";
}

int main() {
    int T;
    cin >> N >> T;

    vector<vector<cell> > map(N, vector<cell>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char input;
            cin >> input;
            map[i][j].color = input;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int p;
            cin >> p;
            map[i][j].power = p;
        }
    }

    //printMap(map);

    for (int i = 0; i < T; i++) {
        //cout << "Trial: " << i + 1 << "\n";
        resetAttack(map);
        //cout << "Morning" << "\n";
        morning(map);
        //printMap(map);
        //cout << "Lunch" << "\n";
        lunch(map);
        //printMap(map);
        printResult(map);
    }

    return 0;
}
