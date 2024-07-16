#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b = 0;
    cin >> a >> b;

    for(int i = a; i <= b; i++){
        if(i % 2 == 1) cout << i << " ";
    }

    return 0;
}