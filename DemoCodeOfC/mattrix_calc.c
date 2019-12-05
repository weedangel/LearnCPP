#include <stdio.h>

#define MAXSTACKLENGTH 81

int jiuGongArray[][9] =
{
    {0,0,0,0,4,0,0,3,2},
    {4,0,0,0,0,1,0,0,0},
    {5,3,0,6,0,0,0,0,7},
    {3,0,0,5,1,0,7,0,0},
    {0,0,5,0,3,0,2,0,0},
    {0,0,9,0,7,4,0,0,3},
    {1,0,0,0,0,9,0,4,6},
    {0,0,0,1,0,0,0,0,9},
    {8,9,0,0,6,0,0,0,0}
};

int dataNeedToBeInsert[][9] =
{
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9}
};

//����ջ��Ԫ�Ľṹ
typedef struct
{
    int xPosition;
    int yPosition;
    int jiuGongGePosition;
    int num;
}node;

//����ջ����
node stack[MAXSTACKLENGTH];

//���m*n�ľ���
void PrintArray(int *ptr, int m, int n)
{
    int i, j;
    int data;
    int temp;
    
    temp = n - 1;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            data = *(ptr+i*n+j);
            printf("%d ",data);
			/*
            if(j == temp)
            {
                printf("test");
            }
			*/
        }
		printf("\n");
    }
}

//�ɸ����ľŹ�����󣬲��ҿ�ȱ������
void FindDataToBeInsert(void)
{
    int i, j;
    int x, y;
    
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(jiuGongArray[i][j] != 0)
            {
                x = (i / 3) * 3 + j / 3;
                y = jiuGongArray[i][j] - 1;
                dataNeedToBeInsert[x][y] = 0;
            }
        }
    }
    PrintArray(dataNeedToBeInsert, 9, 9)
}

//��ʵ�Ƿ������������
int CheckEnd(void)
{
    int i, j, sum;
    
    for(i = 0; i < 9; i++)
    {
        sum = 0;
        for(j = 0; j < 9; j++)
        {
            sum += jiuGongArray[i][j];
        }
        if(sum != 45)
        {
            return -1;
        }
    }
    
    for(j = 0; j < 9; j++)
    {
        sum = 0;
        for(i = 0; i < 9; i++)
        {
            sum += jiuGongArray[i][j];
        }
        if(sum != 45)
        {
            return -1;
        }
    }
    return 0;
}

//�Ӿ���dataNeedToBeInsert[][]�в�����һ������
int FindNextData(int m, int n, int *xPosition, int *yPosition)
{
    int state = 0;
    
    if(n > 8)
    {
        n = 0;
        m++;
    }
    
    if(m > 8)
    {
        state = CheckEnd();
        if(state != 0)
            return -1;
        else
            return 1;
    }
    
    while(dataNeedToBeInsert[m][n] == 0)
    {
        if(n < 8)
            n++;
        else
        {
            n = 0;
            m++;
            if(m > 8)
            {
                state = CheckEnd();
                if(state != 0)
                    return -1;
                else
                    return 1;
            }
        }
    }
    *xPosition = m;
    *yPosition = n;
    
    return 0;
}

//��ʵԪ�ض�Ӧ���к����Ƿ�����ͬ������
int CheckLine(int m, int n, int num)
{
    int i;
    
    for(i = 0;i < 9; i++)
    {
        if(jiuGongArray[m][i] == num)
            return -1;
    }
    for(i = 0; i < 9; i++)
    {
        if(jiuGongArray[i][n] == num)
            return -1;
    }
    
    return 0;
}

//��ʵ�Ƿ�������ջ����
int CheckCanPush(int m, int n, int *position)
{
    int start = *position;
    int i, temp1, temp2, temp3, temp4;
    int num;
    
    temp1 = (m / 3) * 3;
    temp2 = (m % 3) * 3;
    num = dataNeedToBeInsert[m][n];
    for(i = start; i < 10; i++)
    {
        temp3 = temp1 + (start - 1) / 3;
        temp4 = temp2 + (start - 1) % 3;
        if(jiuGongArray[temp3][temp4] != 0)
        {
            start++;
            continue;
        }
        
        if(CheckLine(temp3, temp4, num) != 0)
        {
            start++;
            continue;
        }
        else
        {
            *position = start;
            
            return 0;
        }
    }
    
    return -1;
}

//��ջ
int Push(int *top,int xPosition,int yPosition,int jiuGongGePosition,int num)
{
    if(*top >= MAXSTACKLENGTH)
    {
        printf("Reach stack top!\n");
        
        return -1;
    }
    else
    {
        (*top)++;
        stack[*top].xPosition = xPosition;
        stack[*top].yPosition = yPosition;
        stack[*top].jiuGongGePosition = jiuGongGePosition;
        stack[*top].num = num;
        
        return 0;
    }
}

//��ջ
int Pop(int *top, int *xPosition, int *yPosition, int *jiuGongGePosition, int *num)
{
    if(*top == -1)
    {
        printf("Reach stack bottom!\n");
        
        return -1;
    }
    else
    {
        *xPosition = stack[*top].xPosition;
        *yPosition = stack[*top].yPosition;
        *jiuGongGePosition = stack[*top].jiuGongGePosition;
        *num = stack[*top].num;
        (*top)--;
        
        return 0;
    }
}

int main(void)
{
    int end = 0;
    int line = 0;
    int row = 0;
    int top = -1;
    int positionInUnitArray = 1;
    int state = 0;
    int num;
    
    FindDataToBeInsert();
	printf("source data:\n");
    PrintArray(jiuGongArray, 9, 9);
    
    while(end != 1)
    {
        state = FindNextData(line, row, &line, &row);
        if(state == 0)
        {
            state = CheckCanPush(line, row, &positionInUnitArray);
            if(state == 0)
            {
                state = Push(&top, line, row, positionInUnitArray, dataNeedToBeInsert[line][row]);
                if(state == 0)
                {
                    jiuGongArray[(line / 3) * 3 + (positionInUnitArray - 1) / 3][(line%3) * 3 + (positionInUnitArray - 1) % 3] = dataNeedToBeInsert[line][row];
                    row++;
                    positionInUnitArray = 1;
                }
                else
                    end = 1;
            }
            else
            {
                state = Pop(&top, &line, &row, &positionInUnitArray, &num);
                if(state == 0)
                {
                    jiuGongArray[(line / 3) * 3 + (positionInUnitArray-1) / 3][(line % 3) * 3 + (positionInUnitArray - 1) % 3] = 0;
                    positionInUnitArray++;
                }
                else
                    end = 1;
            }
        }
        else if(state == 1)
        {
            printf("\ncalc result:\n");
            PrintArray(jiuGongArray, 9, 9);
            end = 1;
        }
        else
        {
            printf("Some error occur!\n");
            end = 1;
        }
    }
    
    return 0;
}
