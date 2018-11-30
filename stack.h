#include "stack_node.h"

#define MAX_PRINT 10

template <class T1, template <class> class T2>
class Stack
{
private:
	SNode <T1, T2> * top;
	int l;

public:
	Stack() { top = 0; l = 0; }
	~Stack() {
		SNode <T1, T2> * curr = top;
		while (top) {
			curr = top;
			top = top->get_next();
			delete curr;
		}
		top = 0;
		l = 0;
	}

	void push(SNode <T1, T2> * n) { // add top
		n->set_next(top);
		top = n;
		l++;
	}
	void pop() { // delete top
		SNode <T1, T2> * curr = top;
		if (top) {
			top = top->get_next();
			delete curr;
			l--;
		}
	}
	int size() const { return l; }
	SNode <T1, T2> * get_top() const { return top; }

	int read(FILE * fp, int n, int m) {
		T2 <T1> curr;
		SNode <T1, T2> * node;
		int i = 0, res = 0;
		for (; i < m; i++) {
			if ((res = curr.read(fp, n))) {
				return res;
			}
			node = new SNode <T1, T2>;
			if (!node) return -1;
			*node == curr;
			push(node);
			curr.clear();
		}
		return 0;
	}

	void print() {
		int i = 0, n = (l > MAX_PRINT) ? MAX_PRINT : l;
		SNode <T1, T2> * curr = top;
		for (; i < n; i++) {
			curr->print();
			curr = curr->get_next();
		}
		printf("\n");
	}
	void help() {
		printf("Stack\n\
 -1 - return\n\
  0 - goto top menu\n\
  1 - print Stack\n\
  2 - print size\n\
  3 - print top\n\
  4 - pop (delete top)\n\
  5 - push (add to top)\n\n");
	}

	void add() {
		SNode <T1, T2> * node = new SNode <T1, T2>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		push(node);
	}
	void menu() {
		int i, k = system("clear");
		help();
		print();
		while (scanf("%d", &i) == 1) {
			k = system("clear");
			help();
			switch(i) {
				case -1: return;
				case 0: top->menu(); help(); print(); break;
				case 1: print(); break;
				case 2: printf("SIZE = %d\n", size()); break;
				case 3: top->print(); break;
				case 4: pop(); print(); break;
				case 5: add(); print(); break;
				default: return;
			}
		}
	}
};

