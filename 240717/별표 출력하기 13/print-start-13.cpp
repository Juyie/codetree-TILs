#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;
    string stars[n];

    for(int i = 0; i < n; i++){
        if(i % 2 == 0){
            string star = "";
            for(int j = i/2; j < n; j++){
                cout << "* ";
                star.append("* ");
            }
            stars[i] = star;
            cout << endl;
        }
        else{
            string star = "";
            for(int j = n - i/2; j <= n; j++){
                cout << "* ";
                star.append("* ");
            }
            stars[i] = star;
            cout << endl;
        }
    }
    for(int i = n - 1; i >= 0; i--){
        cout << stars[i].c_str() << endl;
    }
    return 0;
}