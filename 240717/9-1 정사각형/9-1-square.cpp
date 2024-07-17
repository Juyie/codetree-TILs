#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n =0;
    cin >> n;

    int num = 9;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(num == 0) num = 9;
            cout << num;
            num--;
        }
        cout << endl;
    }
    return 0;
}