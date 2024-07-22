#include <iostream>
using namespace std;

int findGCD(int a, int b);
int findLCM(int a, int b);

int main() {
    // 여기에 코드를 작성해주세요.
    int n, m = 0;
    cin >> n >> m;

    cout << findLCM(n, m);

    return 0;
}

int findGCD(int a, int b){
    if(b == 0)
        return a;
    else
        return findGCD(b, a % b);
}

int findLCM(int a, int b){
    int gcd = findGCD(a, b);
    return a*b/gcd;
}