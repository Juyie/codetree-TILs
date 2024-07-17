#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int N = 0; 
    cin >> N;

    char c = 'A';

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j < i) cout << "  ";
            else{
                cout << c << " ";
                c += 1;
            }
        }
        cout << endl;
    }

    return 0;
}