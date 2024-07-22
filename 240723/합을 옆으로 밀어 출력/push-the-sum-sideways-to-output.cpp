#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;

    int sum = 0;
    for(int i = 0; i < n; i++){
        int n = 0;
        cin >> n;
        sum += n;
    }

    string s = to_string(sum);
    s = s.substr(1, s.length()) + s.substr(0, 1);
    cout << s;

    return 0;
}