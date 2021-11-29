#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef>
# include <sstream>

namespace ft {

    //? choose <bool, true, false>
    //* Dato un booleano, sceglie uno dei due parametri

    template <bool flag, typename isTrue, typename isFalse>
    struct choose;

    template <typename isTrue, typename isFalse>
    struct choose<true, isTrue, isFalse> {
        typedef isTrue type;
    };

    template <typename isTrue, typename isFalse>
    struct choose<false, isTrue, isFalse> {
        typedef isFalse type;
    };

    //? enable_if <bool, true>
    //* Se vero, definisce come type il tipo generico passato

    template <bool, class isTrue = void>
    struct enable_if;

    template <typename isTrue>
    struct enable_if <true, isTrue> {
        typedef isTrue type;
    };

    //! OPERATORI RELAZIONALI FRA ITERATORI
    //? Controllo Uguaglianza

    template <typename Iter1, typename Iter2>
    bool equal(Iter1 first1, Iter1 last1, Iter2 first2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    //? Lunghezza Iteratori

    template <typename Iter>
    size_t itlen(Iter first, Iter last) {
        size_t i = 0;
        
        while (first != last) {
            ++first;
            ++i;
        }
        return (i);
    }

    //? Lexicographical Compare (Praticamente ha lo stesso funzionamento di strcmp)

    template <typename Iter1, typename Iter2>
    bool lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
    {
        while (first1 != last1 && first2 != last2 && *first1 == *first2) {
            ++first1;
            ++first2;
        }
        if (first1 == last1)
            return (first2 != last2);
        else if (first2 == last2)
            return (false);
        return (*first1 < *first2);
    }

    //? Uno Struct è tecnicamente COME UNA CLASSE (puù avere un costruttore e dei metodi come nel caso qui sotto)
    //? L'unica differenza è che di default i suoi membri vengono inizializzati come pubblici (nelle classi come privati)

    template<typename T>
    struct lstNode {
        T           data;
        lstNode     *prev;
        lstNode     *next;

        //* Di default, il nodo precedente ed il successivo sono lo stesso. Ricorda inoltre di chiamare il costruttore di T!
        lstNode(const T &src = T()) : data(src), prev(this), next(this) {};
    };
    
}

#endif