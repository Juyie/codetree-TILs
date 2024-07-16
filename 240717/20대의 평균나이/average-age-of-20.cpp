#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int sum = 0;
    int cnt = 0;

    while(true){
        int a = 0;
        cin >> a;
        if(a / 10 != 2){
            printf("%.2f", (float)sum / cnt);
            break;
        }
        sum += a;
        cnt++;
    }

    return 0;
}