#if !defined (STACKLINKED_H)
#define STACKLINKED_H

#include "NextNode.h"

template < class T >
class StackLinked
{
   private:
      NextNode<T>* top;
      int sze;  // number of items in the stack

   public:
      StackLinked();
      ~StackLinked();
      bool isEmpty();
      int size();
      void popAll();
      T* pop();
      void push(T* item);
      T* peek();
};

template < class T >
StackLinked<T>::StackLinked()
{
   top = NULL;
   sze = 0;
}

template < class T >
StackLinked<T>::~StackLinked()
{
   popAll();
}

template < class T >
bool StackLinked<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
int StackLinked<T>::size()
{
   return sze;
}

template < class T >
void StackLinked<T>::popAll()
{
   //loop over the stack, deleting the nodes
   //the actual items are not deleted
   if (sze == 0) return;

   NextNode<T>* curr = top;
   NextNode<T>* prev = NULL;
   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      prev->setNext(NULL);
      delete prev;
   }
}

template < class T >
T* StackLinked<T>::peek()
{
	T* item = NULL;
	//DO THIS
	if(top != NULL)
	{
		item = top->getItem(); //returns the item at the top
	}
	return item;
}

template < class T >
void StackLinked<T>::push(T* item)
{
	//DO THIS
	NextNode<T>* node = new NextNode<T>(item);
	node->setNext(top);  //new item goes to the top
	top = node;          //top equal to the node
	sze++;
}

template < class T >
T* StackLinked<T>::pop()
{
	if (sze == 0) return NULL;  //don't pop if true
	
	//DO THIS
	T* item = NULL;
	if(sze > 0)
	{
		NextNode<T>* curr = top;  //current node = to top
		item = top->getItem();    //item equals to the item at the top
		top = top->getNext();     //set top equal to the next item in the stack
		sze--;
		delete curr;              //delete curr becuae you arn't returning it
		return item;              //return the item
	}

}

#endif
