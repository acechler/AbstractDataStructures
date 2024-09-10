#ifndef IBAG_H
#define IBAG_H

template <typename T>

class IBag {
public:
	virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const T& newEntry) = 0;
	virtual bool remove(const T& targetEntry) = 0;
	virtual void clear() = 0;
	virtual int getFrequencyOf(const T& entry) const = 0;
	virtual bool contains(const T& targetEntry) const = 0;
	virtual ~IBag() {}
};


#endif // !I_BAG