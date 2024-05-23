#include <iostream>
#include <queue>
#include <utility>
#include <API.h>
using namespace std;


typedef struct cell{
/* val denotes cell value
   (x,y) denotes cell coordinates
   r,l,t,b values denote presence of walls
   if value equals 1 then wall is present */
    int val;
    int x;
    int y;
    int r;
    int l;
    int t;
    int b;
}Cell;

void printMaze(Cell ** maze, int n){
    int i, j;
    for(i=(n-1); i>=0; i--){
        for(j=0; j<n; j++){
            cout << maze[i][j].val << "  ";
        }
        cout << "\n";
    }
}

Cell ** initMaze(int n){
    Cell ** maze = (Cell **)malloc(n*sizeof(Cell*));
    int i, j;
    for(i=0; i<n; i++){
        maze[i] = (Cell*)malloc(n*sizeof(Cell));
        for(j=0; j<n; j++){
            maze[i][j].val = 0;
            maze[i][j].x = i;
            maze[i][j].y = j;
            if(i==0){
                if(j==0){
                    maze[i][j].t = 0;
                    maze[i][j].l = 1;
                    maze[i][j].b = 1;
                    maze[i][j].r = 0;
                }
                else if(j==(n-1)){
                    maze[i][j].t = 0;
                    maze[i][j].l = 0;
                    maze[i][j].b = 1;
                    maze[i][j].r = 1;
                }
                else{
                    maze[i][j].t = 0;
                    maze[i][j].l = 0;
                    maze[i][j].b = 1;
                    maze[i][j].r = 0;
                }
            }
            else if(i==(n-1)){
                if(j==0){
                    maze[i][j].t = 1;
                    maze[i][j].l = 1;
                    maze[i][j].b = 0;
                    maze[i][j].r = 0;
                }
                else if(j==(n-1)){
                    maze[i][j].t = 1;
                    maze[i][j].l = 0;
                    maze[i][j].b = 0;
                    maze[i][j].r = 1;
                }
                else{
                    maze[i][j].t = 1;
                    maze[i][j].l = 0;
                    maze[i][j].b = 0;
                    maze[i][j].r = 0;

                }
            }
            else{
                if(j==0){
                    maze[i][j].t = 0;
                    maze[i][j].l = 1;
                    maze[i][j].b = 0;
                    maze[i][j].r = 0;
                }
                else if(j==(n-1)){
                    maze[i][j].t = 0;
                    maze[i][j].l = 0;
                    maze[i][j].b = 0;
                    maze[i][j].r = 1;
                }
                else{
                    maze[i][j].t = 0;
                    maze[i][j].l = 0;
                    maze[i][j].b = 0;
                    maze[i][j].r = 0;
                }
            }
        }
    }
    return maze;
}

