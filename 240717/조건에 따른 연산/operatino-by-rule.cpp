#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;

    int cnt = 0;

    while(n < 1000){
        if(n % 2 == 0) n = n * 3 + 1;
        else n = n * 2 + 2;
        cnt++;
    }

    cout << cnt;
    
    return 0;
}