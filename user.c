#include <stdio.h>
#include <stdlib.h>

#include "user.h"

static person* p ;

int user_create(char* datafile, person** pp, int* return_number)
{
   //몇명의 선수의 기록을 가져올지 결정
   int number;

	FILE* file; //file 이라는 파일 선언
	file = fopen(datafile, "r"); //fopen("파일명", 모드)
	fscanf(file,"%d", &number);

p  = (person*)malloc(sizeof(person)*number);

	for (int i = 0; i < number; i++)
	{
		fscanf(file,"%s %lf %d %d %d %c", p[i].name, &p[i].record, &p[i].height, &p[i].weight, &p[i].age, &p[i].gender);
	}

*return_number = number;
*pp = p;

if ( *return_number <= 0 )
{
  printf("Please check the number of players\n");
  return -1;
}

fclose(file);

  return 0;
}

int user_close()
{
  free(p);

  return 0;
}
