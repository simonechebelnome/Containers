#ifndef VECTOR_INTERFACE_HPP
# define VECTOR_INTERFACE_HPP

# include "Iterator.hpp"
# include "Rev_iterator.hpp"
# include "Utils.hpp"

namespace ft {
    template<typename T, typename Allocator = std::allocator<T>>
    class vector {
    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;   
        typedef typename allocator_type::reference			reference;
        typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer			pointer;
        typedef typename allocator_type::const_pointer		const_pointer;

        typedef ptrdiff_t									difference_type;
        typedef size_t										size_type;

        //* Iterator è una classe nestata, per enfatizzare che fa parte di questa specifica interfaccia e che si usano con oggetti di tipo Vector
        //? Quando erediti da un template devi necessariamente specificare il tipo tra le parentesi angolari <>, questo perchè RanIter preso singolarmente NON E' UNA CLASSE
        //? RanIter preso da solo è un class Template, ovvero un blueprint per la generazione di classi. Classi possono essere RanIter<int> o RanIter<std::string>
        class iterator : public RanIter<value_type> {
        protected:
            typedef RanIter<value_type>     super;
            iterator(value_type *src) : RanIter<value_type>(src) {}; //* Qui ci basta semplicemente chiamare il costruttore della base class
        
        private:
            iterator(const RanIter<value_type> &copy) : RanIter<value_type>(src) {}; //* Copy Constructor base class

        public:
            iterator(void) : RandIte<value_type>() {}; //* Default Constructor
            iterator(const iterator &src) : RandIte<value_type>(src) {}; //* Copy Constructor default

            typedef value_type&     reference;
            typedef value_type*     pointer;

            //! Gli operatori += e -= returnano SEMPRE UNA REFERENCE. Questo perchè stiamo returnando un'istanza modificata di quell'oggetto.
            //? Altri operatori (come +), modificano quell'oggetto in modo locale e devono returnare un valore

            reference			operator*(void) const;
            pointer				operator->(void) const;
            iterator		    &operator+=(difference_type n);
            iterator		    &operator-=(difference_type n);
            reference			operator[](difference_type n) const;

            //* Per le seguenti posso direttamente utilizzare i metodi della base class (super)

            difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
            iterator			operator-(difference_type n) const { return super::operator-(n); };
            iterator			operator+(difference_type n) const { return super::operator+(n); };
            friend iterator		operator+(difference_type n, const iterator &rhs) { return rhs.operator+(n); }; //? Lo stesso di sopra, ma può essere utilizzato fuori dalla classe

            //* Ricordati ciò che si è detto su prefisso/suffisso (reverse_iterator)

            iterator			&operator++(void) { super::operator++(); return *this; };
            iterator			operator++(int) { return super::operator++(0); };
            iterator			&operator--(void) { super::operator--(); return *this; };
            iterator			operator--(int) { return super::operator--(0); };

            //? Diamo a vector la possibilità di accedere a tutti i membri di questa classe, chiaramente
            friend class vector;
        };

        //? Non basta, serve anche un CONST_ITERATOR. Ovvero, un iterator che non ci consente di modificare il valore a cui sta puntando.
        //* L'implementazione è identica a quella dell'iteratore normale, semplicemente punta ad un const value (const T*)

        class const_iterator : public RanIter<value_type> {
        protected:
            typedef RandIte<value_type> super;
            const_iterator(value_type *src) : RandIte<value_type>(src) {};

        public:
            const_iterator(void) : RandIte<value_type>() {};
            const_iterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

            typedef const value_type&		reference;
            typedef const value_type*		pointer;

            reference			operator*(void) const;
            pointer				operator->(void) const;
            const_iterator		&operator+=(difference_type n);
            const_iterator		&operator-=(difference_type n);
            reference			operator[](difference_type n) const;

            difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
            const_iterator		operator-(difference_type n) const { return super::operator-(n); };
            const_iterator		operator+(difference_type n) const { return super::operator+(n); };
            friend const_iterator	operator+(difference_type n, const const_iterator &rhs) { return rhs.operator+(n); };

