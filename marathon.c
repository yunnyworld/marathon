#include <stdio.h>
#include <stdlib.h> //malloc(memory allocation)함수 사용
#include <string.h> //strcmp(string compare)함수 사용

typedef struct person
{
  char name[10];
  double record;
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
  double avg = sum/number;

  return avg;
}

//1등

person* first(person *p, int number) //리턴값이 함수에 처음에 위치(person*)
{
  double min = p[0].record;
  int index = 0;
  for(int i=0;i < number;i++)
  {
    if(p[i].record < min)
    {
      index = i;
      min = p[i].record;
    }
  }
  // 최소값을 갖는 선수의 구조체를 리턴
  return &p[index];
}

//상위 비율

double rate(person *p,int number, char *name)
{
  int index;
  double* rankptr = (double*)malloc(sizeof(double)*number);
  double* rateptr = (double*)malloc(sizeof(double)*number);

  for(int i = 0; i < number; i++)
  {
    rankptr[i] = 1;
	if( !strcmp(p[i].name, name)) // !(p[i].name 과 name의 문자열 비교) -> 같으면 0(거짓)이 아닌 1(참), 다르면 0이 아닌 수가 아닌 0(거짓)
	{
		index = i;
	}
    for(int j = 0; j < number; j++)
    {
      if(p[i].record > p[j].record)
      {
        rankptr[i]++;
      }
    }
    rateptr[i] = rankptr[i]/number*100;

  }
	return rateptr[index];
}

//decide gender - 성별을 주고 그 성별 끼리의 평균, 1등 구하기

int decgen(person *p, int number, char gender)
{
  char* dec = (char*)malloc(sizeof(char)*number);
  int cnt = 0; // 그 성별의

  for(int i = 0; i < number ; i++) // 남자와 여자로 구분해 dec[i]에 넣기
  {
    if(p[i].gender == 'm')
    {
      dec[i] = 'm';
    }
    else
    {
      dec[i] = 'f';
    }
  }
  for(int i = 0; i < number ; i++) // 그 성별이 몇명이 있는지 cnt로 세어주기
  {
    if(dec[i] == gender)
    {
      cnt++;
    }
    printf("cnt is %d\n", cnt);
  }

  person* pgender = (person*)malloc(sizeof(person)*cnt); // pgender(포인터젠더)로 그 성별 개수 만큼 포인터 배열 만들기

  int cntgender = 0; // 그 성별의 인원 수

  for(int i = 0; i < number; i++)
  {
    if(p[i].gender == gender)
    {
      pgender[cntgender++] = p[i];
    }
  }
  printf("cntgender is %d\n", cntgender);
  // 평균
  printf("Average of %c is %lf\n", gender,average(pgender,cntgender));
  // 1등
  person* first_person;
  first_person = first(pgender, cntgender);
  printf("first person is %s. %s record is %lf\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);
  // 상위 비율 - rate함수는 처음에 어떤 사람의 상위 비율을 구할지 정해야 하기 때문에 "어떤 사람이 남자이면 여자일때 실행 불가"하므로 decgen 함수 안에서 처리 안 함

  return cntgender;
}

//decide age - 나이 구간을 주고 그 구간끼리의 평균, 1등 구하기

int decage(person* p, int number, int a, int b)
{
  int cnt = 0; // a와 b사이에 해당하는 나이를 가진 사람 수 세기

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].age)&&(p[i].age < b))
    {
      cnt++;
    }
  }

  person* page = (person*)malloc(sizeof(person)*cnt); // a와 b사이에 해당하는 나이를 가진 사람 수(cnt) 만큼 dec 구조체 배열 생성

  int cntage = 0;

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].age)&&(p[i].age < b))
    {
      page[cntage++] =  p[i];
    }
  }
  //평균
  printf("Average of between %d years old and %d years old is %lf\n", a, b, average(page, cntage));
  //1등
  person* first_person;
  first_person = first(page, cntage);
  printf("first person is %s. %s record is %lf\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

  return cntage;
}

//decide height - 키 구간을 주고 그 구간끼리의 평균, 1등 구하기

int dechei(person* p, int number, int a, int b)
{
  int cnt = 0;

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].height)&&(p[i].height < b))
    {
      cnt++;
    }
  }

  person* phei = (person*)malloc(sizeof(person)*cnt);

  int cnthei = 0;

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].height)&&(p[i].height < b))
    {
      phei[cnthei++] = p[i];
    }
  }
  //평균
  printf("Average of between %d cm and %d cm is %lf\n", a, b, average(phei, cnthei));
  //1등
  person* first_person;
  first_person = first(phei, cnthei);
  printf("first person is %s. %s record is %lf\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

  return cnthei;
}

//decide weight - 몸무게 구간을 주고 그 구간끼리의 평균, 1등 구하기

int decwei(person* p, int number, int a, int b)
{
  int cnt = 0;

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].weight)&&(p[i].weight < b))
    {
      cnt++;
    }
  }

  person* pwei = (person*)malloc(sizeof(person)*cnt);

  int cntwei = 0;

  for(int i = 0; i < number; i++)
  {
    if((a <= p[i].weight)&&(p[i].weight < b))
    {
      pwei[cntwei++] = p[i];
    }
  }
  //평균
  printf("Average of between %d kg and %d kg is %lf\n", a, b, average(pwei, cntwei));
  //1등
  person* first_person;
  first_person = first(pwei, cntwei);
  printf("first person is %s. %s record is %lf\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

  return cntwei;
}



int main(){

  int number; //몇명의 선수의 기록을 가져올지 결정

  FILE* file; //file 이라는 파일 선언
  file = fopen("marathon_v1.txt","r"); //fopen("파일명", 모드)
  fscanf(file,"%d", &number);

  person* p = (person*)malloc(sizeof(person)*number);

  for (int i = 0; i < number; i++)
  {
    fscanf(file,"%s %lf %d %d %d %c", p[i].name, &p[i].record, &p[i].height, &p[i].weight, &p[i].age, &p[i].gender);
    printf("%s\n", p[i].name);
  }



  double avg;
  avg = average(p, number);
  printf("Average is %f\n", average(p, number));

  // 최소값을 갖는 사람의 변수를 first_person  선언
  person* first_person;
  // 최소값을 갖는 사람을 구하는 함수를 호출, return 값(person 구조체)을 first_person 에 저장
  first_person = first(p, number);
  // first_person->name은 first_person.name과 다르게 구조체를 가리키는 의미가 아닌 구조체의 주소값을 가르키는 의미를 뜻함으로써 메모리 절약 가능
  // ( ~~ )?" true " false " - 괄호 안이 참이면 true칸 실행 아니면 false칸 실행
  printf("first person is %s. %s record is %lf.\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

  double _rate;
  _rate = rate(p, number, "e");
  printf("Rate of e from total is %lf%%\n", _rate); //double형은 lf로 받음

  //person* dec_gen;
  int dec_gen_f;
  //ret = decgen(p, number, 'm');
  dec_gen_f = decgen(p, number, 'f');

  int dec_age_10_20;
  dec_age_10_20 = decage(p, number, 20, 30);

  int dec_hei_160_170;
  dec_hei_160_170 = dechei(p, number, 170, 180);

  int dec_wei_70_80;
  dec_wei_70_80 = decwei(p, number, 80, 90);

  fclose(file); //끝나기 전 항상 파일 닫기

  return 0;
}
