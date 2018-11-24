#include "stack.h"
#include <time.h>

int read(Stack <Student, Queue> *, const char *, int, int);
int read(Queue <Student> *, const char *, int);

int main(int argc, char ** argv) {
	Stack <Student, Queue> a;
//	Queue <Student> a;
	int n, m, res;
	const char * filename = "a.txt";

	if (argc < 3 || argc > 4 || (n = atoi(argv[1])) <= 0 || (m = atoi(argv[2])) <= 0) {
		printf("usage: %s [n] [m] [filename]\n", argv[0]);
		return -4;
	}
	if (argc == 4) filename = argv[3];
	else printf("file %s is default\n", filename);

	if ((res = read(&a, filename, n, m))) {
		switch (res) {
			case -1:
				printf("Not enough memory\n");
				break;
			case -2:
				printf("Cannot read file %s\n", filename);
				break;
			case -3:
				printf("Cannot open file %s\n", filename);
				break;
			default:
				printf("Unknown error\n");
		}
		return -2;
	}

//	a.print();
	a.menu();

	return 0;
}

int read(Stack <Student, Queue> * a, const char * name, int n, int m) {
	int res;
	FILE * fp;
	if (!(fp = fopen(name, "r"))) return -3;
	res = a->read(fp, n, m);
	fclose(fp);
	return res;
}

int read(Queue <Student> * a, const char * name, int n) {
	int res;
	FILE * fp;
	if (!(fp = fopen(name, "r"))) return -3;
	res = a->read(fp, n);
	fclose(fp);
	return res;
}

