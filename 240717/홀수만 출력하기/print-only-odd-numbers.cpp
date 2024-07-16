#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;

    for(int i = 0; i < n; i++){
        int a = 0;
        cin >> a;
        if(a % 2 == 1 && a % 3 == 0) cout << a << endl;
    }
    return 0;
}