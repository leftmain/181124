#include "student.h"

void Student::help() {
	printf("Student\n\
 -1 - return\n\
  0 - print student\n\
  1 - print name\n\
  2 - print value\n\n");
}

void Student::menu() {
	int i; system("clear");
	help();
	print_();
	while (scanf("%d", &i) == 1) {
		system("clear");
		help();
		switch(i) {
			case -1: system("clear"); return;
			case 0: print_(); break;
			case 1: printf("%s\n", name);
			case 2: printf("%d\n", value);
			default: return;
		}
	}
}

void Student::print() { printf("[%s %d] ", name, value); }
void Student::print_() { printf("[%s %d]\n", name, value); }

