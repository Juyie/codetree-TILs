#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;
    int area = n*n;
    cout << area << endl;
    if(n < 5) cout << "tiny";
    return 0;
}