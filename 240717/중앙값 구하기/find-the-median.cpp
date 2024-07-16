#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b, c = 0;
    cin >> a >> b >> c;

    vector<int> list = {a, b, c};

    sort(list.begin(), list.end());

    cout << list[1];

    return 0;
}