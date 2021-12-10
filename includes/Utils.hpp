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

    //? Uno Struct è tecnicamente COME UNA CLASSE (può avere un costruttore e dei metodi come nel caso qui sotto)
    //? L'unica differenza è che di default i suoi membri vengono inizializzati come pubblici (nelle classi come privati)

    //? Ora, questa è una figata. Questo è chiamato NODO SENTINELLA, è una sorta di "dummy node" che viene sfruttato per le DOUBLY LINKED LIST
    //? Ricorda che stai lavorando con una LISTA CIRCOLARE, quindi questo nodo sentinella è SIA L'INIZIO CHE LA FINE
    //? Più precisamente, qui NEXT punta al primo Elemento, mentre PREV punta all'ultimo. E' un ciclo!.
    //! Non dobbiamo stare neanche ad aggiornare i puntatori, basta inseirire elementi prima/dopo il nodo sentinella e veranno gestiti automaticamente
    template<typename T>
    struct lstNode {
        T           data;
        lstNode     *prev;
        lstNode     *next;

        //* Di default, il nodo precedente ed il successivo sono lo stesso. Ricorda inoltre di chiamare il costruttore di T!    
        lstNode(const T &src = T()) : data(src), prev(this), next(this) {};
    };
    
    //? Veniamo ora alle MAPPE. Cosa stiamo astraendo questa volta? Un albero di ricerca binario.
    //? Il nodo in questo caso avrà ovviamente, i nodi figli (destra e sinistra) ed il parent (quello che generalmente viene definito root)

    template <typename T>
    struct mapNode {
        T           data;
        mapNode     *parent;
        mapNode     *left;
        mapNode     *right;

        mapNode(const T &src = T()) :
            data(src), parent(NULL), left(NULL), right(NULL) {}; 
    };

    //? Per l'ordinamento e la ricerca dei valori nell'albero, avremo spesso bisogno di scorrere tutto a destra o tutto a sinistra
    //? Le prossime due funzioni fanno esattamente questo

    template <typename T>
    mapNode<T>  *farLeft(mapNode<T> *node){
        while(node->left != NULL)
            node = node->left;
        return(node);
    }

    template <typename T>
    mapNode<T>  *farRight(mapNode<T> *node){
        while(node->right != NULL)
            node = node->right;
        return(node);
    }

    //? Definiamo ora lo struct per un pair, cosa intendiamo per pair?
    //? Banalmente, una cokppia di elementi (first, second) di TIPO DIVERSO
    //? Ne abbiamo bisogno per ft::map, perchè ogni nodo contiene una chiave e l'elemento ad esso associato

    template <typename T1, typename T2>
    struct pair {
        typedef T1      first_type;
        typedef T2      second_type;

        first_type      first;
        second_type     second;

        //* Member elements
        pair(void) : first(), second() {};
        template<typename F, typename S>
        pair(const pair<F, S> &src) : first(src.first), second(src.second) {}; //* Questo è praticamente un copy constructor, costruisco partendo da un altro pair
        pair(const first_type &a, const second_type &b) : first(a), second(b) {};

        pair &operator=(const pair &src) {
            if (*this == src)
                return (*this);
            this->first = src.first;
            this->second = src.second;
            return (*this);
        }
    };

    //* Pair ha tutti i suoi overloads, che sono riportati di seguito

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator< (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator> (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs < rhs);
    }

}
#endif