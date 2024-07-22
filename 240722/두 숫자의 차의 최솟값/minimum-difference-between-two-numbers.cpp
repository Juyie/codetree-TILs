#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0;
    cin >> n;
    int nums[n] = {0,};

    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }

    int min = 100;
    for(int j = n - 1; j > 0; j--){
        int diff = nums[j] - nums[j-1];
        if(diff < min) min = diff;
    }

    cout << min;

    return 0;
}