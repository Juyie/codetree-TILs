#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct mapInfo {
public:
    int power;
    int attack_time;
    int attacked; // 0: 공격 안당함 1: 공격 당함 2: 공격자

    void setInfo(int p) {
        power = p;
        attack_time = 0;
        attacked = false;
    };
};

int N = 0;
int M = 0;
// 우하좌상
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
// 8방향
int dx8[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy8[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void printMap(vector<vector<mapInfo>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << "(" << map[i][j].power << ", " << map[i][j].attack_time << ") ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void destroyTower(vector<vector<mapInfo>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j].power < 0) {
                map[i][j].power = 0; // 음수 처리된 애들 0으로 초기화
            }
        }
    }
}

void attackAll(vector<vector<mapInfo>>& map, int minus_power) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j].attacked == 1) {
                map[i][j].power -= minus_power;
                //cout << "Attack: " << i << ", " << j << "\n";
            }
            else if (map[i][j].attacked == 0 && map[i][j].power > 0) {
                map[i][j].power++;
                //cout << "Heal: " << i << ", " << j << "\n";
            }
        }
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            map[i][j].attacked = 0;
        }
    }
}

int laserAttack(vector<vector<mapInfo>>& map, pair<int, int> attacker, pair<int, int> victim) {
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    visited[attacker.first][attacker.second] = true;
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> trace(N, vector<pair<int, int>>(M, make_pair(0, 0))); //좌표 역추적용
    q.push(attacker);
    map[attacker.first][attacker.second].attacked = 2;
    bool find = false;


    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = (x + dx[i] + N) % N;
            int ny = (y + dy[i] + M) % M;
            //cout << "original: " << nx << ", " << ny << ", Change: " << (nx + N) % N << ", "<< (ny + M) % M << "\n";

            // 목표 찾으면 바로 종료
            if (nx == victim.first && ny == victim.second) {
                map[nx][ny].power -= map[attacker.first][attacker.second].power; // 공격
                map[nx][ny].attacked = 2; // 체력을 또 빼면 안되니까

                int now_x = x;
                int now_y = y;
                //cout << now_x << ", " << now_y << "\n";
                while (!(now_x == attacker.first && now_y == attacker.second)) {
                    map[now_x][now_y].attacked = 1;
                    //cout << "Attack 후보: " << now_x << ", " << now_y << "\n";
                    pair<int, int> temp = trace[now_x][now_y];
                    now_x = temp.first;
                    now_y = temp.second;
                }

                attackAll(map, map[attacker.first][attacker.second].power / 2); // 경로에 있던 애들 공격하고 정비
                return 0;
            }

            if (!visited[nx][ny]) {
                if (map[nx][ny].power > 0) { // 벗어난 경우까지 모두 커버
                    //cout << "power:" << map[(nx + N) % N][(ny + M) % M].power << "\n";
                    //cout << "Push: " << (nx + N) % N << ", " << (ny + M) % M << "\n";
                    visited[nx][ny] = true;
                    q.push(make_pair(nx, ny));

                    trace[nx][ny] = make_pair(x, y);
                    //cout << "Make trace: " << x << ", " << y << " -> " << nx << ", " << ny << "\n";
                    //map[(nx + N) % N][(ny + M) % M].attacked = 1;
                }
            }
        }
    }

    return -1; // 레이저 공격을 실패했으면 -1 리턴
}

void bombAttack(vector<vector<mapInfo>>& map, pair<int, int> attacker, pair<int, int> victim) {
    int target_x = victim.first;
    int target_y = victim.second;
    int power = map[attacker.first][attacker.second].power;
    map[attacker.first][attacker.second].attacked = 2;
    map[target_x][target_y].power -= power;
    map[target_x][target_y].attacked = 2;

    for (int i = 0; i < 8; i++) {
        int nx = target_x + dx8[i];
        int ny = target_y + dy8[i];
        if (nx == attacker.first && ny == attacker.second) continue;
        if (map[(nx + N) % N][(ny + M) % M].power > 0) {
            map[(nx + N) % N][(ny + M) % M].attacked = 1;
        }
    }

    attackAll(map, power / 2);
}

int mostPowerful(vector<vector<mapInfo>>& map) {
    int maximum = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j].power > maximum) {
                maximum = map[i][j].power;
            }
        }
    }
    return maximum;
}

pair<int, int> chooseAttacker(vector<vector<mapInfo>>& map) {
    int r = 0;
    int c = 0;
    int minimum = 5001;
    int last_attack = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j].power == 0) continue; // 공격력 0인 애들은 제외
            if (map[i][j].power < minimum) {
                minimum = map[i][j].power;
                last_attack = map[i][j].attack_time;
                r = i;
                c = j;
            }
            else if (map[i][j].power == minimum) {
                if (map[i][j].attack_time > last_attack) {
                    minimum = map[i][j].power;
                    last_attack = map[i][j].attack_time;
                    r = i;
                    c = j;
                }
                else if (map[i][j].attack_time == last_attack) {
                    if (i + j > r + c) {
                        minimum = map[i][j].power;
                        last_attack = map[i][j].attack_time;
                        r = i;
                        c = j;
                    }
                    else if (i + j == r + c) {
                        if (j > c) {
                            minimum = map[i][j].power;
                            last_attack = map[i][j].attack_time;
                            r = i;
                            c = j;
                        }
                    }
                }
            }
        }
    }
    //map[r][c].power += N + M;
    //cout << map[r][c].power << "\n";
    return make_pair(r, c);
}

pair<int, int> chooseVictim(vector<vector<mapInfo>>& map) {
    int r = 0;
    int c = 0;
    int maximum = 0;
    int last_attack = 1001;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j].power > maximum) {
                maximum = map[i][j].power;
                last_attack = map[i][j].attack_time;
                r = i;
                c = j;
            }
            else if (map[i][j].power == maximum) {
                if (map[i][j].attack_time < last_attack) {
                    maximum = map[i][j].power;
                    last_attack = map[i][j].attack_time;
                    r = i;
                    c = j;
                }
                else if (map[i][j].attack_time == last_attack) {
                    if (i + j < r + c) {
                        maximum = map[i][j].power;
                        last_attack = map[i][j].attack_time;
                        r = i;
                        c = j;
                    }
                    else if (i + j == r + c) {
                        if (j < c) {
                            maximum = map[i][j].power;
                            last_attack = map[i][j].attack_time;
                            r = i;
                            c = j;
                        }
                    }
                }
            }
        }
    }
    return make_pair(r, c);
}

int main() {
    int K;
    cin >> N >> M >> K;
    vector<vector<mapInfo>> map(N, vector<mapInfo>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int n;
            cin >> n;
            map[i][j].setInfo(n);
        }
    }
    //printMap(map);

    for (int i = 0; i < K; i++) {
        pair<int, int> attacker = chooseAttacker(map);
        pair<int, int> victim = chooseVictim(map);
        map[attacker.first][attacker.second].attack_time = i + 1;
        map[attacker.first][attacker.second].power += N + M;
        //cout << "attacker: " << attacker.first << ", " << attacker.second << ", victim: " << victim.first << ", " << victim.second << "\n";
        int laser = laserAttack(map, attacker, victim);
        destroyTower(map);
        if (laser == -1) { // 레이저 공격을 실패한 경우
            //cout << "Bomb!" << "\n";
            bombAttack(map, attacker, victim);
            destroyTower(map);
        }
        //printMap(map);
    }

    cout << mostPowerful(map);

    return 0;
}