int isValid(int n, int a,int b,int c,int d,Cell ** maze){ //checks if we can move from (c,d) to (a,b) in current maze
    if(a<0 || a>=n || b<0 || b>=n){
        return 0;
    }
    else{
        if(a==c){
            if(b==(d-1)){
                if(maze[a][b].r==1){
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                if(maze[a][b].l==1){
                    return 0;
                }
                else{
                    return 1;
                }
            }
        }
        else{
            if(a==(c+1)){
                if(maze[a][b].b==1){
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                if(maze[a][b].t==1){
                    return 0;
                }
                else{
                    return 1;
                }
            }            
        }
    }

}

void floodfill (Cell ** maze, int n){
    queue <pair<int,int>> q;
    q.push(make_pair(n/2-1,n/2-1));
    q.push(make_pair(n/2-1,n/2));
    q.push(make_pair(n/2,n/2-1));
    q.push(make_pair(n/2,n/2));
    int ** visited = (int**)malloc(n*sizeof(int*));
    int i, j;
    for(i=0; i<n; i++){
        visited[i] = (int *)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            visited[i][j] = 0;
        }
    }
    visited[n/2-1][n/2-1] = 1;
    visited[n/2-1][n/2] = 1;
    visited[n/2][n/2-1] = 1;
    visited[n/2][n/2] = 1;
    int cx, cy;
    while(q.size()!=0){
        cx = q.front().first;
        cy = q.front().second;

        q.pop();
        if(isValid(n,cx-1,cy,cx,cy,maze) && visited[cx-1][cy]==0){
            q.push(make_pair(cx-1,cy));
            visited[cx-1][cy] = 1;
            maze[cx-1][cy].val = maze[cx][cy].val + 1;

        }
        if(isValid(n,cx+1,cy,cx,cy,maze) && visited[cx+1][cy]==0){
            q.push(make_pair(cx+1,cy));
            visited[cx+1][cy] = 1;
            maze[cx+1][cy].val = maze[cx][cy].val + 1;

        }
        if(isValid(n,cx,cy-1,cx,cy,maze) && visited[cx][cy-1]==0){
            q.push(make_pair(cx,cy-1));
            visited[cx][cy-1] = 1;
            maze[cx][cy-1].val = maze[cx][cy].val + 1;

        }
        if(isValid(n,cx,cy+1,cx,cy,maze) && visited[cx][cy+1]==0){
            q.push(make_pair(cx,cy+1));
            visited[cx][cy+1] = 1;
            maze[cx][cy+1].val = maze[cx][cy].val + 1;

        }
    }

    
    free(visited);
}

int updateMazeWalls(Cell ** maze, int curr_x, int curr_y, int n, char orient){
    int r, l, t, b;
    r = l = t = b = 0;
    if(orient == 't'){
        if(API::wallFront()){
            t = 1;            
        }
        if(API::wallLeft()){
            l = 1;
        }
        if(API::wallRight()){
            r = 1;
        }
    }
    else if(orient == 'l'){
        if(API::wallFront()){
            l = 1;            
        }
        if(API::wallLeft()){
            b = 1;
        }
        if(API::wallRight()){
            t = 1;
        }
    }
    else if(orient == 'b'){
        if(API::wallFront()){
            b = 1;            
        }
        if(API::wallLeft()){
            r = 1;
        }
        if(API::wallRight()){
            l = 1;
        }
    }
    else if(orient == 'r'){
        if(API::wallFront()){
            r = 1;            
        }
        if(API::wallLeft()){
            t = 1;
        }
        if(API::wallRight()){
            b = 1;
        }
    }
    
    if(maze[curr_x][curr_y].r==r && maze[curr_x][curr_y].l==l && maze[curr_x][curr_y].t==t && maze[curr_x][curr_y].b==b){
        return 0;
    }
    else{
        maze[curr_x][curr_y].l = l;
        if(curr_y>0){
            maze[curr_x][curr_y-1].r = l;
        }
        maze[curr_x][curr_y].r = r;
        if(curr_y<(n-1)){
            maze[curr_x][curr_y+1].l = r;
        }
        maze[curr_x][curr_y].t = t;
        if(curr_x<(n-1)){
            maze[curr_x+1][curr_y].b = t;
        }
        maze[curr_x][curr_y].b = b;
        if(curr_x>0){
            maze[curr_x-1][curr_y].t = b;
        }
        return 1;

    }
} 

char minNeighbour(Cell ** maze, int curr_x, int curr_y, int n){
    int min = maze[curr_x][curr_y].val;
    char k;
    if(isValid(n,curr_x-1,curr_y,curr_x,curr_y,maze) && (maze[curr_x-1][curr_y].val<min)){
        min = maze[curr_x-1][curr_y].val;
        k = 'b';
    }

    if(isValid(n,curr_x+1,curr_y,curr_x,curr_y,maze)&&(maze[curr_x+1][curr_y].val<min)){
        min = maze[curr_x+1][curr_y].val;
        k = 't';
    }

    if(isValid(n,curr_x,curr_y-1,curr_x,curr_y,maze)&&(maze[curr_x][curr_y-1].val<min)){
        min = maze[curr_x][curr_y-1].val;
        k = 'l';
    }

    if(isValid(n,curr_x,curr_y+1,curr_x,curr_y,maze)&&(maze[curr_x][curr_y+1].val<min)){
        min = maze[curr_x][curr_y+1].val;
        k = 'r';
    }

    return k;
}

void Run(Cell ** maze,int n,char orient){
    int curr_x = 0;
    int curr_y = 0;
    while(maze[curr_x][curr_y].val!=0){
        
        int u = updateMazeWalls(maze,curr_x,curr_y,n,orient);
        if(u==1){
            floodfill(maze,n);
        }
        char c = minNeighbour(maze,curr_x,curr_y,n);
        if (c == 'b'){
            if(orient == 't'){
                API::turnLeft();
                API::turnLeft();
            }
            else if(orient == 'l'){
                API::turnLeft();
            }
            else if(orient == 'r'){
                API::turnRight();
            }
            API::moveForward();
            curr_x = curr_x - 1;
            orient = 'b';   
        }
        else if (c == 'r'){
            if(orient == 't'){
                API::turnRight();
            }
            else if(orient == 'l'){
                API::turnLeft();
                API::turnLeft();
            }
            else if(orient == 'b'){
                API::turnLeft();
            }
            API::moveForward();
            curr_y = curr_y + 1;
            orient = 'r';   
        }
        else if (c == 't'){
            if(orient == 'b'){
                API::turnRight();
                API::turnRight();
            }
            else if(orient == 'l'){
                API::turnRight();
            }
            else if(orient == 'r'){
                API::turnLeft();
            }
            API::moveForward();
            curr_x = curr_x + 1;
            orient = 't';   
        }
        else{
            if(orient == 'b'){
                API::turnRight();
            }
            else if(orient == 't'){
                API::turnLeft();
            }
            else if(orient == 'r'){
                API::turnLeft();
                API::turnLeft();
            }
            API::moveForward();
            curr_y = curr_y - 1;
            orient = 'l'; 
        }
        
    }

}



int main(){
    char orient = 't';         
    int n;
    cin >> n;
    Cell ** maze = initMaze(n);
    floodfill(maze,n);
    int numruns = 1;

    while(numruns--){
        Run(maze,n,orient);        
    }
    printMaze(maze, n);
    
    return 0;
}
