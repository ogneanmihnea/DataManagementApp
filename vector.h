#ifndef LAB6_ARRAY_H_
#define LAB6_ARRAY_H_

#include "domain.h"

template <typename ElementType>
class vector
{
private:
	ElementType* elems;
	int dim, cp;

	void resize()
	{
		ElementType* Newelems = new ElementType[2 * cp];

		for (int i = 0; i < dim; i++)
			Newelems[i] = elems[i];

		cp *= 2;
		delete[] elems;

		elems = Newelems;
	}
public:
	vector(int cp) {
		this->dim = 0;
		this->cp = cp;
		this->elems = new ElementType[cp];
	}

	vector() {
		this->dim = 0;
		this->cp = 2;
		this->elems = new ElementType[this->cp];
	}


	vector(const vector& arrayCopy)
	{
		this->dim = arrayCopy.dim;
		this->cp = arrayCopy.cp;

		this->elems = new ElementType[this->cp];

		for (int i = 0; i < this->dim; i++)
			this->elems[i] = arrayCopy.elems[i];
	}

	vector& operator=(const vector& arrayCopy)
	{
		delete[] elems;
		this->dim = arrayCopy.dim;
		this->cp = arrayCopy.cp;

		this->elems = new ElementType[this->cp];

		for (int i = 0; i < this->dim; i++)
			this->elems[i] = arrayCopy.elems[i];

		return *this;
	}


	void push_back(ElementType e)
	{
		if (this->cp == this->dim)
			resize();
		this->elems[this->dim] = e;
		this->dim += 1;
	}

	void erase(int index)
	{
		for (int i = index; i < dim - 1; i++)
			elems[i] = elems[i + 1];
		dim -= 1;
	}

	ElementType& at(int index) const {
		return elems[index];
	}

	int size() const {
		return this->dim;
	}

	~vector() {
		delete[] elems;
	}

	ElementType& operator[](int poz)  const {
		//if (poz < 0 || poz >= dim) {
			//throw std::exception("Index out of bounds!");
		//}
		return elems[poz];
	}

	ElementType* begin() const {
		return elems;
	}

	ElementType* end() const {
		return elems + dim;
	}
};


#endif 
