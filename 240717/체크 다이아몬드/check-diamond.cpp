#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;

    for(int i = n - 1; i > 0; i--){
        for(int j = 1; j <= i; j++) cout << " ";
        for(int j = i; j < n; j++) cout << "* ";
        cout << "\n";
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j < i; j++) cout << " ";
        for(int j = i; j <= n; j++) cout << "* ";
        cout << "\n";
    }
    return 0;
}