            const_iterator		&operator++(void) { super::operator++(); return *this; };
            const_iterator		operator++(int) { return super::operator++(0); };
            const_iterator		&operator--(void) { super::operator--(); return *this; };
            const_iterator		operator--(int) { return super::operator--(0); };

            friend class vector;
        };

        //* Infine, definiamo come tipi anche i due reverse_iterator
        typedef ft::reverse_iterator<iterator>			reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

        //* ------------- METODI CLASSE -------------
        
        explicit vector(const allocator_type &alloc = allocator_type()); //* Qui sto chiamando il costruttore di std::allocator
        explicit vector(size_type size, const value_type &val = value_type(),
            const allocator_type &alloc = allocator_type());
        //? Enable if "abilita" quel tipo (Ite) solo se la condizione è vera, altrimenti non compila
        //! Il typename è valido qui sia per first che per last (sono entrambi Ite)
        template<typename Ite>
        vector(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
            Ite last, const allocator_type &alloc = allocator_type());
        vector(const vector &src);
        virtual ~vector(void);

        vector &operator=(const vector &rhs);

        //* ###### METODI ITERATORI ######

        iterator                begin(void);
        const_iterator          begin(void) const;
        iterator                end(void);
        const_iterator          end(void) const;

        reverse_iterator        rbegin(void);
        const_reverse_iterator  rbegin(void) const;
        reverse_iterator        rend(void);
        const_reverse_iterator  rend(void) const;

        //* ###### METODI CAPACITY ######

        //? I primi tre sono sostanzialmente getter
        size_type   size(void) const;
        size_type   capacity(void) const;
        size_type   max_size(void) const;
        bool        empty(void) const;
        void        reserve(size_type n);

        void        resize(size_type size, value_type val = value_type());

        //* ###### METODI ACCESSO ELEMENTI ######
        //? La differenza fra [] e at() è che at controlla che l'index non sia out of bound
        //? e throwa un'exception, l'element access operator non esegue questo controllo

        reference           operator[](size_type n);
        const_reference     operator[](size_type n) const;
        reference           at(size_type n);
        const_reference     at(size_type n) const;
        reference           front(void);
        const_reference     front(void) const;
        reference           back(void);
        const_reference     back(void) const;

        //* ##### MODIFICATORI #####

        template <class Ite>
        void		assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last);
        void		assign(size_type n, const value_type &val);
        void		push_back(const value_type &val);
        void		pop_back(void);

        //? Gli insert sono un pò bastardi, inseriscono elementi a partire dalla posizione specificata
        //? Quindi se la nuova size supera la capacity attuale (cioè tipo sempre) siamo costretti a reallocare
        //? Questo è ciò che rende i vettori relativamente LENTI rispetto ad altri tipi di container

        //* Possiamo scegliere se addare un singolo elemento, fillare (sempre dello stesso elemento) o copiare un range
        //* Chiaramente, per il range occorre sempre l'enable_if, solita storia

        iterator	insert(iterator position, const value_type &val); //! Questa returna un iteratore che punta all'elemento inserito
        void		insert(iterator position, size_type n, const value_type &val);
        template <class Ite>
            void	insert(iterator position, Ite first,
                typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last);

        iterator	erase(iterator ite);
        iterator	erase(iterator first, iterator last);
        void		swap(vector &x);
        void		clear(void);
        
    private:
        //* ------------- ATTRIBUTI CLASSE -------------
        //? Devo metterli necessariamente in fondo poichè devono essere privati
        value_type              *_data;
        allocator_type			_alloc;
        size_type				_size;
        size_type				_capacity;
        const static size_type	_max_size; //! Le variabili statiche non vanno mai inizializzate dal costruttore

        //? I metodi che seguono gestiscono L'ALLOCAZIONE DI MEMORIA
        //? Abbiamo due create data, in uno è possibile definire un RANGE usando gli iteratori
        template<typename Ite>
        void            _create_data(difference_type capacity, Ite first, Ite last);
        void            _create_data(size_type size, const value_type &val = value_type());
        void            _destroy_data(void);
        template<typename Ite, typename Iterator>
        static void     _cpy_data(Ite start, Iterator first, Iterator last);
        void            _cpy_content(vector &vct);


    };
}
#endif