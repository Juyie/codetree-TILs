#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

struct player {
public:
    int x;
    int y;
    bool escape;
    bool move;
    void setPlayer(int _x, int _y) {
        x = _x;
        y = _y;
        escape = false;
        move = false;
    };
};

int N = 0;
int output = 0;
// 상하좌우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
// 우상 좌상 우하 좌하
int dx4[4] = { -1, -1, 1, 1 };
int dy4[4] = { -1, 1, -1, 1 };

void drawMap(vector<vector<int>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printStatus(vector<player>& players, pair<int, int> exit) {
    for (int i = 0; i < players.size(); i++) {
        cout << "Player " << i + 1 << ": " << players[i].x << ", " << players[i].y << "\n";
    }
    cout << "Exit: " << exit.first << ", " << exit.second << "\n";
}

void turn90(vector<vector<int>>& map, vector<player>& players, vector<pair<int, int>> &closest, pair<int, int> &exit) {
    int up_x = closest[0].first;
    int down_x = closest[1].first;
    int left_y = closest[0].second;
    int right_y = closest[1].second;

    int size = abs(up_x - down_x) + 1;
    bool exit_move = false;

    // 정사각형 부분 tempMap에 옮기기, 범위에 포함되는 참여자와 출구도 tempMap 좌표로 옮기기
    vector<vector<int>> tempMap(size, vector<int>(size, 0));
    int x = 0;
    int y = 0;
    for (int i = up_x; i <= down_x; i++) {
        y = 0;
        for (int j = left_y; j <= right_y; j++) {
            if (i == exit.first && j == exit.second) {
                exit.first = x;
                exit.second = y;
                exit_move = true;
            }
            for (int k = 0; k < players.size(); k++) {
                if (!players[k].escape && i == players[k].x && j == players[k].y) {
                    players[k].x = x;
                    players[k].y = y;
                    players[k].move = true;
                }
            }
            tempMap[x][y] = map[i][j];
            y++;
        }
        x++;
    }

    // tempMap 회전해서 map에 적용하기
    x = 0;
    y = 0;
    for (int j = right_y; j >= left_y; j--) {
        y = 0;
        for (int i = up_x; i <= down_x; i++) {
            // 회전하려는게 출구라면 출구 좌표 업데이트
            if (exit_move && x == exit.first && y == exit.second) {
                exit.first = i;
                exit.second = j;
                exit_move = false;
            }
            // 회전하려는 데에 참여자가 있다면 참여자 좌표 업데이트
            for (int k = 0; k < players.size(); k++) {
                if (!players[k].escape && players[k].move && x == players[k].x && y == players[k].y) {
                    players[k].x = i;
                    players[k].y = j;
                    players[k].move = false;
                }
            }
            map[i][j] = tempMap[x][y];
            y++;
        }
        x++;
    }

    // 내구도 깎기
    for (int i = up_x; i <= down_x; i++) {
        for (int j = left_y; j <= right_y; j++) {
            if (map[i][j] > 0) {
                map[i][j]--;
            }
        }
    }
}

vector<pair<int, int>> findClosest(vector<player>& players, pair<int, int> &exit) {
    vector<pair<int, int>> output;

    while (true) {
        for (int s = 1; s < N; s++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int up_x = i;
                    int down_x = up_x + s;
                    int left_y = j;
                    int right_y = left_y + s;
                    // 만들어진 값이 맵 범위를 넘어가는지 확인
                    if (up_x >= 0 && up_x < N && down_x >= 0 && down_x < N && left_y >= 0 && left_y < N && right_y >= 0 && right_y < N) {
                        // 탈출구가 포함되지 않으면 다음 좌표로
                        if (!(up_x <= exit.first && down_x >= exit.first && left_y <= exit.second && right_y >= exit.second)) {
                            continue;
                        }
                        // 탈출구가 포함되었으면 플레이어가 하나라도 포함되는지 확인
                        for (int k = 0; k < players.size(); k++) {
                            if (!players[k].escape) {
                                if (players[k].x >= up_x && players[k].x <= down_x && players[k].y >= left_y && players[k].y <= right_y) {
                                    output.push_back(make_pair(up_x, left_y));
                                    output.push_back(make_pair(down_x, right_y));
                                    //cout << "좌상: " << up_x << ", " << left_y << ", 우하: " << down_x << ", " << right_y << "\n";
                                    return output;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void escape(vector<vector<int>>& map, vector<player>& players, pair<int, int> &exit) {
    // 탈출 못한 플레이어 이동
    for (int i = 0; i < players.size(); i++) {
        if (!players[i].escape) {
            int x = players[i].x;
            int y = players[i].y;

            for (int j = 0; j < 4; j++) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                    // 만약 이동하려는 곳이 탈출구라면 탈출
                    if (nx == exit.first && ny == exit.second) {
                        players[i].escape = true;
                        output++;
                        break;
                    }
                    // 이동하는 곳이 0이고, 거리가 가까워진다면 이동
                    if (map[nx][ny] == 0 && abs(x - exit.first) + abs(y - exit.second) > abs(nx - exit.first) + abs(ny - exit.second)) {
                        players[i].x = nx;
                        players[i].y = ny;
                        output++;
                        //cout << "Move 1 step: " << output << "\n";
                        break;
                    }
                }
            }
        }
    }

    // 가장 가까운 플레이어 찾기
    vector<pair<int, int>> colsest = findClosest(players, exit);
    // 찾은 사각형 기준으로 90도 회전하기
    turn90(map, players, colsest, exit);
}

bool checkAllExcape(vector<player>& players) {
    bool escape = true;
    for (int i = 0; i < players.size(); i++) {
        if (!players[i].escape) {
            escape = false;
            return escape;
        }
    }
    return escape;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int M, K;
    cin >> N >> M >> K;

    vector<vector<int>> map(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int n;
            cin >> n;
            map[i][j] = n;
        }
    }
    //drawMap(map);

    vector<player> players(M);
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        players[i].setPlayer(x - 1, y - 1);
    }

    pair<int, int> exit;
    int x, y;
    cin >> x >> y;
    exit = make_pair(x - 1, y - 1);

    for (int i = 0; i < K; i++) {
        // 탈출
        //cout << "Trial " << i + 1 << "\n";
        escape(map, players, exit);
        //drawMap(map);
        //printStatus(players, exit);
        // 전부 탈출 했다면 끝내기
        if (checkAllExcape(players)) {
            break;
        }
    }

    cout << output << "\n";
    cout << exit.first + 1 << " " << exit.second + 1;

    return 0;
}