#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
#define MAX_VALUE 1000



typedef enum{false,true} bool;
typedef struct square{
    int value; // between 0-1000
    unsigned int sum;

}square;

//put random values between 0-1000 in each square
void createWorld(square[][SIZE]);

//deals with connors - sends their neighbors to the func function
void connors(int row ,int col,square[][SIZE]);

//deals with edges - sends their neighbors to the func function
void edges(int row,int col,square[][SIZE]);

//deals with normal squares - sends their neighbors to the func function
void normal(int row,int col,square[][SIZE]);

//updates the sum of the current square
void func(int row,int col,square[][SIZE],int);

int main() {
    srand(time(NULL));

    square world[SIZE][SIZE];
    createWorld(world);
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            printf("%4d|", world[i][j].value);
        }
        printf("\n");
    }

    world[0][0].sum = 0;
    connors(0,0,world);
    printf("%d",world[SIZE-1][SIZE-1].sum);

    return 0;
}


void createWorld(square world[][SIZE])
{
    square* curr;
    int i;

    for(i=0,curr=*world;i<(SIZE*SIZE);i++,curr++)
    {
        curr->value = rand()%MAX_VALUE;
        curr->sum = SIZE*SIZE*MAX_VALUE;
    }

}
void connors(int rowIndex,int colIndex,square world[][SIZE])
{
    int add2row,add2col;

    add2row = (rowIndex==0)?1:-1; // if row = 0 we access the neighbors from down and if row  = size -1 we access the neighbors from up.
    add2col = (colIndex==0)?1:-1; // if col = 0 we access the neighbors from right and if col  = size -1 we access the neighbors from left.

    // 3 neighbors to connor square
    func(rowIndex+add2row,colIndex+add2col,world,(world[rowIndex][colIndex]).sum);
    func(rowIndex+add2row,colIndex,world,(world[rowIndex][colIndex]).sum);
    func(rowIndex,colIndex+add2col,world,(world[rowIndex][colIndex]).sum);


}
void edges(int rowIndex,int colIndex,square world[][SIZE])
{
    int add2row, add2col, i , j;

    if(rowIndex%(SIZE-1)==0) // top/bottom edge
    {
        add2row = (rowIndex == 0)?1:-1; // if row = 0 we access the neighbors from down and if row  = size -1 we access the neighbors from up.

        // go over its neighbors
        for(i = rowIndex;i!=rowIndex+(2*add2row);i+=add2row)
        {
            for(j=colIndex-1;j<=colIndex+1;j++)
            {
                if(!(i==rowIndex&&j==colIndex)) // if (i,j) is not the square we are in now do the if
                {
                    func(i,j,world,world[rowIndex][colIndex].sum);
                }
            }
        }

     }


    if(colIndex%(SIZE-1)==0) // left/right edge
    {
        add2col = (colIndex==0)?1:-1; // if col = 0 we access the neighbors from right and if col  = size -1 we access the neighbors from left.


        // go over its neighbors
        for(i = rowIndex-1;i<=rowIndex+1;i++)
        {
            for(j=colIndex;j!=colIndex+(2*add2col);j+=add2col)
            {
                if(!(i==rowIndex&&j==colIndex)) // if (i,j) is not the square we are in now do the if
                {
                    func(i,j,world,world[rowIndex][colIndex].sum);
                }
            }
        }

}

}
void normal(int rowIndex,int colIndex,square world[][SIZE])
{
    int i,j;

    // go over its neighbors
    for(i = rowIndex-1;i<=rowIndex+1;i++)
    {
        for(j=colIndex-1;j<=colIndex+1;j++)
        {
            if(!(i==rowIndex&&j==colIndex)) // if (i,j) is not the square we are in now do the if
            {
                func(i,j,world,world[rowIndex][colIndex].sum);
            }
        }
    }
}


void func(int rowIndex,int colIndex,square world[][SIZE], int preSum)
{
    int currSum, tempSum;

    currSum = world[rowIndex][colIndex].sum;
    tempSum = world[rowIndex][colIndex].value+preSum;

    if(tempSum < currSum)
    {
        world[rowIndex][colIndex].sum = tempSum;

        if(rowIndex%(SIZE-1)==0&&colIndex%(SIZE-1)==0)
        {
            connors(rowIndex,colIndex,world);
            return;
        }
        if(rowIndex%(SIZE-1)==0||colIndex%(SIZE-1)==0)
        {
            edges(rowIndex,colIndex,world);
            return;
        }

        normal(rowIndex,colIndex,world);
        return;
    }
}
