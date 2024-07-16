#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    float a, b = 0;
    cin >> a >> b;
    float calc = (a+b)/(a-b);
    printf("%.2f", calc);
    return 0;
}