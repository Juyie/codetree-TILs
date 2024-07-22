#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a0, a1 = 0;
    cin >> a0 >> a1;
    cout << a0 << " " << a1 << " ";
    
    for(int i = 0; i < 8; i++){
        int a2 = a1 + 2 * a0;
        cout << a2 << " ";
        a0 = a1;
        a1 = a2;
    }



    return 0;
}