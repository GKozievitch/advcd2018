#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert(int *array, int index)
{
	int temp=0,order=1;
	while(index>-1)
	{
		temp+=(array[index]-48)*order;
		order*=10;
		index--;
	}
	return temp;
}

void modifyMatrix(int matrix[1001][1001], int smx , int smy, int bgx, int bgy)
{
	int line,column;
	for(line=smy+1;line<=bgy;line++)
	{
		for(column=smx+1; column<=bgx; column++)
		{
				matrix[line][column]+=1;
		}
	}
}

int collisionCounter(int matrix[1001][1001])
{
	int count,x,y;
	for(x=0;x<=1000;x++)
	{
		for(y=0;y<=1000;y++)
		{
			if(matrix[x][y]>1)
				count++;
		}
	}
	return count;
}

void cleanMatrix(int matrix[1001][1001])
{
	int x,y;
	for(x=0;x<=1000;x++)
	{for(y=0;y<=1000;y++){matrix[x][y]=0;}}
}
int main()
{
	int i,b,smallx,smally,bigx,bigy,collisions;
	int matrix[1001][1001];
	int tempnum[4];
	char line[30];
	FILE *inputfile;
	inputfile=fopen("./input","r");
	cleanMatrix(matrix);
	while(fgets(line,30,inputfile))
	{
		for(i=0;line[i]!='\n';i++)
		{
			//extract coordinates
			if (line[i]=='@')
			{

				b=0;
				i+=2;
				while(line[i]!=',')
				{
					tempnum[b]=(int)line[i];
					i++;
					b++;
				}
				smallx=convert(tempnum,b-1);

				i++;
				b=0;
				while(line[i]!=':')
				{
					tempnum[b]=(int)line[i];
					i++;
					b++;
				}
				smally=convert(tempnum,b-1);

				b=0;
				i+=2;
				while(line[i]!='x')
				{
					tempnum[b]=(int)line[i];
					i++;
					b++;
				}
				bigx=convert(tempnum,b-1);

				i++;
				b=0;
				while(line[i]!='\n')
				{
					tempnum[b]=(int)line[i];
					i++;
					b++;
				}
				bigy=convert(tempnum,b-1);
				i--; //so the for loop sees the \n and jumps out
			}
		}
		//corrects the coordinates of the bottom right
		bigy+=smally;
		bigx+=smallx;
		//add the area specified in the matrix
		modifyMatrix(matrix,smallx,smally,bigx,bigy);
	}
	//count the collisions
	collisions=collisionCounter(matrix);
	printf("%d\n",collisions);
	return fclose(inputfile);
}


