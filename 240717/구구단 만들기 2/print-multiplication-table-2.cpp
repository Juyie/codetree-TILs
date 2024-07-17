#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b = 0;
    cin >> a >> b;

    for(int i = 0; i < 4; i++){
        for(int j = b; j >= a; j--){
            cout << j << " * " << (i+1)*2 << " = " << j*(i+1)*2;
            if(j != a) cout << " / ";
        }
        cout << endl;
    }

    return 0;
}