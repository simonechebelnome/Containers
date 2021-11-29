#ifndef ITER_INTERFACE_HPP
# define ITER_INTERFACE_HPP

# include "Utils.hpp"

//? -- INTERFACCIA ITERATORE --
//* / Tutte le definizioni sono negli altri header file
namespace ft {

    template<typename T>
    class RandIte {
    protected:		
        T		*_value; //* Questo è un puntatore al tipo di elemento che è stato passato, ergo, ne stiamo storando il valore
    
    public:
        typedef T			value_type;
        typedef ptrdiff_t	difference_type; //* Ptrdiff stora la differenza tra due puntatori

        RandIte(void);
        RandIte(T *value); //* Qui possiamo passare un valore per inizializzare
        RandIte(RandIte const &copy);
        virtual ~RandIte(void);
        RandIte &operator=(RandIte const &rhs);

        //? Operator Override tra RandItei

        bool	operator==(RandIte const &rhs) const;
        bool	operator!=(RandIte const &rhs) const;
        bool	operator<(RandIte const &rhs) const;
        bool	operator<=(RandIte const &rhs) const;
        bool	operator>(RandIte const &rhs) const;
        bool	operator>=(RandIte const &rhs) const;

        //? RandIte<T> restituisce un oggetto RandItee

        RandIte<T>	&operator++(void);
        RandIte<T>	&operator--(void);
        RandIte<T>	operator++(int);
        RandIte<T>	operator--(int);

        difference_type		operator-(RandIte const &rhs) const;
        RandIte<T>			operator+(difference_type n) const;
        RandIte<T>			operator-(difference_type n) const;

        //* I metodi definiti con friend possono anche essere usati singolarmente al di fuori dello scope della classe
        friend RandIte<T>	operator+(difference_type n, RandIte const &rhs)
            { return rhs.operator+(n); };	
    };
}

#endif