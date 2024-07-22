#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a, b;
    cin >> a >> b;

    int cnt = 0;

    for(int i = 0; i < a.length() - 1; i++){
        if(a[i] == b[0]){
            if(a[i+1] == b[1]) cnt++;
        }
    }

    cout << cnt;
    
    return 0;
}