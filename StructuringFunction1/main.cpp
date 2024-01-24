#include <iostream>
using namespace std;

float distance(float velocity, float acceleration, float time_elapsed);

int main() {
    cout << distance(3, 4, 5) << endl;
    cout << distance(0.7, 2.1, 5.4) << endl;
    return 0;   
}