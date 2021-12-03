#ifndef LIST_HPP
# define LIST_HPP

# include "Utils.hpp"
# include "List_interface.hpp"

namespace ft {
    //* Ricorda che nodetype è definito come ft::lstNode<value_type> dove value_type == T
    //* Quindi quando creo un nuovo nodo con new node_type sto già assegnando T a data chiamando il costruttore del nodo
    template <typename T, typename Alloc>
    list<T, Alloc>::list(const allocator_type &alloc) : \
        _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        return ;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::list(size_type size, const value_type &val, const allocator_type &alloc) : \
        _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        this->_create_data(size, val);
        return ;
    }

    template <typename T, typename Alloc> template <class Ite>
    list<T, Alloc>::list(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
            Ite last, const allocator_type &alloc) : _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        this->_create_data_it(first, last);
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::list(list const &src) : _data(), _alloc(allocator_type()), _size(0) {
        this->_data = new node_type;
        *this = src;
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::~list(void) {
        this->_destroy_data();
        delete this->_data;
    }

    template<typename T, typename Alloc>
    list<T, Alloc>	&list<T, Alloc>::operator=(list const &rhs) {
        if (this == &rhs)
            return (*this);
        this->_create_data_it(rhs.begin(), rhs.end());
        return (*this);
    }

    //* ################### METODI ITERATORI ###################
    //? Ricorda che stai lavorando con un NODO SENTINELLA ed una LISTA CIRCOLARE!

    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::begin(void) {
        return iterator(this->_data->next);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin(void) const {
        return const_iterator(this->_data->next);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::end(void) {
        return iterator(this->_data);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::end(void) const {
        return const_iterator(this->_data);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin(void) {
        return reverse_iterator(this->end());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin(void) const {
        return const_reverse_iterator(this->end());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend(void) {
        return reverse_iterator(this->begin());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend(void) const {
        return const_reverse_iterator(this->begin());
    }

    //* ################### METODI CAPACITY ###################

    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::size(void) const {
        return (this->_size);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::max_size(void) const {
        return (_max_size);
    }

    template<typename T, typename Alloc>
    bool	list<T, Alloc>::empty(void) const {
        return (this->_size == 0 ? true : false);
    }

    //* ################### METODI ACCESSO ELEMENTI ###################

    template<typename T, typename Alloc> typename list<T, Alloc>::
    reference		list<T, Alloc>::front(void) {
        return *this->begin();
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    const_reference	list<T, Alloc>::front(void) const {
        return *this->begin();
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    reference		list<T, Alloc>::back(void) {
        return this->_data->prev->data;
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    const_reference	list<T, Alloc>::back(void) const {
        return this->_data->prev->data;
    }
    
    //* ################### METODI PRIVATI ###################

    template<typename T, typename Alloc> template <class Ite>
    void	list<T, Alloc>::_create_data_it(Ite first, Ite last) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite && first != last)
            *it++ = *first++;
        --it;
        while (it != --this->end())
            this->pop_back();
        while (first != last)
            this->push_back(*first++);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::_create_data(size_type size, const value_type &val) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite && size != 0)
        {
            *it++ = val;
            --size;
        }
        --it;
        while (it != --this->end())
            this->pop_back();
        while (size != 0)
        {
            this->push_back(val);
            --size;
        }
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::_destroy_data(void) {
        if (this->empty())
            return ;
        this->clear();
    }

    //? Creiamo una copia del nodo attuale e lo mettiamo in src, è una sorta di swap
    template<typename T, typename Alloc>
    void	list<T, Alloc>::_cpy_content(list<T, Alloc> &src) {
        this->clear();
        node_ptr tmp = this->_data;

        this->_data = src._data;
        this->_alloc = src._alloc;
        this->_size = src._size;
        src._data = tmp; src._size = 0;
        tmp = NULL; //! Mettiamo a Null dopo averlo utilizzato
    }

    //? Questa è la definizione della variabile statica _max_size
    template <typename T, typename Alloc>
    const typename list<T, Alloc>::size_type list<T, Alloc>::_max_size =
        std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1);

    }

#endif