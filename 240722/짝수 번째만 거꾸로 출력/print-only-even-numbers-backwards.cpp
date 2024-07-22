#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string s;
    cin >> s;

    for(int i = s.length() - 1; i >= 0; i--){
        if(i % 2 != 0) cout << s[i];
    }

    return 0;
}