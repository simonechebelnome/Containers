#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "Utils.hpp"
# include "Iterator.hpp"

namespace ft {
    template<typename T>
    class reverse_iterator {
    protected:
        //* Si, è normale avere più typedef per lo stesso valore
        typedef T   super;
        T           _base; //* Base altro non è che il VALORE dell'iteratore, quello che passiamo al costruttore
    public:
        typedef T									iterator_type;
        //* Qui typename semplicemente ci indica che dopo lo scope operator non c'è un metodo ma, appunto, un tipo
        typedef typename super::difference_type		difference_type;
        typedef typename super::reference			reference;
        typedef typename super::pointer				pointer;

        reverse_iterator(void);
        explicit reverse_iterator(T iter); //! Con explicit questo costruttore non può effettuare conversioni implicite
        reverse_iterator(reverse_iterator const &copy);
        reverse_iterator &operator=(reverse_iterator const &copy);
        T base(void) const { return this->_base; };

        //* I metodi seguenti potranno essere usati solo dalle classi che ereditano (super si riferisce alla base class, questa)
        reference	operator*(void) const { return(--super(this->_base)).operator*(); }
        pointer		operator->(void) const { return &this->operator*(); }

        //? OPERATOR CON REFERENCE & = SUFFISSO
        //? OPERATOR CON PARAMETRO(INT) = PREFISSO
        //! Si tratta semplicemente di rendere il codice più leggibile e funzionale (passo 0 perchè di fatto non mi serve a niente l'argomento)
        reverse_iterator	&operator++(void) { this->_base.operator--(); return *this; };
        reverse_iterator	operator++(int) { return reverse_iterator(this->_base.operator--(0)); };
        reverse_iterator	&operator--(void) { this->_base.operator++(); return *this; };
        reverse_iterator	operator--(int) { return reverse_iterator(this->_base.operator++(0)); };

        difference_type	operator-(reverse_iterator const &u) { return u.base().operator-(this->_base); };
        reverse_iterator	operator+ (difference_type n) const { return reverse_iterator(this->_base.operator-(n)); };
        reverse_iterator	&operator+=(difference_type n) { this->_base.operator-=(n); return *this; };
        reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };
        reverse_iterator	&operator-=(difference_type n) { this->_base.operator+=(n); return *this; };
        reference		operator[](difference_type n) const { return *this->operator+(n); };

        //* Dato che stiamo usando friend sappiamo a priori che questo metodo sarà utilizzato al di fuori della classe
        //! Di conseguenza, l'operator overload DEVE PRENDERE DUE ARGOMENTI (lhs, rhs). Di norma il lhs è l'oggetto stesso (this) e non deve essere specificato
        friend reverse_iterator operator+(difference_type n, const reverse_iterator &rhs)
            { return rhs.operator+(n); };
        
        template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
        template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
        template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
        template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
        template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
        template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };
    };

    template <typename T>
    reverse_iterator<T>::reverse_iterator(void) : _base() { };

    template <typename T>
    reverse_iterator<T>::reverse_iterator(T x) : _base(x) { };

    template <typename T>
    reverse_iterator<T>::reverse_iterator(reverse_iterator const &copy) : _base(copy.base()) { };

    template <typename T>
    reverse_iterator<T> &reverse_iterator<T>::operator=(reverse_iterator const &copy) {
        //* Usiamo un reinterpret cast per assicurarci che i due iteratori siano effettivamente uguali (cioè abbiano lo stesso valore)
        if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&copy))
            return (*this);
        this->_base = copy.base();
        return (*this);
    };
}

#endif