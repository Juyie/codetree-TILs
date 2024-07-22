#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a, b;
    cin >> a >> b;
    int n = 0;

    for(int i = 0; i < a.length(); i++){
        a = a.substr(a.length() - 1, 1) + a.substr(0, a.length() - 1);
        n++;
        if(a == b) break;
    }

    if(n == 0) cout << -1;
    else cout << n;

    return 0;
}