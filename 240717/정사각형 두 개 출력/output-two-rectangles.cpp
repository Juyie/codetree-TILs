#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;
    string stars = "";

    for(int i = 0; i < n; i++){
        stars += "*";
    }

    for(int i = 0; i < n; i++){
        cout << stars << endl;
    }

    cout << endl;

    for(int i = 0; i < n; i++){
        cout << stars << endl;
    }

    return 0;
}