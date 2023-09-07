#include "FineGrainedQueue.h"

std::mutex* bc;

Node::Node(int v, Node* n) : value(v), next(n)
{
     this->node_mutex = new std::mutex{};
}

Node::~Node()
{
}


FineGrainedQueue::FineGrainedQueue()
{
    this->head = new Node(10, nullptr);
    this->queue_mutex = new std::mutex{};
}

FineGrainedQueue::~FineGrainedQueue()
{
    Node* cur = this->head, *next = this->head->next;
    delete this->queue_mutex;
    bc = cur->node_mutex;
    while (next)
    {
        delete cur;
        cur = next;
        next = cur->next;
    }
    delete cur;
}


void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* prev, * cur;
    queue_mutex->lock();

    

    prev = this->head;
    cur = this->head->next;

    prev->node_mutex->lock();
    
    queue_mutex->unlock();


    for(int i = 1; i <= pos && cur != nullptr; ++i)
    {
        if (i == pos)
        {
            Node* newNode = new Node{ value, cur };
            prev->next = newNode;
            prev->node_mutex->unlock();
            return;
        }
        if (cur) 
        {
            cur->node_mutex->lock();
            prev->node_mutex->unlock();
            prev = cur;
            cur = prev->next;
        }
    }

    Node* newNode = new Node{ value, cur };
    prev->next = newNode;
    prev->node_mutex->unlock();
}


std::ostream& operator<<(std::ostream& out, const FineGrainedQueue& queue)
{
    Node* cur, * next;
    queue.queue_mutex->lock();

    

    cur = queue.head;
    next = cur->next;

    cur->node_mutex->lock();
    
    queue.queue_mutex->unlock();

    out << "Content of queue: ";

    while (next)
    {
        out << cur->value << " ";
        cur = next;
        next = cur->next;
    }
    out << cur->value;

    return out;
}