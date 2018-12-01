#include "queue_node.h" 

#define MAX_QUEUE_PRINT 10

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
		head = 0;
		l = 0;
	}
	void operator==(const Queue& rhs) {
		head = rhs.head;
		tail = rhs.tail;
		l = rhs.l;
	}
	int operator<(const Queue& b) {
		return (*head < *b.head);
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

	int number_len(int a) {
		int k = 0;
		if (a == 0) return 1;
		while (a) {
			k++;
			a /= 10;
		}
		return k;
	}
	int len() {
		int s = 0;
		QNode <T> * curr = head;
		while (curr) {
			s += strlen(curr->get_name()) + 4 + number_len(curr->get_value());
			curr = curr->get_next();
		}
		return s;
	}
	void print() {
		int i = 0, n = (l > MAX_QUEUE_PRINT) ? MAX_QUEUE_PRINT : l;
		QNode <T> * curr = head;
		for (; i < n; i++) {
			curr->print();
			curr = curr->get_next();
		}
	}

	void help() {
		system("clear");
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
			delete node;
			printf("error\n");
			return;
		}
		push(node);
	}
	void menu() {
		int i; system("clear");
		help();
		print();
		while (scanf("%d", &i) == 1) {
			help();
			switch(i) {
				case -1: system("clear"); return;
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

