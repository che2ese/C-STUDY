#include <iostream>
using namespace std;

void Swap(int& a, int& b){ // 참조
    int temp = a;
    a = b;
    b = temp;
}

// 오름차순
void Sort(int* numbers, int count){
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count - 1 - i; j++){
            if(numbers[j] > numbers[j + 1]){
                Swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}
void ChooseLotto(int* numbers){
    int count = 0;
    while(count != 6){
        int randValue = 1 + rand() % 45;

        // 이미 찾은 값인지?
        bool found = false;

        for(int i = 0; i < count; i++){
            if(numbers[i] == randValue){
                found = true;
                break;
            }
        }
        if(!found){
            numbers[count] = randValue;
            count++;
        }
    }
    Sort(numbers, 6);
}

int main(){
    srand((unsigned)time(0));

    int lotto[6]; 
    ChooseLotto(lotto);
    
    for(int i = 0; i < 6; i++){
        cout << lotto[i] << " ";
    }
}