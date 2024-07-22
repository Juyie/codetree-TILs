#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a;
    cin >> a;

    string cmd;
    cin >> cmd;

    for(int i = 0; i < cmd.length(); i++){
        if(cmd[i] == 'L'){
            char temp = a[0];
            for(int j = 0; j < a.length() - 1; j++){
                a[j] = a[j+1];
            }
            a[a.length() - 1] = temp;
        }
        else{
            char temp = a[a.length() - 1];
            for(int j = a.length() - 1; j > 0; j--){
                a[j] = a[j-1];
            }
            a[0] = temp;
        }
    }

    cout << a;

    return 0;
}