#include<stdio.h>
#include<string>

using namespace std;

typedef struct{
    int x;
    int y;
} Pos;

class Piece{
    private:
        Pos pos;
    public:
        string name;
        int* possibleMoves(){
            int arr[5];  //example func
            return arr;
        }
        
};