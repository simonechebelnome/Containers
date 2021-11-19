#ifndef ITERATOR_CLASS_HPP
# define ITERATOR_CLASS_HPP

# include "Iter_interface.hpp"

namespace ft {

	template <typename T>
	Iterator<T>::Iterator(void) : _value(NULL) {
		return ;
	}

	template <typename T>
	Iterator<T>::Iterator(T *src) : _value(src) {
		return ;
	}

	template <typename T>
	Iterator<T>::Iterator(Iterator const &copy) {
		*this = src;
	}

	template <typename T>
	Iterator<T>::~Iterator(void) {
		return ;
	}

	template <typename T>
	Iterator<T> &Iterator<T>::operator=(Iterator const &rhs) {
		if (this == &rhs)
			return (*this);
		*this->_value = rhs._value;
		return (*this);
	}

	template <typename T>
	bool Iterator<T>::operator==(Iterator const &rhs) const {
		return (this->_value == rhs._value);
	}

	template <typename T>
	bool Iterator<T>::operator!=(Iterator const &rhs) const {
		return (this->_value != rhs._value);
	}

	template <typename T>
	bool Iterator<T>::operator<(Iterator const &rhs) const {
		return (this->_value < rhs._value);
	}

	template <typename T>
	bool Iterator<T>::operator<=(Iterator const &rhs) const {
		return (this->_value <= rhs._value);
	}

	template <typename T>
	bool Iterator<T>::operator>(Iterator const &rhs) const {
		return (this->_value > rhs._value);
	}

	template <typename T>
	bool Iterator<T>::operator>=(Iterator const &rhs) const {
		return (this->_value >= rhs._value);
	}

	//? Queste due returnano l'iteratore prima che venga incrementato

	template <typename T>
	Iterator<T> Iterator<T>::operator++(int) {
		Iterator<T>	tmp(*this);
		++this->_value;
		return(tmp);
	}

	template <typename T>
	Iterator<T> Iterator<T>::operator--(int) {
		Iterator<T>	tmp(*this);
		--this->_value;
		return(tmp);
	}

	//? Questi returnano con il valore già incrementato

	template <typename T>
	Iterator<T> &Iterator<T>::operator++(void) {
		++this->_value;
		return(*this);
	}

	template <typename T>
	Iterator<T> &Iterator<T>::operator--(void) {
		--this->_value;
		return(*this);
	}

	template <typename T>
	typename Iterator<T>::difference_type
		Iterator<T>::operator-(Iterator const &rhs) const {
			return(this->_value - rhs._value);
	}

	template <typename T>
	Iterator<T>	Iterator<T>::operator+(difference_type n) const {
			return(Iterator(this->_value + n));
	}

	template <typename T>
	Iterator<T>	Iterator<T>::operator-(difference_type n) const {
			return(Iterator(this->_value - n));
	}
}

#endif