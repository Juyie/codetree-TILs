#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0; 
    cin >> n;
    int nums[n] = {0, };

    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }

    for(int j = n-1; j >=0; j--){
        if(nums[j] % 2 == 0) cout << nums[j] << " ";
    }

    return 0;
}