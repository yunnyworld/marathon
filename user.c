#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

static user* p = NULL;
static FILE* file = NULL;

user* _user_first(user *p, int number);
double _user_average(user *p, int number);
double _user_rate(user *p, int number, char *name);

int _user_decgen(user *p, int number, char gender);
int _user_decage(user *p, int number, int a, int b);
int _user_dechei(user *p, int number, int a, int b);
int _user_decwei(user *p, int number, int a, int b);

void _user_query(user *p, int stmt_id);

int user_create(const char *datafile, user** plist, int* return_number)
{
	int number = 0;

	file = fopen(datafile, "r");
	if(file == NULL) {
		printf("file open() errors!\n");
		return -1;
	}

	fscanf(file,"%d", &number);
	if( number < 1 ) {
		printf("empty file!\n");
		return -1;
	}

	p = (user*)malloc(sizeof(user)*number);

	// Load data from a datafile
	for (int i = 0; i < number; i++) {
		fscanf(file,"%s %lf %d %d %d %c", p[i].name, &p[i].record, &p[i].height,
										&p[i].weight, &p[i].age, &p[i].gender);
	}

	*plist = p;
	*return_number = number;

	// MySQL init
	if( db_init() != 0 ) {
		printf("db_init() failed!\n");
	}

	return 0;
}

// Calculate some results
int user_stat(user* p, int number)
{
	int ret = 0;

	printf("Average is %.2f\n", _user_average(p, number));

	user* first_person = NULL;
	first_person = _user_first(p, number);
	printf("First person is %s. %s record is %.2f.\n", first_person->name,
			(first_person->gender == 'm')?"he's":"she's" ,first_person->record);

	printf("Rate of e from total is %.2f%%\n", _user_rate(p, number, "e"));

	ret = _user_decgen(p, number, 'f');
  	if( ret != 0 ) {
		printf("_user_decgen returns error! %d\n", ret);
		return ret;
	}

	ret = _user_decage(p, number, 20, 30);
  	if( ret != 0 ) {
		printf("_user_decage returns error! %d\n", ret);
		return ret;
	}

	ret = _user_dechei(p, number, 160, 170);
  	if( ret != 0 ) {
		printf("_user_dechei returns error! %d\n", ret);
		return ret;
	}

	ret = _user_decwei(p, number, 70, 80);
  	if( ret != 0 ) {
		printf("_user_decwei returns error! %d\n", ret);
		return ret;
	}

	return 0;
}

void user_close()
{
	free(p);
	fclose(file);

	p = NULL;
	file = NULL;

	db_close();

	return;
}

// 전체 평균
double _user_average(user *p, int number)
{
	double avg, sum = 0;

	if( number == 0 )
		return -1;

	for(int i=0;i < number;i++)
	{
		sum += p[i].record;
	}

	avg = sum/number;

	return avg;
}

//1등
user* _user_first(user *p, int number)
{
	int index = 0;
	double min = p[0].record;

	for(int i=0;i < number;i++) {
		if(p[i].record < min) {
			index = i;
			min = p[i].record;
		}
	}

	return &p[index];
}

//상위 비율
double _user_rate(user *p,int number, char *name)
{
	int index;
	double* rankptr = (double*)malloc(sizeof(double)*number);
	double* rateptr = (double*)malloc(sizeof(double)*number);

	for(int i = 0; i < number; i++) {
		rankptr[i] = 1;

		if( !strcmp(p[i].name, name)) {
		   index = i;
		}

		for(int j = 0; j < number; j++) {
			if(p[i].record > p[j].record) {
				rankptr[i]++;
			}
		}
		rateptr[i] = rankptr[i]/number*100;
	}

	double result = rateptr[index];

	free(rankptr);
	free(rateptr);

	return result;
}

