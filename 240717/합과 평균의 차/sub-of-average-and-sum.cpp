#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b, c = 0;
    cin >> a >> b >> c;
    int sum = a+b+c;
    int avg = sum / 3;
    cout << sum << endl << avg << endl << sum-avg;
    return 0;
}