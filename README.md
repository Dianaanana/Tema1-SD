**Ciocoiu Diana Iulia:**
**313CA:**

## Now You See Me + tema 1

### Description:

* Short description of the functionality of the homework

This program manipulates multiple lists in the same time using a list which nodes store pointers to other lists.

There is a list (big_hand) which stores on every node a pointer to another list (deck). Each deck stores on every node a pointer to a structure (value_t) representing a pair number-symbol. 

functions:

    ADD_DECK (index, nr_of_cards) = adds a new deck on the position index.
        -create a new deck 
        -check if the input is ok
        -add every card in the deck
        -add the deck in the big_hand
    
    DEL_DECK (index) = deletes the deck in the position index.
        -access the node from big_hand where the deck is stored
        -free the symbol for each card (they are dinamically aloccated)
        -free each struct value(number, symbol)
        -free each node
        -delete the node from the big_hand

    DEL_CARD (pack_index, card_index) = deletes a certain card (from the deck 
              with pack_index the card with card_index)
        -is similar with del_deck but if frees the certain card

    ADD_CARDS ( pack_index, nr_cards) = adds nr_cards cards to the pack with index
               pack_index
        -access the pack with pack_index
        -allocate nr_cards new cards (aka nodes)
        -check if the input is ok
        -copy the nr and symbol into the value_t struct wich is stored in every node

    DECK_LEN (index) = shows the length of a deck in the position index

    DECK_NUMBER () = shows the number of decks in big_hand

    SHUFFLE_DECK (index) = switch the first and the last half of the deck on the  
                 position index 
        -because a work with circular doubly linked lists, I only switched the list.head position

    MERGE_DECKS (index1, index2) = combines 2 decks 
		-alternate elements from bath until one is empty, then add the rest of them
		-delete the 2 packs (resulting only the merged ones)

    SPLIT_DECK (index, index_split) = split the pack from position index in  2 new 
				packs by index_split
		-create a new pack with the last size - index_split elements
		-add it after the original pack 
		-delete the las size - index_split elements from the original pack

    REVERSE_DECK (index) = reverse the position of cards.
		-access the node from big_hand where the deck is stored
		-iterate through the deck.
		-delete the first node then add it on the size - i position.
		-special case when the deck length is 1!!!!! because after deleting the node you end up with list.head = NULL and can't use my approach

    SHOW_DECK (index) = prints a certain deck

    SHOW_ALL () = prints all decks

    EXIT = free all and exit program

    BONUS()

### Comments:

* I think using a doubly linked list would have been more helpful and easier.
* I've learned pointer arithmetics, i understood better linked lists, i starded understanding working with valgrind and debugging.

           __..--''``---....___   _..._    __
 /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
///_.-' _..--.'_    \                    `( ) ) // //
/ (_..-' // (< _     ;_..__               ; `' / ///
 / // // //  `-._,_)' // / ``--...____..-' /// / //
 //my cat every time I tried codding my homework//