//decide gender - 성별을 주고 그 성별 끼리의 평균, 1등 구하기
int _user_decgen(user *p, int number, char gender)
{
	int cnt = 0;

	if( !(gender == 'm' || gender == 'f') ) {
		printf("Please check your gender.\n");
		return RET_INVALID_GENDER;
	}

	for(int i = 0; i < number ; i++) {
		if(p[i].gender == gender) {
			cnt++;
		}
	}

	user* pgender = (user*)malloc(sizeof(user)*cnt);

	int cntgender = 0;

	for(int i = 0; i < number; i++) {
		if(p[i].gender == gender) {
			pgender[cntgender++] = p[i];
		}
	}

	// 평균
	printf("Average of %c is %.2f\n", gender, _user_average(pgender,cntgender));
	// 1등
	user* first_person;
	first_person = _user_first(pgender, cntgender);
	printf("first person is %s. %s record is %.2f\n", first_person->name,
							(first_person->gender == 'm')?"he's":"she's" ,
							first_person->record);

	// DB Query
	_user_query(first_person, QUERY_UPDATE_AREA_TBL);

	free(pgender);

	return RET_SUCCESS;
}

//decide age - 나이 구간을 주고 그 구간끼리의 평균, 1등 구하기
int _user_decage(user* p, int number, int a, int b)
{
	int cnt = 0;

	if((a < 0)||(b < 0)||(b < a)) {
		printf("Please check your age range.\n");
		return RET_INVALID_AGE;
	}

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].age) && (p[i].age < b) ) {
			cnt++;
		}
	}

	user* page = (user*)malloc(sizeof(user)*cnt);

	int cntage = 0;

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].age) && (p[i].age < b) ) {
			page[cntage++] =  p[i];
		}
	}

	//평균
	printf("Average of between %d years old and %d years old is %.2f\n",
											a, b, _user_average(page, cntage));
	//1등
	user* first_person;
	first_person = _user_first(page, cntage);
	printf("first person is %s. %s record is %.2f\n", first_person->name,
							(first_person->gender == 'm')?"he's":"she's" ,
							first_person->record);

	// DB Query
	_user_query(first_person, QUERY_INSERT_AREA_TBL);

	free(page);

	return RET_SUCCESS;
}

//decide height - 키 구간을 주고 그 구간끼리의 평균, 1등 구하기
int _user_dechei(user* p, int number, int a, int b)
{
	int cnt = 0;

	if((a < 0)||(b < 0)||(b < a)) {
		printf("Please check your height range.\n");
		return RET_INVALID_HEIGHT;
	}

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].height) && (p[i].height < b) ) {
			cnt++;
		}
	}

	user* phei = (user*)malloc(sizeof(user)*cnt);

	int cnthei = 0;

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].height) && (p[i].height < b) ) {
			phei[cnthei++] = p[i];
		}
	}

	//평균
	printf("Average of between %d cm and %d cm is %.2f\n",
											a, b, _user_average(phei, cnthei));
	//1등
	user* first_person;
	first_person = _user_first(phei, cnthei);
	printf("first person is %s. %s record is %.2f\n", first_person->name,
								(first_person->gender == 'm')?"he's":"she's",
								first_person->record);

	free(phei);

	return RET_SUCCESS;
}

//decide weight - 몸무게 구간을 주고 그 구간끼리의 평균, 1등 구하기
int _user_decwei(user* p, int number, int a, int b)
{
	int cnt = 0;

	if((a < 0)||(b < 0)||(b < a)) {
		printf("Please check your weight range.\n");
		return RET_INVALID_WEIGHT;
	}

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].weight) && (p[i].weight < b) ) {
			cnt++;
		}
	}

	user* pwei = (user*)malloc(sizeof(user)*cnt);

	int cntwei = 0;

	for(int i = 0; i < number; i++) {
		if( (a <= p[i].weight) && (p[i].weight < b) ) {
			pwei[cntwei++] = p[i];
		}
	}

	//평균
	printf("Average of between %d kg and %d kg is %.2f\n",
												a, b, _user_average(pwei, cntwei));
	//1등
	user* first_person;
	first_person = _user_first(pwei, cntwei);
	printf("first person is %s. %s record is %.2f\n", first_person->name,
								(first_person->gender == 'm')?"he's":"she's",
								first_person->record);

	free(pwei);

	return RET_SUCCESS;
}

void _user_query(user* p, int stmt_id)
{
	switch (stmt_id/100) {
		case 1:
			db_select(stmt_id);
			break;
		case 2:
			db_insert(stmt_id);
			break;
		case 3:
			db_delete(stmt_id);
			break;
		case 4:
			db_update(stmt_id);
			break;
		default:
			break;
	}

	return;
}
