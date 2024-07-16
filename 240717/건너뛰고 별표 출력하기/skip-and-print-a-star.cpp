#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;
    string stars = "";

    for(int i = 0; i < n; i++){
        stars += "*";
        cout << stars << endl << endl;
    }

    for(int i = 0; i < n-1; i++){
        stars.pop_back();
        cout << stars << endl << endl;
    }

    return 0;
}