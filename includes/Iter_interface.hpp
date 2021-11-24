#ifndef ITER_INTERFACE_HPP
# define ITER_INTERFACE_HPP

# include "Utils.hpp"

//? -- INTERFACCIA ITERATORE --
//* / Tutte le definizioni sono negli altri header file
namespace ft {

	template<typename T>
	class iterator {
	protected:		
		T		*_value; //* Questo è un puntatore al tipo di elemento che è stato passato, ergo, ne stiamo storando il valore
	
	public:
		typedef T			value_type;
		typedef ptrdiff_t	difference_type; //* Ptrdiff stora la differenza tra due puntatori

		iterator(void);
		iterator(T *value); //* Qui possiamo passare un valore per inizializzare
		iterator(iterator const &copy);
		virtual ~iterator(void);
		iterator &operator=(iterator const &rhs);

		//? Operator Override tra iteratori

		bool	operator==(iterator const &rhs) const;
		bool	operator!=(iterator const &rhs) const;
		bool	operator<(iterator const &rhs) const;
		bool	operator<=(iterator const &rhs) const;
		bool	operator>(iterator const &rhs) const;
		bool	operator>=(iterator const &rhs) const;

		//? iterator<T> restituisce un oggetto iteratore

		iterator<T>	&operator++(void);
		iterator<T>	&operator--(void);
		iterator<T>	operator++(int);
		iterator<T>	operator--(int);

		difference_type		operator-(iterator const &rhs) const;
		iterator<T>			operator+(difference_type n) const;
		iterator<T>			operator-(difference_type n) const;

		//* I metodi definiti con friend possono anche essere usati singolarmente al di fuori dello scope della classe
		friend iterator<T>	operator+(difference_type n, iterator const &rhs)
			{ return rhs.operator+(n); };	
	};
}

#endif