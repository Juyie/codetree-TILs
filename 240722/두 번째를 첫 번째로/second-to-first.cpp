#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string s;
    cin >> s;
    char first = s[0];
    char second = s[1];

    for(int i = 0; i < s.length(); i++){
        if(s[i] == second) s[i] = first;
    }

    cout << s;
    
    return 0;
}