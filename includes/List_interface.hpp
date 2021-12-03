#ifndef LIST_INTERFACE_HPP
# define LIST_INTERFACE_HPP

# include "Utils.hpp"
# include "List_iterator.hpp"
# include "Rev_iterator.hpp"

//! DIFFERENZA FRA STD::VECTOR E STD::LIST
//? La differenza principale è che Vector lavora in uno spazio di memoria CONTIGUO, mentre List NO
//? Ciò significa che, ad esempio, sulle liste NON POSSO USARE IL RANDOM ACCESS. Se voglio un elemento specifico
//? Devo prima girarmi tutta la lista. Tuttavia, INSERIRE/ELIMINARE elementi sulle liste è PIU' FACILE, basta SCAMBIARE I PUNTATORI
//? Infine le liste hanno dei METODI SPECIALI che Vector non possiede. Questi metodi funzionano bene con std::algorithm

namespace ft {

    //* Non ti sorprenderà vedere come l'interfaccia sia praticamente quasi la stessa di Vector
    template < typename T, typename Alloc = std::allocator<T> >
    class list {
    public:
        typedef T											value_type;
        typedef Alloc										allocator_type;
        typedef typename allocator_type::reference			reference;
        typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer			pointer;
        typedef typename allocator_type::const_pointer		const_pointer;

        //? Qui ci andiamo a prendere lo struct dentro "Utils.hpp" che definisce il nodo!
        typedef ft::lstNode<value_type>						node_type;
        typedef node_type*									node_ptr;

        typedef ptrdiff_t									difference_type;
        typedef size_t										size_type;

        typedef ft::lstIte<value_type, node_type>			iterator;
        typedef ft::lstIte<const value_type, node_type>		const_iterator;
        typedef ft::reverse_iterator<iterator>				reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator

        //* #################### FUNZIONI MEMBRO ####################

        //! Ma che cazzo? Questo typedef non viene riconosciuto da VsCode....
        //TODO RISOLVI QUESTA ROBA IN QUALCHE MODO
        explicit list(const allocator_type &alloc = allocator_type());
        explicit list(size_type size, const value_type &val = value_type(),
            const allocator_type &alloc = allocator_type());
        template <class Ite>
        list(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
                Ite last, const allocator_type &alloc = allocator_type());
        list(const list &src);
        virtual ~list(void);

        list	&operator=(list const &rhs);

        //* #################### Iteratori ####################

        iterator		begin(void);
        const_iterator	begin(void) const;
        iterator		end(void);
        const_iterator	end(void) const;

        reverse_iterator		rbegin(void);
        const_reverse_iterator	rbegin(void) const;
        reverse_iterator		rend(void);
        const_reverse_iterator	rend(void) const;

        //* #################### Capacità ####################

        size_type	size(void) const;
        size_type	max_size(void) const;
        bool		empty(void) const;
        
        //* #################### Accesso Elementi ####################
        //? Nota come manchi il random access operator [] per il discorso di prima

        reference			front(void);
        const_reference		front(void) const;
        reference			back(void);
        const_reference		back(void) const;

        //* #################### Modificatori ####################

        template <class Ite>
        void		assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last);
        void		assign(size_type n, const value_type &val);

        //? Questi due sono nuovi, nel Vector ci era concesso aggiungere/eliminare solo dalla coda
        void		push_front(const value_type &val);
        void		pop_front(void);

        void		push_back(const value_type &val);
        void		pop_back(void);

        iterator	insert(iterator position, const value_type &val);
        void		insert(iterator position, size_type n, const value_type &val);
        template <class Ite>
        void	insert(iterator position, Ite first,
            typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last);

        iterator	erase(iterator ite);
        iterator	erase(iterator first, iterator last);
        void		swap(list &x);
        void		clear(void);

        //? Resize era anche in Vector, ma era nella - Capacity - e non nei - Modificatori -
        void		resize(size_type n, const value_type &val = value_type());

        //* #################### Metodi Speciali (Operazioni) ####################
        //? Vector è praticamente l'unico container a non disporne

        //? Splice trasferisce elementi da una lista all'altra
        //? Posso trasferli tutti (1), solo uno (2), oppure trasferire quelli in un range (3)
        void		splice(iterator position, list &x);
        void		splice(iterator position, list &x, iterator i);
        void		splice(iterator position, list &x, iterator first, iterator last);

        //? Remove_if rimuove tutti gli elementi che soddisfano la condizione espressa da Predicate (quindi se è True)
        //? Remove banalmente rimuove tutti gli elementi che corrispondono al valore passato come parametro
        template <class Predicate>
        void		remove_if(Predicate pred);
        void		remove(const value_type &val);

        //? Unique rimuove elementi uguali e consecutivi lasciandone solo uno
        template <class BinaryPredicate>
        void		unique(BinaryPredicate binary_pred);
        void		unique(void);

        //? Merge unisce due liste e le sorta, la lista 'x' viene letteralmente trasferita e quindi si svuota.
        //? Con Compare è possibile specificare il metodo per sortare, altrimenti i valori sono ordinati in modo ascendente
        template <class Compare>
        void		merge(list &x, Compare comp);
        void		merge(list &x);

        //? Sort, per l'appunto, ordina lista. Il funzionamento è identico al sort che ho descritto sopra
        template <class Compare>
        void		sort(Compare comp); 
        void		sort(void);

        //? Inverte la lista
        void		reverse(void);

        //* #################### DATI PRIVATI ####################
        
    private:
        node_ptr                _data;
        allocator_type          _alloc;
        size_type               _size;
        const static size_type  _max_size;

        //? Creare, distruggere e copiare data. Il funzionamento è lo stesso di Vector ma cambia l'implementazione.
        template <class Ite>
        void				_create_data_it(Ite first, Ite last);
        void				_create_data(size_type size, const value_type &val = value_type());
        void				_destroy_data(void);
        void				_cpy_content(list &src);

        //* La utilizziamo per il sort
        template <class Compare>
        void				ft_mergesort(Compare comp);
    };
}

#endif