#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_V = 100000;
long long tree[4 * MAX_V + 1];

void updateTree(int node, int start, int end, int idx, int diff){
    if(idx < start || idx > end) return;
    tree[node] += diff;
    if(start != end){
        int mid = (start + end) / 2;
        updateTree(node * 2, start, mid, idx, diff);
        updateTree(node * 2 + 1, mid + 1, end, idx, diff);
    }
}

long long query(int node, int start, int end, int l, int r){
    if(r < start || l > end) return 0;
    if(l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    map<string, int> DB_n;
    map<int, string> DB_v;

    int Q;
    cin >> Q;

    for(int i = 0; i < Q; i++){
        string cmd;
        cin >> cmd;

        if(cmd == "init"){
            DB_n.clear();
            DB_v.clear();
            fill(tree, tree + 4 * MAX_V + 1, 0);
        }
        else if(cmd == "insert"){
            string name;
            int value;
            cin >> name >> value;
            if(DB_n.find(name) == DB_n.end() && DB_v.find(value) == DB_v.end()){
                DB_n[name] = value;
                DB_v[value] = name;
                updateTree(1, 1, MAX_V, value, value);
                cout << 1 << "\n";
            }
            else{
                cout << 0 << "\n";
            }
        }
        else if(cmd == "delete"){
            string name;
            cin >> name;
            if(DB_n.find(name) == DB_n.end()){
                cout << 0 << "\n";
            }
            else{
                int value = DB_n[name];
                cout << value << "\n";
                DB_n.erase(name);
                DB_v.erase(value);
                updateTree(1, 1, MAX_V, value, -value);
            }
        }
        else if(cmd == "rank"){
            int k;
            cin >> k;
            if(DB_v.size() < k){
                cout << "None" << "\n";
            }
            else{
                auto iter = DB_v.begin();
                for(int j = 1; j < k; j++){
                    iter++;
                }
                cout << iter->second << "\n";
            }
        }
        else if(cmd == "sum"){
            int k;
            cin >> k;
            cout << query(1, 1, MAX_V, 1, k) << "\n";
        }
    }

    return 0;
}