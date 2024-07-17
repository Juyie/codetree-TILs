#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;

    int mat[n][n] = {0, };

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = (j+1) * (i+1);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = n-1; j >= 0; j--){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}