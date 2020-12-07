using namespace std;

template <class T>
class GenStack {
  public:

    //constructors
    GenStack();
    GenStack(int s);

    //destructor
    ~GenStack();

    //helpers
    void push(T* p);
    T* peek(); //will return top element
    T* pop(); //will remove and return top element
    void resize(); //increases the size by creating new stack
    bool isEmpty(); //checks if stack is empty
    bool isFull(); //checks if stack is full

    //size of stack
    int size;

    //the top (most recent item & next to be returned)
    int top;

    //pointer to the stack
    T** stack;

  private:
};

template <class T>
GenStack<T>::GenStack()
{
  stack = new T*[1];
  size = 1;
  top = -1;
}

template <class T>
GenStack<T>::GenStack(int s)
{
  stack = new T*[s];
  size = s;
  top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
    for(int i = 0; i < size; ++i) {
        delete[] stack[i];
    }
    delete[] stack;
}

template <class T>
void GenStack<T>::push(T* p)
{
  if (!isFull())
  {
    stack[++top] = p;
  }
  else
  {
    resize();
    stack[++top] = p;
  }
}

template <class T>
T* GenStack<T>::peek()
{
  if (!isEmpty())
  {
    return stack[top];
  }
}

template <class T>
T* GenStack<T>::pop()
{
  if (!isEmpty())
  {
    return stack[top--];
  }
}

template <class T>
void GenStack<T>::resize()
{
  int biggerSize = size++;
  T** biggerStack = new T*[biggerSize];
  for (int i = 0; i < size; ++i)
  {
    biggerStack[i] = stack[i];
  }
  stack = biggerStack;
}

template <class T>
bool GenStack<T>::isEmpty()
{
  bool isEmpty;
  if (top == -1)
  {
    isEmpty = true;
  }
  else
  {
    isEmpty = false;
  }

  return isEmpty;
}

template <class T>
bool GenStack<T>::isFull()
{
  bool isFull;
  if (top == size - 1)
  {
    isFull = true;
  }
  else
  {
    isFull = false;
  }

  return isFull;
}
