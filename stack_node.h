#include "queue.h"

template <class T, template <class> class Container>
class SNode : public Container <T>
{
private:
	SNode * next;

public:
	SNode() { next = 0; }
	~SNode() { next = 0; }
	
	SNode * get_next() const { return next; }
	void set_next(SNode * n) { next = n; }
};

