#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;

    string strs[n];

    for(int i = 0; i < n; i++){
        cin >> strs[i];
    }

    char c;
    cin >> c;

    int cnt = 0;
    int total = 0;

    for(int i = 0; i < n; i++){
        if(strs[i][0] == c){
            cnt++;
            total += strs[i].length();
        }
    }

    printf("%d %.2f", cnt, float(total/cnt));

    return 0;
}