#define NAME_LENGTH 10

//선수 정보 - 구조체
typedef struct person
{
	char name[NAME_LENGTH];
	double record;
	int height;
	int weight;
	int age;
	char gender;
} person;

int user_create(char* datafile, person** pp, int* return_number);
int user_close();
