#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "Utils.hpp"
# include "Iterator.hpp"

namespace ft {
	template<typename T>
	class reverseIterator {
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

		reverseIterator(void);
		explicit reverseIterator(T iter); //! Con explicit questo costruttore non può effettuare conversioni implicite
		reverseIterator(reverseIterator const &copy);
		reverseIterator &operator=(reverseIterator const &copy);
		T base(void) const { return this->_base };

		//* I metodi seguenti potranno essere usati solo dalle classi che ereditano (super si riferisce alla base class, questa)
		reference	operator*(void) const { return(--super(this->_base)).operator*(); }
		pointer		operator->(void) const { return &this->operator*(); }

		//? OPERATOR CON REFERENCE & = SUFFISSO
		//? OPERATOR CON PARAMETRO(INT) = PREFISSO
		//! Si tratta semplicemente di rendere il codice più leggibile e funzionale (passo 0 perchè di fatto non mi serve a niente l'argomento)
		reverseIterator	&operator++(void) { this->_base.operator--(); return *this; };
		reverseIterator	operator++(int) { return reverseIterator(this->_base.operator--(0)); };
		reverseIterator	&operator--(void) { this->_base.operator++(); return *this; };
		reverseIterator	operator--(int) { return reverseIterator(this->_base.operator++(0)); };

		difference_type	operator-(reverseIterator const &u) { return u.base().operator-(this->_base); };
		reverseIterator	operator+ (difference_type n) const { return reverseIterator(this->_base.operator-(n)); };
		reverseIterator	&operator+=(difference_type n) { this->_base.operator-=(n); return *this; };
		reverseIterator	operator- (difference_type n) const { return reverseIterator(this->_base.operator+(n)); };
		reverseIterator	&operator-=(difference_type n) { this->_base.operator+=(n); return *this; };
		reference		operator[](difference_type n) const { return *this->operator+(n); };

        //* Dato che stiamo usando friend sappiamo a priori che questo metodo sarà utilizzato al di fuori della classe
        //! Di conseguenza, l'operator overload DEVE PRENDERE DUE ARGOMENTI (lhs, rhs). Di norma il lhs è l'oggetto stesso (this) e non deve essere specificato
        friend reverseIterator operator+(difference_type n, const reverseIterator &rhs)
			{ return rhs.operator+(n); };
        
        template <class U> bool	operator==(const reverseIterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
		template <class U> bool	operator!=(const reverseIterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
		template <class U> bool	operator< (const reverseIterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
		template <class U> bool	operator<=(const reverseIterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
		template <class U> bool	operator> (const reverseIterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
		template <class U> bool	operator>=(const reverseIterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };
	};

    template <typename T>
    reverseIterator<T>::reverseIterator(void) : _base() { };

    template <typename T>
    reverseIterator<T>::reverseIterator(T x) : _base(x) { };

    template <typename T>
    reverseIterator<T>::reverseIterator(reverseIterator const &copy) : _base(u.base()) { };

    template <typename T>
    reverseIterator<T> &reverseIterator<T>::operator=(reverseIterator const &copy) {
        //* Usiamo un reinterpret cast per assicurarci che i due iteratori siano effettivamente uguali (cioè abbiano lo stesso valore)
        if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
            return (*this);
        this->_base = u.base();
        return (*this);
    };
}

#endif