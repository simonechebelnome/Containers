#ifndef ITER_INTERFACE_HPP
# define ITER_INTERFACE_HPP

# include "Utils.hpp"

//? -- INTERFACCIA ITERATORE --
//* / Tutte le definizioni sono negli altri header file
namespace ft {

    template<typename T>
    class RanIter {
    protected:		
        T		*_value; //* Questo è un puntatore al tipo di elemento che è stato passato, ergo, ne stiamo storando il valore
    
    public:
        typedef T			value_type;
        typedef ptrdiff_t	difference_type; //* Ptrdiff stora la differenza tra due puntatori

        RanIter(void);
        RanIter(T *value); //* Qui possiamo passare un valore per inizializzare
        RanIter(RanIter const &copy);
        virtual ~RanIter(void);
        RanIter &operator=(RanIter const &rhs);

        //? Operator Override tra RanIteri

        bool	operator==(RanIter const &rhs) const;
        bool	operator!=(RanIter const &rhs) const;
        bool	operator<(RanIter const &rhs) const;
        bool	operator<=(RanIter const &rhs) const;
        bool	operator>(RanIter const &rhs) const;
        bool	operator>=(RanIter const &rhs) const;

        //? RanIter<T> restituisce un oggetto RanItere

        RanIter<T>	&operator++(void);
        RanIter<T>	&operator--(void);
        RanIter<T>	operator++(int);
        RanIter<T>	operator--(int);

        difference_type		operator-(RanIter const &rhs) const;
        RanIter<T>			operator+(difference_type n) const;
        RanIter<T>			operator-(difference_type n) const;

        //* I metodi definiti con friend possono anche essere usati singolarmente al di fuori dello scope della classe
        friend RanIter<T>	operator+(difference_type n, RanIter const &rhs)
            { return rhs.operator+(n); };	
    };
}

#endif