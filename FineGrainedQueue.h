#include <mutex>
#include <iostream>


struct Node
{
	int value;
	Node* next;
	std::mutex* node_mutex;

	Node(int v, Node* n);
	~Node();
};

class FineGrainedQueue
{
	Node* head;
	std::mutex* queue_mutex;

public:
	void insertIntoMiddle(int value, int pos);
	FineGrainedQueue();
	~FineGrainedQueue();
	friend std::ostream& operator<<(std::ostream& out, const FineGrainedQueue& queue);
};
