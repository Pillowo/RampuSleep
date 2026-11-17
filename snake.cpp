#include <iostream>
#include <conio.h>
#include<windows.h>
using namespace std;
#define row 32
#define col 32
int x,y,fruitX,fruitY;
int score=0;
int tailX[1000],tailY[1000];
int tailLength=0;
bool gameover;
enum Direction{
    STOP=0,LEFT,RIGHT,UP,DOWN
};
bool tailcollision(){
    for(int i=0;i<tailLength;i++){
        if(tailX[i]==x && tailY[i]==y)
            return true;
    }
    return false;
}
Direction dir;    
void setup(){
    gameover=false;
    x=col/2;
    y=row/2;
    fruitX=rand()%col;
    fruitY=rand()%row;
}
void input(){
    if (kbhit()){
        char c=getch();
        c=tolower(c);
        switch(c){
            case 'a':
                if(dir!=RIGHT)
                    dir=LEFT;
                break;
            case 'd':
                if(dir!=LEFT)
                    dir=RIGHT;
                break;
            case 'w':
                if(dir!=DOWN)
                    dir=UP;
                break;
            case 's':
                if(dir!=UP)
                    dir=DOWN;
                break;
            case 'x':
                gameover=true;
                break;
            default:
                break;
        }
    }  
}
void logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<tailLength;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    } 
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x==fruitX && y==fruitY){
        fruitX=rand()%col;
        fruitY=rand()%row;
        score+=10;
        tailLength++;
    }
    if(x<=0 || x>=col-1 || y<=-1 || y>=row-1){
        gameover=true;
    }
    if(tailcollision()){
        gameover=true;
    }
}
void render(){
    CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    for(int i=0; i<row; i++){
        cout << "#";
    }
    cout << "\n";
    for(int i=0; i<row-2; i++){
        for(int j=0; j<col; j++){
            if(j==0 || j==col-1)
                cout << "#";
            else if(i==y && j==x){
                cout << "O";
            }
            else if(i==fruitY && j==fruitX)
                cout << "F";
            else{
                bool tailPrinted=false;
                for(int k=0;k<tailLength;k++){
                    if(tailX[k]==j && tailY[k]==i){
                        cout << "o";
                        tailPrinted=true;
                    }
                }
                if(!tailPrinted)
                    cout << " ";
            }
        
        }
        cout << "\n";
    }
    for(int i=0; i<row; i++){
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score;
}

int main() {
    int speed=100;
    setup();
    while(!gameover){
        if (dir == LEFT || dir == RIGHT){
          Sleep(5);
        }

Sleep(speed);

if (dir == UP || dir == DOWN){
  Sleep(60);
    }
        render();
        input();
        logic();
        speed = 100 - score / 2;
        if(speed < 40)
            speed = 40;
    }
    return 0;
}
