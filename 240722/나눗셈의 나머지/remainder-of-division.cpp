#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int a, b = 0;
    cin >> a >> b;
    int remains[11] = {0, };

    while(a >= 1){
        int remain = a % b;
        a = a / b;
        remains[remain]++;
    }

    int sum = 0;

    for(int i = 0; i < 10; i++){
        sum += remains[i] * remains[i];
    }

    cout << sum;

    return 0;
}