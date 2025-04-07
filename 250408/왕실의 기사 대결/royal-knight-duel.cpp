#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 위쪽 오른쪽 아래쪽 왼쪽
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
queue<pair<int, int>> order;

struct knight{
public:
    int r;
    int c;
    int h;
    int w;
    int k;
    int origin_k;

    void set(int _r, int _c, int _h, int _w, int _k){
        r = _r;
        c = _c;
        h = _h;
        w = _w;
        k = _k;
        origin_k = _k;
    };
};

void printMap(vector<vector<int>> &map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool checkKnight(vector<knight> &knights, int id, int up_x1, int down_x1, int left_y1, int right_y1){
    int up_x2 = knights[id].r;
    int down_x2 = knights[id].r + knights[id].h - 1;
    int left_y2 = knights[id].c;
    int right_y2 = knights[id].c + knights[id].w - 1;
    for(int i = up_x1; i <= down_x1; i++){
        for(int j = left_y1; j <= right_y1; j++){
            for(int k = up_x2; k <= down_x2; k++){
                for(int h = left_y2; h <= right_y2; h++){
                    if(i == k && j == h){
                        return true; // 해당 위치에 다른 기사가 있으면 true 리턴
                    }
                }
            }
        }
    }
    return false; // 아무도 없으면 false 리턴
}

int calcDamage(vector<vector<int>> &map, knight knights){
    int up_x = knights.r;
    int down_x = up_x + knights.h - 1;
    int left_y = knights.c;
    int right_y = left_y + knights.w - 1;
    //cout << "(" << up_x << ", " << left_y << "), (" << down_x << ", " << right_y << ")\n";
    int output = 0;

    for(int i = up_x; i <= down_x; i++){
        for(int j = left_y; j <= right_y; j++){
            if(map[i][j] == 1){
                output++;
            }
        }
    }
    return output;
}

int moveKnight(vector<vector<int>> &map, vector<knight> &knights, int id, int dir, bool first, int damage){
    int up_x = knights[id].r;
    int down_x = knights[id].r + knights[id].h - 1;
    int left_y = knights[id].c;
    int right_y = knights[id].c + knights[id].w - 1;
    int output = 0;
    
    if(knights[id].k > 0){ // 체력이 남은 나이트에 대해서만 계산
        for(int i = up_x; i <= down_x; i++){
            for(int j = left_y; j <= right_y; j++){
                // 이동해야할 좌표 만들기
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                // 지도 내에 존재하는지 확인
                if(nx >= 0 && nx < map.size() && ny >= 0 && ny < map.size()){
                    // 만약 벽이라면 이동 못함, -1 리턴
                    if(map[nx][ny] == 2){
                        return -1;
                    }
                }
                else{
                    return -1; // 범위 바깥으로 나가는 경우도 이동 못함
                }
            }
        } // 전체를 모두 이동 시켰을 때 벽이 아님
                
        for(int k = 0; k < knights.size(); k++){ // 함정이나 빈칸이라면 다른 기사가 있는지 체크
            if(k != id && knights[k].k > 0){ // 자신은 빼고 생각, 체력 남은 기사들에 대해서만 생각
                if(checkKnight(knights, k, up_x + dx[dir], down_x + dx[dir], left_y + dy[dir], right_y + dy[dir])){ // 다른 기사가 있다면 기사 옆으로 밀기
                    //cout << "push: " << k + 1<< "\n";
                    output = moveKnight(map, knights, k, dir, false, damage); // 처음 밀린 애가 아니니까 false로 넘기기
                }
            }
        }
        if(output == -1){ // 다른 기사가 이동을 못한다면 이 기사도 이동 못함
            //cout << "can't move" << "\n";
            return -1;
        }
        else{ // 좌표 이동 시키고, 체력 깎기
            //cout << "can move: " << id + 1 << "\n";
            knights[id].r += dx[dir];
            knights[id].c += dy[dir];
            //cout << "move to: " << knights[id].r << ", " << knights[id].c << "\n";
            if(!first){ // 밀린 애라면 체력도 깎기
                damage = calcDamage(map, knights[id]);
                //cout << "damage(" << id + 1 << "): " << damage << "\n";
                knights[id].k -= damage;
            }
        }
    }
    return 0;
}

int main() {
    int L, N, Q;
    cin >> L >> N >> Q;

    vector<vector<int>> map(L, vector<int>(L, 0));

    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            int n;
            cin >> n;
            map[i][j] = n;
        }
    }
    //printMap(map);

    vector<knight> knights(N); 
    for(int i = 0; i < N; i++){
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knights[i].set(r - 1, c - 1, h, w, k);
    }

    for(int i = 0; i < Q; i++){
        int id, dir;
        cin >> id >> dir;
        moveKnight(map, knights, id - 1, dir, true, 0);
        //cout << "1: " << knights[0].k << ", 2: " << knights[1].k << ", 3: " << knights[2].k << "\n";
    }

    int output = 0;
    for(int i = 0; i < knights.size(); i++){
        if(knights[i].k > 0){
            output += knights[i].origin_k - knights[i].k;
        }
    }
    cout << output;

    return 0;
}