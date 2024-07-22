#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n, m = 0;
    cin >> n >> m;

    int arr1[n][m] = {0, };
    int arr2[n][m] = {0, };
    int arr3[n][m] = {0, };

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr1[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr2[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr1[i][j] != arr2[i][j]) arr3[i][j] = 1;
            else arr3[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << arr3[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}