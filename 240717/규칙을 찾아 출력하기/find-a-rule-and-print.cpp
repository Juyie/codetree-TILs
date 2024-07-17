#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;
    
    for(int i = 0; i < n; i++){
        cout << "* ";
    }
    cout << endl;

    for(int i = 1; i < n-1; i++){
        for(int j = 0; j < n; j++){
            if(j < i)
                cout << "* ";
            else if(j == n-1)
                cout << "* ";
            else
                cout << "  ";
        }
        cout << endl;
    }

    for(int i = 0; i < n; i++){
        cout << "* ";
    }

    return 0;
}