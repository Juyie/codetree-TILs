#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string a;
    string b;
    cin >> a >> b;

    int i = 0;
    while(i != a.length()){
        if('a' <= a[i] && a[i] <= 'z'){
            a.erase(i, 1);
        }
        else{
            i++;
        }
    }

    i = 0;
    while(i != b.length()){
        if('a' <= b[i] && b[i] <= 'z'){
            b.erase(i, 1);
        }
        else{
            i++;
        }
    }

    cout << stoi(a) + stoi(b);

    return 0;
}