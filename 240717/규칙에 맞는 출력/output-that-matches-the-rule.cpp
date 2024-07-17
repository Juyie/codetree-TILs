#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int N = 0;
    cin >> N;

    for(int i = 0; i < N; i++){
        for(int j = i; j >= 0; j--){
            cout << N-j << " ";
        }
        cout << endl;
    }

    return 0;
}