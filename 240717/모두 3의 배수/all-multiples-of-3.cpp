#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    bool all = true;

    for(int i = 0; i < 5; i++){
        int a = 0;
        cin >> a;
        if(a % 3 != 0){
            all = false;
            cout << 0;
            break;
        }
    }

    if(all) cout << 1;
    
    return 0;
}