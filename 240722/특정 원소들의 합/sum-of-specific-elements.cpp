#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int arr[4][4] = {0, };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> arr[i][j];
        }
    }
    
    int sum = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j <= i; j++){
            sum += arr[i][j];
        }
    }

    cout << sum;

    return 0;
}