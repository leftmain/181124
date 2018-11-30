#include "queue_node.h"

#define MAX_PRINT 10

template <class T>
class Queue
{
private:
	QNode <T> * head, * tail;
	int l;
public:
	Queue() { head = tail = 0; l = 0; }
	~Queue() {
		QNode <T> * curr = 0;
		while (head) {
			curr = head;
			head = head->get_next();
			delete curr;
		}
		l = 0;
	}
	void operator==(const Queue& rhs) {
		head = rhs.head;
		tail = rhs.tail;
		l = rhs.l;
	}
	void clear() { head = tail = 0; l = 0; }

	void push(QNode <T> * n) { // add to tail
		if (!head) head = n;
		else tail->set_next(n);
		tail = n;
		l++;
	}
	void pop() { // delete head
		QNode <T> * curr = head;
		if (head) {
			head = head->get_next();
			delete curr;
			l--;
		}
	}
	int size() const { return l; }
	QNode <T> * get_head() const { return head; }
	QNode <T> * get_tail() const { return tail; }

//	int read(FILE *, int);
	int read(FILE * fp, int n) {
		T curr;
		QNode <T> * node;
		int i = 0, res = 0;
		for (; i < n; i++) {
			if ((res = curr.read(fp))) {
				return res;
			}
			node = new QNode <T>;
			if (!node) return -1;
			*node == curr;
			push(node);
			curr.clear();
		}

		return 0;
	}

	void print() {
		int i = 0, n = (l > MAX_PRINT) ? MAX_PRINT : l;
		QNode <T> * curr = head;
		for (; i < n; i++) {
			curr->print();
			curr = curr->get_next();
		}
		printf("\n");
	}

	void help() {
		printf("Queue\n\
 -1 - return\n\
  0 - goto head menu\n\
  1 - goto tail menu\n\
  2 - print Queue\n\
  3 - print size\n\
  4 - print head\n\
  5 - print tail\n\
  6 - pop (delete head)\n\
  7 - push (add to tail)\n\n");
	}

	void add() {
		QNode <T> * node = new QNode <T>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		printf("Print name and value\n");
		if (node->read(stdin)) {
			printf("error\n");
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
				case -1: k = system("clear"); return;
				case 0: head->menu(); help(); print(); break;
				case 1: tail->menu(); help(); print(); break;
				case 2: print(); break;
				case 3: printf("SIZE = %d\n", size()); break;
				case 4: head->print_(); break;
				case 5: tail->print_(); break;
				case 6: pop(); print(); break;
				case 7: add(); print(); break;
				default: return;
			}
		}
	}
};

