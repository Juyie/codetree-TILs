#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string s;
    cin >> s;

    for(int i = 0; i < s.length(); i++){
        if('A' <= s[i] && s[i] <= 'Z') s[i] += 32;
        else s[i] -= 32;
    }

    cout << s;
    
    return 0;
}