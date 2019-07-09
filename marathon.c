#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
  char name[10];
  int record;
  int height;
  int weight;
  int age;
  char gender;
} person;

//선수 정보 - 구조체

double average(person *p, int number)
{
  double sum = 0;
  for(int i=0;i < number;i++)
  {
    sum += p[i].record;
  }
  printf("average is %f\n", sum/number);
}

//평균값

char first(person *p, int number)
{
  double min = p[0].record;
  int index = 0;
  for(int i=0;i < number;i++)
  {
    if(p[i].record < min)
    {
      index = i;
    }
  }
  printf("first place is %s\n", p[index].name);
  //최소값을 갖는 선수의 "이름" 출력
}

//1등

char rate(person *p,int number)
{
  int* recordptr = (int*)malloc(sizeof(int)*number);
  int* rankptr = (int*)malloc(sizeof(int)*number);
  int* rateptr = (int*)malloc(sizeof(int)*number);
  for(int i = 0; i < number; i++)
  {
    rankptr[i] = 1;
    recordptr[i] = p[i].record;
    for(int j = 1; j < number; j++)
    {
      if(recordptr[i] > recordptr[j])
      {
        rankptr[i]++;
      }
    }
    rateptr[i] = rankptr[i]/number*100;
  }
  printf("rate of person2 is %d\n", rateptr[1]);
}

//상위비율 - 전체 number에서의 등수?

int main(){
  double avg;
  person p[100];
for (int i = 0; i < 5; i++)
{
  scanf("%s %d %d %d %d %c", p[i].name, &p[i].record, &p[i].height, &p[i].weight, &p[i].age, &p[i].gender);
  printf("%s\n", p[i].name);
}

avg = average(p, 5);
first(p, 5);
rate (p)

  return 0;
}
