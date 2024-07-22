#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;
    int arr[n][n];
    int cnt = 1;

    for(int i = n-1; i >= 0; i--){
        for(int j = n-1; j >= 0; j--){
            arr[j][i] = cnt;
            cnt++;
        }
        i--;
        if(i < 0) break;
        for(int j = 0; j < n; j++){
            arr[j][i] = cnt;
            cnt++;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}