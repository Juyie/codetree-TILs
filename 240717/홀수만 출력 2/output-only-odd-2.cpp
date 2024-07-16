#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int b, a = 0;
    cin >> b >> a;

    for(int i = b; i >= a; i--){
        if(i % 2 == 1) cout << i << " ";
    }
    return 0;
}