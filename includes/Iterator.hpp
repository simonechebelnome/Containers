#ifndef ITERATOR_CLASS_HPP
# define ITERATOR_CLASS_HPP

# include "Iter_interface.hpp"

namespace ft {

    template <typename T>
    RandIte<T>::RandIte(void) : _value(NULL) {
        return ;
    }

    template <typename T>
    RandIte<T>::RandIte(T *src) : _value(src) {
        return ;
    }

    template <typename T>
    RandIte<T>::RandIte(RandIte const &copy) {
        *this = copy;
    }

    template <typename T>
    RandIte<T>::~RandIte(void) {
        return ;
    }

    template <typename T>
    RandIte<T> &RandIte<T>::operator=(RandIte const &rhs) {
        if (this == &rhs)
            return (*this);
        this->_value = rhs._value;
        return (*this);
    }

    template <typename T>
    bool RandIte<T>::operator==(RandIte const &rhs) const {
        return (this->_value == rhs._value);
    }

    template <typename T>
    bool RandIte<T>::operator!=(RandIte const &rhs) const {
        return (this->_value != rhs._value);
    }

    template <typename T>
    bool RandIte<T>::operator<(RandIte const &rhs) const {
        return (this->_value < rhs._value);
    }

    template <typename T>
    bool RandIte<T>::operator<=(RandIte const &rhs) const {
        return (this->_value <= rhs._value);
    }

    template <typename T>
    bool RandIte<T>::operator>(RandIte const &rhs) const {
        return (this->_value > rhs._value);
    }

    template <typename T>
    bool RandIte<T>::operator>=(RandIte const &rhs) const {
        return (this->_value >= rhs._value);
    }

    //? Queste due returnano l'RandItee prima che venga incrementato

    template <typename T>
    RandIte<T> RandIte<T>::operator++(int) {
        RandIte<T>	tmp(*this);
        ++this->_value;
        return(tmp);
    }

    template <typename T>
    RandIte<T> RandIte<T>::operator--(int) {
        RandIte<T>	tmp(*this);
        --this->_value;
        return(tmp);
    }

    //? Questi returnano con il valore già incrementato

    template <typename T>
    RandIte<T> &RandIte<T>::operator++(void) {
        ++this->_value;
        return(*this);
    }

    template <typename T>
    RandIte<T> &RandIte<T>::operator--(void) {
        --this->_value;
        return(*this);
    }

    template <typename T>
    typename RandIte<T>::difference_type
        RandIte<T>::operator-(RandIte const &rhs) const {
            return(this->_value - rhs._value);
    }

    template <typename T>
    RandIte<T>	RandIte<T>::operator+(difference_type n) const {
            return(RandIte(this->_value + n));
    }

    template <typename T>
    RandIte<T>	RandIte<T>::operator-(difference_type n) const {
            return(RandIte(this->_value - n));
    }
}

#endif