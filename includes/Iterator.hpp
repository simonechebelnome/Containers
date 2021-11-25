#ifndef ITERATOR_CLASS_HPP
# define ITERATOR_CLASS_HPP

# include "Iter_interface.hpp"

namespace ft {

    template <typename T>
    RanIter<T>::RanIter(void) : _value(NULL) {
        return ;
    }

    template <typename T>
    RanIter<T>::RanIter(T *src) : _value(src) {
        return ;
    }

    template <typename T>
    RanIter<T>::RanIter(RanIter const &copy) {
        *this = src;
    }

    template <typename T>
    RanIter<T>::~RanIter(void) {
        return ;
    }

    template <typename T>
    RanIter<T> &RanIter<T>::operator=(RanIter const &rhs) {
        if (this == &rhs)
            return (*this);
        *this->_value = rhs._value;
        return (*this);
    }

    template <typename T>
    bool RanIter<T>::operator==(RanIter const &rhs) const {
        return (this->_value == rhs._value);
    }

    template <typename T>
    bool RanIter<T>::operator!=(RanIter const &rhs) const {
        return (this->_value != rhs._value);
    }

    template <typename T>
    bool RanIter<T>::operator<(RanIter const &rhs) const {
        return (this->_value < rhs._value);
    }

    template <typename T>
    bool RanIter<T>::operator<=(RanIter const &rhs) const {
        return (this->_value <= rhs._value);
    }

    template <typename T>
    bool RanIter<T>::operator>(RanIter const &rhs) const {
        return (this->_value > rhs._value);
    }

    template <typename T>
    bool RanIter<T>::operator>=(RanIter const &rhs) const {
        return (this->_value >= rhs._value);
    }

    //? Queste due returnano l'RanItere prima che venga incrementato

    template <typename T>
    RanIter<T> RanIter<T>::operator++(int) {
        RanIter<T>	tmp(*this);
        ++this->_value;
        return(tmp);
    }

    template <typename T>
    RanIter<T> RanIter<T>::operator--(int) {
        RanIter<T>	tmp(*this);
        --this->_value;
        return(tmp);
    }

    //? Questi returnano con il valore già incrementato

    template <typename T>
    RanIter<T> &RanIter<T>::operator++(void) {
        ++this->_value;
        return(*this);
    }

    template <typename T>
    RanIter<T> &RanIter<T>::operator--(void) {
        --this->_value;
        return(*this);
    }

    template <typename T>
    typename RanIter<T>::difference_type
        RanIter<T>::operator-(RanIter const &rhs) const {
            return(this->_value - rhs._value);
    }

    template <typename T>
    RanIter<T>	RanIter<T>::operator+(difference_type n) const {
            return(RanIter(this->_value + n));
    }

    template <typename T>
    RanIter<T>	RanIter<T>::operator-(difference_type n) const {
            return(RanIter(this->_value - n));
    }
}

#endif