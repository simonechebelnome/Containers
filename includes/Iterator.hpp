#ifndef ITERATOR_CLASS_HPP
# define ITERATOR_CLASS_HPP

# include "Iter_interface.hpp"

namespace ft {

	template <typename T>
	iterator<T>::iterator(void) : _value(NULL) {
		return ;
	}

	template <typename T>
	iterator<T>::iterator(T *src) : _value(src) {
		return ;
	}

	template <typename T>
	iterator<T>::iterator(iterator const &copy) {
		*this = src;
	}

	template <typename T>
	iterator<T>::~iterator(void) {
		return ;
	}

	template <typename T>
	iterator<T> &iterator<T>::operator=(iterator const &rhs) {
		if (this == &rhs)
			return (*this);
		*this->_value = rhs._value;
		return (*this);
	}

	template <typename T>
	bool iterator<T>::operator==(iterator const &rhs) const {
		return (this->_value == rhs._value);
	}

	template <typename T>
	bool iterator<T>::operator!=(iterator const &rhs) const {
		return (this->_value != rhs._value);
	}

	template <typename T>
	bool iterator<T>::operator<(iterator const &rhs) const {
		return (this->_value < rhs._value);
	}

	template <typename T>
	bool iterator<T>::operator<=(iterator const &rhs) const {
		return (this->_value <= rhs._value);
	}

	template <typename T>
	bool iterator<T>::operator>(iterator const &rhs) const {
		return (this->_value > rhs._value);
	}

	template <typename T>
	bool iterator<T>::operator>=(iterator const &rhs) const {
		return (this->_value >= rhs._value);
	}

	//? Queste due returnano l'iteratore prima che venga incrementato

	template <typename T>
	iterator<T> iterator<T>::operator++(int) {
		iterator<T>	tmp(*this);
		++this->_value;
		return(tmp);
	}

	template <typename T>
	iterator<T> iterator<T>::operator--(int) {
		iterator<T>	tmp(*this);
		--this->_value;
		return(tmp);
	}

	//? Questi returnano con il valore già incrementato

	template <typename T>
	iterator<T> &iterator<T>::operator++(void) {
		++this->_value;
		return(*this);
	}

	template <typename T>
	iterator<T> &iterator<T>::operator--(void) {
		--this->_value;
		return(*this);
	}

	template <typename T>
	typename iterator<T>::difference_type
		iterator<T>::operator-(iterator const &rhs) const {
			return(this->_value - rhs._value);
	}

	template <typename T>
	iterator<T>	iterator<T>::operator+(difference_type n) const {
			return(iterator(this->_value + n));
	}

	template <typename T>
	iterator<T>	iterator<T>::operator-(difference_type n) const {
			return(iterator(this->_value - n));
	}
}

#endif