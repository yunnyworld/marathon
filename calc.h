#include "user.h"

#define RET_SUCCESS 0
#define RET_INVALID_GENDER -1
#define RET_INVALID_AGE -2
#define RET_INVALID_HEIGHT -3
#define RET_INVALID_WEIGHT -4

person* calc_first(person *p, int number);
double calc_average(person *p, int number);
double calc_rate(person *p,int number, char *name);

int calc_decgen(person *p, int number, char gender);
int calc_decage(person* p, int number, int a, int b);
int calc_dechei(person* p, int number, int a, int b);
int calc_decwei(person* p, int number, int a, int b);
