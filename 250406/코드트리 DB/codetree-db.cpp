#include <iostream>
#include <map>
using namespace std;

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
        }
        else if(cmd == "insert"){
            string name;
            int value;
            cin >> name >> value;
            if(DB_n.find(name) == DB_n.end() && DB_v.find(value) == DB_v.end()){
                DB_n[name] = value;
                DB_v[value] = name;
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
            long long output = 0;
            for(auto iter = DB_v.begin(); iter != DB_v.end(); iter++){
                if(iter->first > k){
                    break;
                }
                else{
                    output += iter->first;
                }
            }
            cout << output << "\n";
        }
    }

    return 0;
}