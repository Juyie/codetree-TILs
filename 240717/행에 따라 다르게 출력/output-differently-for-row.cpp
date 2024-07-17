#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;

    int num = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < n; j++){
            if(i % 2 == 0){
                num += 2;
            }
            else{
                num += 1;
            }
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}