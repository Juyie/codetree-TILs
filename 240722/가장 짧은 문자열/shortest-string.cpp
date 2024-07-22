#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    string s1 = "";
    string s2 = "";
    string s3 = "";

    cin >> s1 >> s2 >> s3;

    int max = 0;
    int min = 20;

    if(s1.length() > max) max = s1.length();
    if(s1.length() < min) min = s1.length();
    if(s2.length() > max) max = s2.length();
    if(s2.length() < min) min = s2.length();
    if(s3.length() > max) max = s3.length();
    if(s3.length() < min) min = s3.length();

    cout << max-min;

    return 0;
}