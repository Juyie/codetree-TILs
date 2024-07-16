#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string num = "";
    string mid, last = "";

    cin >> num;

    for(int i = 4; i < 8; i++){
        mid += num[i];
    }
    for(int i = 9; i < 13; i++){
        last += num[i];
    }

    cout << "010-" << last << "-" << mid;

    return 0;
}