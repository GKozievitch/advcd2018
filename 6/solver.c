#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTNAME "./input"
#define COORDINATE_AMMOUNT 80
#define MATRIX_SIZE 401
#define MAGIC_ROUNDS 200



void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int x,y;
	for(x=0;x<=MATRIX_SIZE;x++)
	{for(y=0;y<=MATRIX_SIZE;y++){
		printf("%d",matrix[x][y]);
	}
	printf("\n");}
}

int convert(char* array, int index)
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

void copyMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE],int dummyMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int i;
	for(i=1;i<MATRIX_SIZE;i++)
	{
		memcpy(matrix[i],dummyMatrix[i],sizeof(matrix[0]));
	}
}

void insertStartingPoints(int matrix[MATRIX_SIZE][MATRIX_SIZE],int coordinates[COORDINATE_AMMOUNT][2], int coordinateIndex)
{
	int x,y;

	while(coordinateIndex>0)
	{
		x=coordinates[coordinateIndex][0];
		y=coordinates[coordinateIndex][1];

		matrix[x][y] = coordinateIndex;
		coordinateIndex--;
	}

}

int extractX(char* coordinatesChar)
{
	int i=0;
	char string[5];
	//copy until finds the comma (44)
	while(coordinatesChar[i]!=44)
	{
		string[i]=coordinatesChar[i];
		i++;
	}
	i--;
	return convert(string,i);
}

int extractY(char* coordinatesChar)
{
	int i=0,j=0;
	char string[5];
	//finds the comma
	while(coordinatesChar[i]!=44)
	{
		i++;
	}
	//there is a space between number and comma
	i+=2;
	//copy until finds newline
	while(coordinatesChar[i]!='\n')
	{
		string[j]=coordinatesChar[i];
		i++;
		j++;
	}
	j--;
	return convert(string,j);
}

void cleanMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int x,y;
	for(x=0;x<MATRIX_SIZE;x++)
	{for(y=0;y<MATRIX_SIZE;y++){matrix[x][y]=0;}}
}

void expandRound(int matrix[MATRIX_SIZE][MATRIX_SIZE],int dummyMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int x,y,n,s,l,o;
	int a,b, opposite;

	for(x=1;x<MATRIX_SIZE;x++)
	{
		for (y=1;y<MATRIX_SIZE;y++)
		{

			if(matrix[x][y]==0)
			{
				n=matrix[x][y+1];
				s=matrix[x][y-1];
				l=matrix[x+1][y];
				o=matrix[x-1][y];
				if(n==0)
				{
					if(l==0)
					{
						if((o==0)||(s==0)){dummyMatrix[x][y]= o+s;}
						else if(o==s){dummyMatrix[x][y]= s;}
						else{goto invalid;}
					}
					else if(o==0)
					{
						if((l==0)||(s==0)){dummyMatrix[x][y]= l+s;}
						else if(l==s){dummyMatrix[x][y]= s;}
						else{goto invalid;}
					}
					else{goto invalid;}
				}
				else if(s==0)
				{
					if(l==0)
					{
						if(o==0){dummyMatrix[x][y]= n;}
						else if(o==n){dummyMatrix[x][y]= n;}
						else{goto invalid;}
					}
					else if(o==0)
					{
						if(l==n){dummyMatrix[x][y]= n;}
						else{goto invalid;}
					}
					else{goto invalid;}	
				}
				else
				{
					invalid:
					//if no square in the crux is zero, there must be a competion
					dummyMatrix[x][y]=-1;
				}
			}

		}
	}
}

int main()
{

	int i,j,k,coordinateIndex;
	int coordinates[COORDINATE_AMMOUNT][2];
	int totalArea[COORDINATE_AMMOUNT];
	int matrix[MATRIX_SIZE][MATRIX_SIZE];
	int dummyMatrix[MATRIX_SIZE][MATRIX_SIZE];
	char a;
	char coordinatesChar[20];
	FILE *inputfile;

	inputfile=fopen(INPUTNAME,"r");
	cleanMatrix(matrix);
	cleanMatrix(dummyMatrix);
	for(i=0;i<COORDINATE_AMMOUNT;i++)
	{
		totalArea[i]=0;
	}

	coordinateIndex=1;
	//reads the file and feeds the matrix of coordinates
	while(fgets(coordinatesChar,20,inputfile))
	{
		coordinates[coordinateIndex][0] = extractX(coordinatesChar);
		coordinates[coordinateIndex][1] = extractY(coordinatesChar);
		coordinateIndex++;
	}

	fclose(inputfile);

	insertStartingPoints(matrix,coordinates,coordinateIndex-1);

	copyMatrix(dummyMatrix,matrix);
	//printMatrix(dummyMatrix);
	//printMatrix(matrix);

	//infection
	for(i=0;i<MAGIC_ROUNDS;i++)
	{
		//printf("\n");
		expandRound(matrix,dummyMatrix);
		copyMatrix(matrix,dummyMatrix);
		//printMatrix(matrix);
	}

	//run on the edges and mark those who are infinite
	for(i=1;i<MATRIX_SIZE;i++)
	{
		totalArea[matrix[i][1]] = -1;
	}
	for(i=1;i<MATRIX_SIZE;i++)
	{
		totalArea[matrix[i][MATRIX_SIZE-1]] = -1;
	}
	for(i=1;i<MATRIX_SIZE;i++)
	{
		totalArea[matrix[1][i]] = -1;
	}
	for(i=1;i<MATRIX_SIZE;i++)
	{
		totalArea[matrix[MATRIX_SIZE-1][i]] = -1;
	}
	

	//if the position is not infinite (-1_, we calculate its area
	for(i=0;i<=coordinateIndex;i++)
	{
		if(totalArea[i]!=-1)
		{
			for(j=1;j<MATRIX_SIZE;j++)
			{
				for(k=1;k<MATRIX_SIZE;k++)
				{
					if(matrix[j][k]==i)
						totalArea[i]++;
				}
			}
		}
	}

	k=0;
	j=0;
	for(i=0;i<=coordinateIndex;i++)
	{
		if(totalArea[i]>k)
		{
			k= totalArea[i];
			j= i;
		}
	}

	printf("%d",k);

	return 0;
}
