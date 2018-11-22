#ifndef QUETYPE_H_INCLUDED
#define QUETYPE_H_INCLUDED

class FullQueue {};
class EmptyQueue {};

template<class ItemType>
class QueType {

    public:
        QueType();
        QueType(int max);
        ~QueType();
        void MakeEmpty();
        bool isEmpty();
        bool isFull();
        void Enqueue(ItemType);
        void Dequeue(ItemType&);
        void PrintQue(int);

    private:
        int front;
        int rear;
        ItemType* items;
        int maxQue;
};

#endif // QUETYPE_H_INCLUDED
