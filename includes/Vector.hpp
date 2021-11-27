#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Utils.hpp"
# include "Vec_interface.hpp"

namespace ft {

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(const allocator_type &alloc) : \
    _data(NULL), _alloc(alloc), _size(0), _capacity(0) { return; }

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(size_type size, const value_type &val,
        const allocator_type &alloc) : \
        _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
        this->_create_data(size, val);
        return;
    }

    template <typename T, typename Alloc> template <typename Ite>
    vector<T, Alloc>::vector(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
            Ite last, const allocator_type &alloc) : _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
        this->_create_data(ft::itlen(first, last), first, last);
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(vector const &src) : \
        _data(NULL), _alloc(allocator_type()), _size(0), _capacity(0) {
        *this = src;
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::~vector(void) {
        this->_destroy_data();
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>	&vector<T, Alloc>::operator=(vector const &rhs) {
        if (this == &rhs)
            return (*this);
        const_iterator first = rhs.begin();
        const_iterator last = rhs.end();
        size_type len = ft::itlen(first, last);
        this->_create_data((len > this->_capacity) ? len : this->_capacity, first, last);
        return (*this);
    }

    //* ##### IMPLEMENTAZIONE ITERATORI #####
    //? Nota come i tipi vadano ogni volta ridefiniti nell'implementazione

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    iterator vector<T, Alloc>::begin(void) {
        return (iterator(this->_data));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_iterator vector<T, Alloc>::begin(void) const {
        return (const_iterator(this->_data));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    iterator vector<T, Alloc>::end(void) {
        return (iterator(&this->_data[this->_size]));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_iterator vector<T, Alloc>::end(void) const {
        return (const_iterator(&this->_data[this->_size]));
    }

    //! Nota come per il reverse_iterator il return value sia INVERTITO!
    
    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reverse_iterator vector<T, Alloc>::rbegin(void) {
        return (reverse_iterator(&this->_data[this->_size]));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reverse_iterator vector<T, Alloc>::rbegin(void) const {
        return (const_reverse_iterator(&this->_data[this->_size]));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reverse_iterator vector<T, Alloc>::rend(void) {
        return (reverse_iterator(this->_data));
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reverse_iterator vector<T, Alloc>::rend(void) const {
        return (const_reverse_iterator(this->_data));
    }

    //* ###### CAPACITY ######

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    size_type vector<T, Alloc>::size(void) const {
        return(this->_size);
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    size_type vector<T, Alloc>::capacity(void) const {
        return(this->_capacity);
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    size_type vector<T, Alloc>::max_size(void) const {
        return(this->_max_size);
    }

    template<typename T, typename Alloc>
    bool vector<T, Alloc>::empty(void) const {
        return(this->size == 0 ? true : false);
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::reserve(size_type n) {
        //* Controlliamo inanzitutto che n non sia più grande della dimensione massima
        if(n > this->max_size())
            throw std::length_error("error:: 'n' exceeds maximum storage value");
        //* Allo stesso tempo, non ha senso riservare spazio minore della capacity
        //? Reminder che la capacity rappresenta il NUMERO CORRENTE di elementi nel vettore
        if(n <= this->capacity())
            return ;
        this->_create_data(n, this->begin(), this->end());
    }

    template<typename T, typename Alloc>
    void		vector<T, Alloc>::resize(size_type size, value_type val) {
        if (size < this->_size)
        {
            //* Se il size che passiamo è minore, distruggiamo tutto quello che viene dopo
            while (size < this->_size)
                this->_alloc.destroy(&this->_data[--this->_size]);
        }
        else
        {
            size_type const &lambda = this->_size;

            //* Se size è maggiore del _size attuale, tocca reallocare
            if (size <= this->_capacity)
                ;
            else if (size <= lambda * 2)
                this->reserve(lambda * 2);
            else
                this->reserve(size);
            while (this->_size < size)
                this->_alloc.construct(&this->_data[this->_size++], val);
        }
    }

    //* ##### ACCESSO ELEMENTI #####

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reference		vector<T, Alloc>::operator[](size_type n) {
        return this->_data[n];
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reference	vector<T, Alloc>::operator[](size_type n) const {
        return this->_data[n];
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reference		vector<T, Alloc>::at(size_type n) {
        if (n < this->_size)
            return ((*this)[n]);
        throw std::out_of_range("error:: n is out of range");
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reference	vector<T, Alloc>::at(size_type n) const {
        if (n < this->_size)
            return ((*this)[n]);
        throw std::out_of_range("error:: n is out of range");
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reference		vector<T, Alloc>::front(void) {
        return (*this)[0];
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reference	vector<T, Alloc>::front(void) const {
        return (*this)[0];
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    reference		vector<T, Alloc>::back(void) {
        return (*this)[this->_size - 1];
    }

    template<typename T, typename Alloc> typename vector<T, Alloc>::
    const_reference	vector<T, Alloc>::back(void) const {
        return (*this)[this->_size - 1];
    }

    //* ------ ATTRIBUTI PRIVATI -------

    template<typename T, typename Alloc> template <class Ite>
    void	vector<T, Alloc>::_create_data(difference_type capacity, Ite first, Ite last) {
        vector<T, Alloc> res;
        difference_type len = ft::itlen(first, last);

        if (capacity < len || capacity < 0)
            throw std::bad_alloc();
        res._alloc = this->_alloc;
        res._size = len; res._capacity = capacity;
        res._data = res._alloc.allocate(capacity);
        for (size_type i = 0; first != last; ++first)
            res._alloc.construct(&res._data[i++], *first);
        this->_destroy_data();
        this->_cpy_content(res);
    }

    template<typename T, typename Alloc>
    void	vector<T, Alloc>::_create_data(size_type size, const value_type &val) {
        this->_destroy_data();
        this->_data = this->_alloc.allocate(size);
        for (size_type i = 0; i < size; ++i)
            this->_alloc.construct(&this->_data[i], val); //? Construct, appunto, costruisce l'oggetto con i valori effettivi
        this->_size = size; this->_capacity = size; //? Nota come l'assegnazione venga fatta qui e non nel costruttore
    }

    template<typename T, typename Alloc>
    void	vector<T, Alloc>::_destroy_data(void) {
        if (!this->_data)
            return ;
        this->clear();
        this->_alloc.deallocate(this->_data, this->_capacity);
        this->_data = NULL; this->_size = 0; this->_capacity = 0;
    }

    template<typename T, typename Alloc> template <class Ite, class Iterator>
    void	vector<T, Alloc>::_cpy_data(Ite start, Iterator first, Iterator last) {
        while (first != last)
        {
            *start = *first;
            ++start;
            ++first;
        }
    }

    //? Copia il contenuto di un vettore passato come parametro nell'istanza dell'oggetto attuale
    //? Serve poichè nel primo _create_data ci appoggiamo ad un vettore temporaneo
    template<typename T, typename Alloc>
    void	vector<T, Alloc>::_cpy_content(vector<T, Alloc> &vct) {
        this->_data = vct._data;
        this->_alloc = vct._alloc;
        this->_size = vct._size;
        this->_capacity = vct._capacity;
        vct._data = NULL; vct._size = 0; vct._capacity = 0;
    }
}
# endif