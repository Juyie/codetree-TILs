#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b = 0;
    cin >> a >> b;
    bool find = false;

    for(int i = a; i <= b; i++){
        if(1920 % i == 0 && 2880 % i == 0){
            cout << 1;
            find = true;
            break;
        }
    }

    if(!find) cout << 0;
    
    return 0;
}