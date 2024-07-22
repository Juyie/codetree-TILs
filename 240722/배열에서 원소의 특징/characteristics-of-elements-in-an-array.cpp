#include <iostream>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int nums[10] = {0, };
    for(int i = 0; i < 10; i++){
        cin >> nums[i];
    }

    for(int j = 0; j < 10; j++){
        if(nums[j] % 3 == 0){
            cout << nums[j-1];
            break;
        }
    }
    return 0;
}