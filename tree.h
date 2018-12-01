#include <stdio.h>
#include <time.h>
#include "tree_node.h"

#define MAX_TREE_LEVEL 3

template <class T, template <class> class T1,
template <class, template <class> class> class T2>
class Tree
{
private:
	TNode <T, T1, T2> * root, * curr;

	void delete_tree(TNode <T, T1, T2> * r) {
		TNode <T, T1, T2> * k;
		while (r) {
			if (r->get_down()) delete_tree(r->get_down());
			k = r;
			r = r->get_level();
			delete k;
		}
	}
public:
	Tree() { root = curr = 0; }
	~Tree() { delete_tree(root); }
	int read(FILE * fp, int n, int m, int k) {
		T2 <T, T1> curr;
		TNode <T, T1, T2> * node;
		int i = 0, res = 0;
		for (; i < k; i++) {
			if ((res = curr.read(fp, n, m))) {
				return res;
			}
			node = new TNode <T, T1, T2>;
			if (!node) return -1;
			*node == curr;
			add(node, root);
			curr.clear();
		}
		return 0;
	}
	void print(TNode <T, T1, T2> * r = 0, int level = 0) {
		TNode <T, T1, T2> * c;
		if (!r) r = root;
		if (!r) return;
		if (level > MAX_TREE_LEVEL) return;
//		for (int i = 0; i < level; i++) printf("    ");
		if (r == curr) r->print_curr(level);
		else r->print(level);
		c = r->get_down();
		while (c) { print(c, level + 1); c = c->get_level(); }
	}

	void add(TNode <T, T1, T2> * a, TNode <T, T1, T2> * r) {
		if (!r) {
			curr = root = a;
			return;
		}
		TNode <T, T1, T2> * c = r->get_down();
		if (!c) r->set_down(a);
		else {
			int cmp = (*a < *r);
			if (cmp < 0) {
				if ((*c < *r) < 0) add(a, c);
				else {
					a->set_level(c);
					r->set_down(a);
				}
			} else if (cmp > 0) {
				if ((*c < *r) > 0) add(a, c);
				else {
					if (c->get_level()) {
						c = c->get_level();
						if ((*c < *r) == 0) {
							if (c->get_level()) {
								add(a, c->get_level());
							} else c->set_level(a);
						} else add(a, c);
					} else c->set_level(a);
				}
			} else {
				cmp = (*c < *r);
				if (cmp < 0) {
					if (c->get_level()) {
						if ((*c->get_level() < *r) == 0) {
							c = c->get_level();
							while (c->get_down())
								c = c->get_down();
							c->set_down(a);
						} else {
							a->set_level(c->get_level());
							c->set_level(a);
						}
					} else c->set_level(a);
				} else if (cmp == 0) {
					while (c->get_down()) c = c->get_down();
					c->set_down(a);
				} else {
					a->set_level(c);
					r->set_down(a);
				}
			}
		}
	}
	
	void goto_root() { curr = root; }
	void goto_level() { curr = curr->get_level(); }
	void goto_down() { curr = curr->get_down(); }
	TNode <T, T1, T2> * get() const { return curr; }
	TNode <T, T1, T2> * get_root() const { return root; }
	TNode <T, T1, T2> * get_level() const { return curr->get_level(); }
	TNode <T, T1, T2> * get_down() const { return curr->get_down(); }
	void set(TNode <T, T1, T2> * c) { curr = c; }
	void set_level(TNode <T, T1, T2> * l) { curr->set_level(l); }
	void set_down(TNode <T, T1, T2> * d) { curr->set_down(d); }

	void help() {
		system("clear");
		printf("Tree\n\
  -1      - return\n\
  0/1     - [root/curr] menu\n\
  2/3/4/5 - print [Tree/curr_subtree/root/curr]\n\
  6/7/8   - goto [root/down/level]\n\
  9/10/11 - add to [root/down/level]\n\
  12/13   - delete [down/level]\n\
  14      - delete down subtree\n\n");
	}

	void add_root() {
		TNode <T, T1, T2> * node = new TNode <T, T1, T2>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		while (!node->get_top() ||
				!node->get_top()->get_head() ||
				!node->get_top()->get_head()->get_name()) {
			node->menu(1);
		}
		add(node, root);
	}
	void add_down() {
		if (curr->get_down()) {
			printf("down is not empty\n");
			return;
		}
		TNode <T, T1, T2> * node = new TNode <T, T1, T2>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		curr->set_down(node);
	}
	void add_level() {
		if (curr->get_level()) {
			printf("level is not empty\n");
			return;
		}
		TNode <T, T1, T2> * node = new TNode <T, T1, T2>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		curr->set_level(node);
	}
	void delete_down() {
		if (!curr->get_down()->get_down() && !curr->get_down()->get_level()) {
			delete curr->get_down();
			curr->set_down(0);
		} else {
			printf("cannot\n");
		}
	}
	void delete_level() {
		if (!curr->get_level()->get_down() && !curr->get_level()->get_level()) {
			delete curr->get_level();
			curr->set_level(0);
		} else {
			printf("cannot\n");
		}
	}
	void menu() {
		int i;
		system("clear");
		help();
		print();
		while (scanf("%d", &i) == 1) {
			help();
			switch(i) {
				case -1: return;
				case 0: root->menu(); help(); print(); break;
				case 1: curr->menu(); help(); print(); break;
				case 2: print(); break;
				case 3: print(curr); break;
				case 4: root->print(); break;
				case 5: curr->print(); break;
				case 6: goto_root(); print(); break;
				case 7: if (curr->get_down()) goto_down(); else printf("curr->down = 0 now\n"); print(); break;
				case 8: if (curr->get_level()) goto_level(); else printf("curr->level = 0 now\n"); print(); break;
				case 9: add_root(); help(); print(); break;
				case 10: add_down(); print(); break;
				case 11: add_level(); print(); break;
				case 12: delete_down(); print(); break;
				case 13: delete_level(); print(); break;
				case 14: delete_tree(curr->get_down()); curr->set_down(0); print(); break;
				default: return;
			}
		}
	}
};
	
