#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a;
    string b;

    cin >> a >> b;

    string c1 = a + b;
    string c2 = b + a;
    bool flag = true;

    for(int i = 0; i < c1.length(); i++){
        if(c1[i] != c2[i]){
            flag = false;
            break;
        }
    }

    if(flag) cout << "true";
    else cout << "false";

    return 0;
}