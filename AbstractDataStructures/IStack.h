#ifndef ISTACK_H
#define ISTACK_H

template <typename T>
class IStack {
public:
	
	virtual bool push(const T& item) = 0;
	virtual T* pop() = 0;
	virtual void empty() = 0;
	virtual T* peek() = 0;
	virtual ~IStack() {}
};


#endif // !ISTACK_H
