#ifndef ITER_INTERFACE_HPP
# define ITER_INTERFACE_HPP

# include "Utils.hpp"

//? -- INTERFACCIA ITERATORE --
//* / Tutte le definizioni sono negli altri header file
namespace ft {

	template<typename T>
	class Iterator {
	protected:		
		T		*_value; //* Questo è un puntatore al tipo di elemento che è stato passato, ergo, ne stiamo storando il valore
	
	public:
		typedef T			value_type;
		typedef ptrdiff_t	difference_type; //* Ptrdiff stora la differenza tra due puntatori

		Iterator(void);
		Iterator(T *value); //* Qui possiamo passare un valore per inizializzare
		Iterator(Iterator const &copy);
		virtual ~Iterator(void);
		Iterator &operator=(Iterator const &rhs);

		//? Operator Override tra Iteratori

		bool	operator==(Iterator const &rhs) const;
		bool	operator!=(Iterator const &rhs) const;
		bool	operator<(Iterator const &rhs) const;
		bool	operator<=(Iterator const &rhs) const;
		bool	operator>(Iterator const &rhs) const;
		bool	operator>=(Iterator const &rhs) const;

		//? Iterator<T> restituisce un oggetto iteratore

		Iterator<T>	&operator++(void);
		Iterator<T>	&operator--(void);
		Iterator<T>	operator++(int);
		Iterator<T>	operator--(int);

		difference_type		operator-(Iterator const &rhs) const;
		Iterator<T>			operator+(difference_type n) const;
		Iterator<T>			operator-(difference_type n) const;

		//* I metodi definiti con friend possono anche essere usati singolarmente al di fuori dello scope della classe
		friend Iterator<T>	operator+(difference_type n, Iterator const &rhs)
			{ return rhs.operator+(n); };	
	};
}

#endif