#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTNAME "./input"
#define COORDINATE_AMMOUNT 80
#define MATRIX_SIZE 401
#define MAX_DIST 10000

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

int checker(int x,int y,int coordinateIndex, int coordinates[COORDINATE_AMMOUNT][2])
{
	int i,temp=0;

	for(i=1;i<coordinateIndex;i++)
	{
		temp+=abs(x-coordinates[i][0])+abs(y-coordinates[i][1]);
	}

	if(temp<MAX_DIST)
		return 1;

	return 0;

}

int main()
{

	int i,j,k,area=0,coordinateIndex=1;
	int coordinates[COORDINATE_AMMOUNT][2];
	char a;
	char coordinatesChar[20];
	FILE *inputfile;

	inputfile=fopen(INPUTNAME,"r");

	//reads the file and feeds the matrix of coordinates
	while(fgets(coordinatesChar,20,inputfile))
	{
		coordinates[coordinateIndex][0] = extractX(coordinatesChar);
		coordinates[coordinateIndex][1] = extractY(coordinatesChar);
		coordinateIndex++;
	}

	fclose(inputfile);

	//runs matrix calculating values
	for(i=1;i<MATRIX_SIZE;i++)
	{
		for (j=1;j<MATRIX_SIZE;j++)
		{
			area+=checker(i,j,coordinateIndex,coordinates);
		}
	}

	printf("%d",area);
	return 0;
}
 
