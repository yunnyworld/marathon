#include "db.h"

#define NAME_LENGTH 10

#define RET_SUCCESS 0
#define RET_INVALID_GENDER -1
#define RET_INVALID_AGE -2
#define RET_INVALID_HEIGHT -3
#define RET_INVALID_WEIGHT -4

typedef struct user
{
	char name[NAME_LENGTH];
	double record;
	int height;
	int weight;
	int age;
	char gender;
} user;

int user_create(const char* datafile, user **p, int* return_number);
int user_stat(user* p, int number);
void user_close();
