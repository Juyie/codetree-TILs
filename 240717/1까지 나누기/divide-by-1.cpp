#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;
    int d = 1;

    while(n / d > 1){
        n /= d;
        d++;
    }

    cout << d;
    
    return 0;
}