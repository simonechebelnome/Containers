#ifndef LIST_INTERFACE_HPP
# define LIST_INTERFACE_HPP

# include "List_iterator.hpp"

//! DIFFERENZA FRA STD::VECTOR E STD::LIST
//? La differenza principale è che Vector lavora in uno spazio di memoria CONTIGUO, mentre List NO
//? Ciò significa che, ad esempio, sulle liste NON POSSO USARE IL RANDOM ACCESS. Se voglio un elemento specifico
//? Devo prima girarmi tutta la lista. Tuttavia, INSERIRE/ELIMINARE elementi sulle liste è PIU' FACILE, basta SCAMBIARE I PUNTATORI
//? Infine le liste hanno dei METODI SPECIALI che Vector non possiede. Questi metodi funzionano bene con std::algorithm

#endif