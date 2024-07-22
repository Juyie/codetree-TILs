#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    char s1[100] = "";
    char s2[100] = "";

    cin.getline(s1, 100);
    cin.getline(s2, 100);

    for(int i = 0; i < 100; i++){
        if(s1[i] == '\0') break;
        if(s1[i] != ' ') cout << s1[i];
    }
    for(int i = 0; i < 100; i++){
        if(s2[i] == '\0') break;
        if(s2[i] != ' ') cout << s2[i];
    }

    return 0;
}