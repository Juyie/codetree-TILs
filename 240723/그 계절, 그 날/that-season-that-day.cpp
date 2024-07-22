#include <iostream>
using namespace std;

int findWeather(int y, int m, int d){
    if((y % 4 == 0 && y % 100 != 0) || (y % 4 == 0 && y % 100 == 0 && y % 400 == 0)){
        if(m == 2 && d > 29){
            return -1;
        }
        else if((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d > 31){
            return -1;
        }
        else if((m == 4 || m == 6 || m == 9 || m == 11) && d > 30){
            return -1;
        }
    }
    else{
        if((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d > 31){
            return -1;
        }
        else if((m == 4 || m == 6 || m == 9 || m == 11) && d > 30){
            return -1;
        }
        else if(m == 2 && d > 28){
            return -1;
        }
    }
    return m;
}

int main() {
    // 여기에 코드를 작성해주세요.
    int y, m, d;
    cin >> y >> m >> d;

    int result = findWeather(y, m, d);
    if(result == -1){
        cout << -1;
    }
    else if(3 <= result && result <= 5){
        cout << "Spring";
    }
    else if(6 <= result && result <= 8){
        cout << "Summer";
    }
    else if(9 <= result && result <= 11){
        cout << "Fall";
    }
    else{
        cout << "Winter";
    }

    return 0;
}