#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int x, y;
} Pos;

int main(){
    vector<Pos> numHolder = {Pos(1,3), Pos(2,4)};
    numHolder.push_back(Pos(5,6));
    for(int i = 0; i < numHolder.size(); i++){
        cout << numHolder[i].x << numHolder[i].y << endl;
    }
    return 0;
}