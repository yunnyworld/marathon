#include <stdio.h>
#include <stdlib.h> //malloc(memory allocation)함수 사용
#include <string.h> //strcmp(string compare)함수 사용

#include "calc.h"

double calc_average(person *p, int number)
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
person* calc_first(person *p, int number) //리턴값이 함수에 처음에 위치(person*)
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
double calc_rate(person *p,int number, char *name)
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

	double return_value = rateptr[index];

	free(rankptr);
	free(rateptr);

	 return return_value;
}

//decide gender - 성별을 주고 그 성별 끼리의 평균, 1등 구하기

int calc_decgen(person *p, int number, char gender)
{
	int cnt = 0; // 그 성별의

	if( (gender != 'm') && (gender != 'f') )
	{
		printf("Please check your age range.\n");
		return RET_INVALID_GENDER;
	}

	for(int i = 0; i < number ; i++) // 그 성별이 몇명이 있는지 cnt로 세어주기
	{
		if(p[i].gender == gender)
		{
			cnt++;
		}
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

	// 평균
	printf("Average of %c is %.2f\n", gender, calc_average(pgender,cntgender));
	// 1등
	person* first_person;
	first_person = calc_first(pgender, cntgender);
	printf("first person is %s. %s record is %.2f\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);
	// 상위 비율 - rate함수는 처음에 어떤 사람의 상위 비율을 구할지 정해야 하기 때문에 "어떤 사람이 남자이면 여자일때 실행 불가"하므로 decgen 함수 안에서 처리 안 함
	free(pgender);

	return RET_SUCCESS;
}

//decide age - 나이 구간을 주고 그 구간끼리의 평균, 1등 구하기

int calc_decage(person* p, int number, int a, int b)
{
	int cnt = 0; // a와 b사이에 해당하는 나이를 가진 사람 수 세기

	if((a < 0)||(b < 0)||(b < a))
	{
		printf("Please check your age range.\n");
		return RET_INVALID_AGE;
	}

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
	printf("Average of between %d years old and %d years old is %.2f\n", a, b, calc_average(page, cntage));
	//1등
	person* first_person;
	first_person = calc_first(page, cntage);
	printf("first person is %s. %s record is %.2f\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

  free(page);

	return RET_SUCCESS;
}

//decide height - 키 구간을 주고 그 구간끼리의 평균, 1등 구하기

int calc_dechei(person* p, int number, int a, int b)
{
	int cnt = 0;

	if((a < 0)||(b < 0)||(b < a))
	{
		printf("Please check your height range.\n");
		return RET_INVALID_HEIGHT;
	}

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
	printf("Average of between %d cm and %d cm is %.2f\n", a, b, calc_average(phei, cnthei));
	//1등
	person* first_person;
	first_person = calc_first(phei, cnthei);
	printf("first person is %s. %s record is %.2f\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

	free(phei);

	return RET_SUCCESS;
}

//decide weight - 몸무게 구간을 주고 그 구간끼리의 평균, 1등 구하기

int calc_decwei(person* p, int number, int a, int b)
{
	int cnt = 0;

	if((a < 0)||(b < 0)||(b < a))
	{
		printf("Please check your weight range.\n");
		return RET_INVALID_WEIGHT;
	}

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
	printf("Average of between %d kg and %d kg is %.2f\n", a, b, calc_average(pwei, cntwei));
	//1등
	person* first_person;
	first_person = calc_first(pwei, cntwei);
	printf("first person is %s. %s record is %.2f\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

	free(pwei);

	return RET_SUCCESS;
}
