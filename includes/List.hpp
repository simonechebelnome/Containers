#ifndef LIST_HPP
# define LIST_HPP

# include "Utils.hpp"
# include "List_interface.hpp"

namespace ft {
    //* Ricorda che nodetype è definito come ft::lstNode<value_type> dove value_type == T
    //* Quindi quando creo un nuovo nodo con new node_type sto già assegnando T a data chiamando il costruttore del nodo
    template <typename T, typename Alloc>
    list<T, Alloc>::list(const allocator_type &alloc) : \
        _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        return ;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::list(size_type size, const value_type &val, const allocator_type &alloc) : \
        _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        this->_create_data(size, val);
        return ;
    }

    template <typename T, typename Alloc> template <class Ite>
    list<T, Alloc>::list(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
            Ite last, const allocator_type &alloc) : _data(), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        this->_create_data_it(first, last);
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::list(list const &src) : _data(), _alloc(allocator_type()), _size(0) {
        this->_data = new node_type;
        *this = src;
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::~list(void) {
        this->_destroy_data();
        delete this->_data;
    }

    template<typename T, typename Alloc>
    list<T, Alloc>	&list<T, Alloc>::operator=(list const &rhs) {
        if (this == &rhs)
            return (*this);
        this->_create_data_it(rhs.begin(), rhs.end());
        return (*this);
    }

    //* ################### METODI ITERATORI ###################
    //? Ricorda che stai lavorando con un NODO SENTINELLA ed una LISTA CIRCOLARE!

    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::begin(void) {
        return iterator(this->_data->next);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin(void) const {
        return const_iterator(this->_data->next);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::end(void) {
        return iterator(this->_data);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::end(void) const {
        return const_iterator(this->_data);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin(void) {
        return reverse_iterator(this->end());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin(void) const {
        return const_reverse_iterator(this->end());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend(void) {
        return reverse_iterator(this->begin());
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend(void) const {
        return const_reverse_iterator(this->begin());
    }

    //* ################### METODI CAPACITY ###################

    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::size(void) const {
        return (this->_size);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::max_size(void) const {
        return (_max_size);
    }

    template<typename T, typename Alloc>
    bool	list<T, Alloc>::empty(void) const {
        return (this->_size == 0 ? true : false);
    }

    //* ################### METODI ACCESSO ELEMENTI ###################

    template<typename T, typename Alloc> typename list<T, Alloc>::
    reference		list<T, Alloc>::front(void) {
        return *this->begin();
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    const_reference	list<T, Alloc>::front(void) const {
        return *this->begin();
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    reference		list<T, Alloc>::back(void) {
        return this->_data->prev->data;
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    const_reference	list<T, Alloc>::back(void) const {
        return this->_data->prev->data;
    }

    //! #### DEBUG ####
    template<typename T, typename Alloc>
    void            list<T, Alloc>::display(void) {
        iterator start = this->begin();
        iterator end = this->end();

        while(start != end){
            std:: cout << *start << std::endl;
            start++;
        }
    }
    
    //* ################### MODIFICATORI ###################

    //? Assign effettua una sostituzione completa (quindi sovrascrive gli elementi già presenti)
    //? Per questo motivo è comodo utilizzare swap. Abbiamo anche i costruttori necessari per costruire le due liste.
    template<typename T, typename Alloc> template <class Ite>
    void	list<T, Alloc>::assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last) {
        list newList(first, last);
        this->swap(newList);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::assign(size_type n, const value_type &val) {
        list newList(n, val);
        this->swap(newList);
    }

    template<typename T, typename Alloc>
    void		list<T, Alloc>::push_front(const value_type &val) {
        node_type	*newNode = new node_type;

        ++this->_size;
        newNode->data = val;
        newNode->next = this->_data->next; //? Il suo prossimo elemento è l'ATTUALE PRIMO ELEMENTO
        newNode->prev = this->_data; //? Il suo elemento precedente è il dummy node
        this->_data->next->prev = newNode; //? Il precedente dell'attuale primo elemento è ora il nuovo nodo
        this->_data->next = newNode; //? Finalemnte diciamo che il primo elemento è il nuovo nodo
    }

    template<typename T, typename Alloc>
    void		list<T, Alloc>::pop_front(void) {
        //? Qui è tutta una questione di riassegnare i nodi e di eliminare il primo della lista (oldnode)
        node_type	*oldNode = this->_data->next;

        if (this->empty())
            return ;
        --this->_size;
        this->_data->next = oldNode->next;
        this->_data->next->prev = this->_data;
        delete oldNode;
    }

    //? Il processo è speculare per i prossimi due, semplicemente l'ultimo elemento è dato da prev a partire dal dummy node
    template<typename T, typename Alloc>
    void		list<T, Alloc>::push_back(const value_type &val) {
        node_type	*newNode = new node_type;

        ++this->_size;
        newNode->data = val;
        newNode->next = this->_data;
        newNode->prev = this->_data->prev;
        this->_data->prev->next = newNode;
        this->_data->prev = newNode;
    }

    template<typename T, typename Alloc>
    void		list<T, Alloc>::pop_back(void) {
        node_type	*oldNode = this->_data->prev;

        if (this->empty())
            return ;
        --this->_size;
        this->_data->prev = oldNode->prev;
        this->_data->prev->next = this->_data;
        delete oldNode;
    }

    template<typename T, typename Alloc> typename list<T, Alloc>::
    iterator	list<T, Alloc>::insert(iterator position, const value_type &val) {
        this->insert(position, 1, val);
        return (--position);
    }

    //? Ricorda che Insert inserisce il valore PRIMA DELLA POSIZIONE
    template<typename T, typename Alloc>
    void	list<T, Alloc>::insert(iterator position, size_type n, const value_type &val) {
        node_type *after = position._node; //? Assegniamo un nodo alla posizione passata come parametro
        node_type *after_end = this->_data->prev; //? Questo in teoria è un nodo all'ultimo elemento della lista

        --position; //? Dobbiamo inserire prima di position
        position._node->next = this->_data; //? Facciamo esattamente questo
        this->_data->prev = position._node;
        while (n-- != 0)
            this->push_back(val); //? Continuiamo ad aggiungere val alla fine n volte
        if (after == this->_data)
            return ;
        after->prev = this->_data->prev;
        this->_data->prev->next = after;
        this->_data->prev = after_end;
    }

    template<typename T, typename Alloc> template <class Ite>
    void	list<T, Alloc>::insert(iterator position, Ite first, typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last) {
        node_type *after = position._node;
        node_type *after_end = this->_data->prev;

        --position;
        position._node->next = this->_data;
        this->_data->prev = position._node;
        while (first != last)
            this->push_back(*first++);
        if (after == this->_data)
            return ;
        after->prev = this->_data->prev;
        this->_data->prev->next = after;
        this->_data->prev = after_end;
    }

    //? Questo erase elimina un solo elemento
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator	list<T, Alloc>::erase(iterator ite) {
        return (this->erase(ite++, ite));
    }

    //? Elimina un range di elementi definito da due iteratori
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator	list<T, Alloc>::erase(iterator first, iterator last) {
        node_type *last_del = last._node;
        node_type *before_del = first._node->prev;

        //? Con queste due assegnazioni stiamo di fatto escludendo tutti i nodi che intercorrono nel mezzo
        before_del->next = last_del;
        last_del->prev = before_del;

        //? Rimane sono da diminuire la size ed eliminare quei nodi dalla memoria utilizzando delete
        while (first != last)
        {
            --this->_size;
            delete (first++)._node;
        }
        return last;
    }

    //? Ci appoggiamo ad una lista temporanea ed effettuiamo lo swap
    template<typename T, typename Alloc>
    void	list<T, Alloc>::swap(list &x) {
        list<T, Alloc> tmp;

        tmp._cpy_content(x);
        x._cpy_content(*this);
        this->_cpy_content(tmp);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::clear(void) {
        iterator it = this->begin(), ite = this->end(), tmp;

        while (it != ite)
        {
            tmp = it++;
            delete tmp._node;
        }
        this->_size = 0;
        this->_data->next = this->_data; this->_data->prev = this->_data; //! Resettiamo anche il dummy node
    }

    //? Resize è reso veramente stupido utilizzando pop_back e push_back
    template<typename T, typename Alloc>
    void	list<T, Alloc>::resize(size_type size, const value_type &val) {
        while (size < this->_size)
            this->pop_back();
        while (size > this->_size)
            this->push_back(val);
    }

    //* ################### OPERAZIONI ###################

    template<typename T, typename Alloc>
    void	list<T, Alloc>::splice(iterator position, list &x) {
        if (this == &x)
            return ; 
        this->splice(position, x, x.begin(), x.end());
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::splice(iterator position, list &x, iterator i) {
        this->splice(position, x, i++, i);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::splice(iterator position, list &x, iterator first, iterator last) {
        node_type	*before = position._node->prev;
        node_type	*_position = position._node;
        node_type	*_first = first._node, *_last = last._node->prev;
        size_type	len;

        //? Aggiorna entrambe le lunghezze
        for (len = 0; first != last; ++len)
            ++first;
        this->_size += len;
        x._size -= len;
        //? Unlinka da x il range di iteratori
        _first->prev->next = _last->next;
        _last->next->prev = _first->prev;
        //? Rimette il range in posizione
        before->next = _first;
        _first->prev = before;
        _position->prev = _last;
        _last->next = _position;
    }

    //? Reminder che il predicate è una funzione che restiuisce un bool
    template<typename T, typename Alloc> template <class Predicate>
    void	list<T, Alloc>::remove_if(Predicate pred) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (pred(*it))
                this->erase(it--); //! Qui stai passando it PRIMA CHE VENGA DECREMENTATO, bisogna decrementare perchè stiamo ELIMINANDO un nodo
            ++it;
        }
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::remove(const value_type &val) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (*it == val)
                this->erase(it--);
            ++it;
        }
    }

    template<typename T, typename Alloc> template <class BinaryPredicate>
    void	list<T, Alloc>::unique(BinaryPredicate binary_pred) {
        iterator it = this->begin(), ite = this->end();
        iterator tmp;

        //? tmp qui sta sempre ad indicare l'elemento successivo
        tmp = it++;
        while (it != ite)
        {
            if (binary_pred(*it, *tmp))
                this->erase(it--);
            tmp = it++;
        }
    }

    //! Il binary predicate è proprio definito in questo modo (prendere due oggetti come parametro)
    template <typename T>
    static bool	ft_eq(const T &a, const T &b) {
        return (a == b);
    }

    //? Qui stiamo passando ad unique solo il template della funzione, gli argomenti effettivi verranno passati all'interno di unique
    template<typename T, typename Alloc>
    void	list<T, Alloc>::unique(void) {
        this->unique(ft_eq<value_type>);
    }

    template<typename T, typename Alloc> template <class Compare>
    void	list<T, Alloc>::merge(list &x, Compare comp) {
        if (this == &x)
            return ;
        iterator this_it = this->begin(), x_it = x.begin();

        //? Aggiunge a this solo qualora la condizione espressa da comp sia vera
        while (x_it != x.end() && this_it != this->end())
        {
            if (comp(*x_it, *this_it))
                this->splice(this_it, x, x_it++);
            else
                ++this_it;
        }
        //? Alla fine adda comunque tutto ciò che rimane e che non è ancora stato sortato
        if (!x.empty())
            this->splice(this->end(), x);
    }

    //? Creiamo la funzione che effettuerà il sort in ordine ascendente una volta passata a merge
    template <typename T>
    static bool	ft_less(const T &a, const T &b) {
        return (a < b);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::merge(list &x) {
        if (this == &x)
            return ;
        //? Chiama merge sfruttando la funzione appena creata
        this->merge(x, ft_less<value_type>);
    }

    //! Questo mergesort ricorsivo sfugge alla mia comprensione
    template<typename T, typename Alloc> template <class Compare>
    void	list<T, Alloc>::ft_mergesort(Compare comp) {
        if (this->_size <= 1)
            return ;
        size_type mid = this->_size / 2;
        iterator it = this->begin();
        list tmp;

        while (mid-- != 0)
            ++it;
        tmp.splice(tmp.begin(), *this, it, this->end());

        this->ft_mergesort(comp);
        tmp.ft_mergesort(comp);

        this->merge(tmp, comp);
    }

    template<typename T, typename Alloc> template <class Compare>
    void	list<T, Alloc>::sort(Compare comp) {
        this->ft_mergesort(comp);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::sort(void) {
        this->sort(ft_less<value_type>);
    }

    //? Questo è facile, semplicemente swappa i nodi
    template<typename T, typename Alloc>
    void	list<T, Alloc>::reverse(void) {
        iterator	it = iterator(this->_data);
        size_type	size = this->_size + 1;
        node_type	*tmp;

        //? Next diventa prev e prev diventa next finchè non ci siamo girati tutta la lista
        while (size != 0)
        {
            tmp = it._node->next;
            it._node->next = it._node->prev;
            it._node->prev = tmp;
            ++it; --size;
        }
    }

    //* ################### METODI PRIVATI ###################

    template<typename T, typename Alloc> template <class Ite>
    void	list<T, Alloc>::_create_data_it(Ite first, Ite last) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite && first != last)
            *it++ = *first++;
        --it;
        while (it != --this->end())
            this->pop_back();
        while (first != last)
            this->push_back(*first++);
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::_create_data(size_type size, const value_type &val) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite && size != 0)
        {
            *it++ = val;
            --size;
        }
        --it;
        while (it != --this->end())
            this->pop_back();
        while (size != 0)
        {
            this->push_back(val);
            --size;
        }
    }

    template<typename T, typename Alloc>
    void	list<T, Alloc>::_destroy_data(void) {
        if (this->empty())
            return ;
        this->clear();
    }

    //? Creiamo una copia del nodo attuale e lo mettiamo in src, è una sorta di swap
    template<typename T, typename Alloc>
    void	list<T, Alloc>::_cpy_content(list<T, Alloc> &src) {
        this->clear();
        node_ptr tmp = this->_data;

        this->_data = src._data;
        this->_alloc = src._alloc;
        this->_size = src._size;
        src._data = tmp; src._size = 0;
        tmp = NULL; //! Mettiamo a Null dopo averlo utilizzato
    }

    //? Questa è la definizione della variabile statica _max_size
    template <typename T, typename Alloc>
    const typename list<T, Alloc>::size_type list<T, Alloc>::_max_size =
        std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1);
    
    //* ################### NON-MEMBER OVERLOADS ###################
    //? Sono gli stessi di Vector ma con le liste

    template <class T, class Alloc>
    bool	operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>
    bool	operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool	operator< (const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool	operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool	operator> (const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool	operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void	swap(list<T, Alloc> &x, list<T, Alloc> &y) { x.swap(y); }

}

#endif