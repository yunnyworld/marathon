#include <stdio.h>
#include <stdlib.h> //malloc(memory allocation)함수 사용

#include "calc.h"
//#include "userinput.h"

#define DEFAULT_FILE "marathon_v1.txt"

int main( int argc, char* argv[])
{
  int number;
	person *p;

  char* datafile;

  if(argc == 1)
  {
    datafile = DEFAULT_FILE;
  } else if(argc == 2)
  {
    datafile = argv[1];
  } else if(argc>2)
  {
    printf("Usage : ./marathon datafile\n");
    exit(1);
  }

  user_create(datafile, &p, &number);

	double avg;
	avg = calc_average(p, number);
	printf("Average is %.2f\n", calc_average(p, number));

	// 최소값을 갖는 사람의 변수를 first_person  선언
	person* first_person;
	// 최소값을 갖는 사람을 구하는 함수를 호출, return 값(person 구조체)을 first_person 에 저장
	first_person = calc_first(p, number);
	// first_person->name은 first_person.name과 다르게 구조체를 가리키는 의미가 아닌 구조체의 주소값을 가르키는 의미를 뜻함으로써 메모리 절약 가능
	// ( ~~ )?" true " false " - 괄호 안이 참이면 true칸 실행 아니면 false칸 실행
	printf("first person is %s. %s record is %.2f.\n", first_person->name, (first_person->gender == 'm')?"he's":"she's" ,first_person->record);

	double _rate;
	_rate = calc_rate(p, number, "e");
	printf("Rate of e from total is %.2f%%\n", _rate); //double형은 lf로 받음

	//person* dec_gen;
	//int dec_gen_f;
	//ret = decgen(p, number, 'm');
	calc_decgen(p, number, 'f');

  calc_decage(p, number, -20, -30);

	//int dec_hei_160_170;
	calc_dechei(p, number, 160, 170);

	//int dec_wei_70_80;
	calc_decwei(p, number, 70, 80);

  user_close();

	//fclose(file); //끝나기 전 항상 파일 닫기

	return 0;
}
