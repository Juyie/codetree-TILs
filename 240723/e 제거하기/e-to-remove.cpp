#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string s;
    cin >> s;

    s.erase(find(s.begin(), s.end(), 'e'));

    cout << s;

    return 0;
}