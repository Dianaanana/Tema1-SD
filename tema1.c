// copyright 2022 Ciocoiu Diana-iulia 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"
#include "utils.h"

/* This program uses circular doubly linked list.*/

/* sorry for both using deck and pack, it confuses me as well */

typedef struct value_t
{
    int nr;
    char *symbol;
} value_t;

// function for parsing arguments (if there are extra parameters then
// it prints INVALID_COMMAND macro).
int gibberish()
{
    char whatever[MAX_STRING_SIZE];
    fgets(whatever, MAX_STRING_SIZE, stdin);
    int i = 0;
    for (i = 0; i < strlen(whatever); i++)
    {
        if (whatever[i] != ' ' && whatever[i] != '\n')
        {
            printf(INVALID_COMMAND);
            return 0;
        }
    }
    return 1;
}

// same but INVALID_CARD macro.
int gibberish_card()
{
    char whatever[MAX_STRING_SIZE];
    fgets(whatever, MAX_STRING_SIZE, stdin);
    int i = 0;
    for (i = 0; i < strlen(whatever); i++)
    {
        if (whatever[i] != ' ' && whatever[i] != '\n')
        {
            printf(INVALID_CARD);
            return 0;
        }
    }
    return 1;
}

// function to check if a card in valid.
int check_valid_card(int nr, char symbol[])
{
    if (nr < 0 || nr > 14)
    {
        return 1;
    }
    if (strcmp(symbol, "HEART") != 0 && strcmp(symbol, "DIAMOND") != 0 &&
        strcmp(symbol, "CLUB") != 0 && strcmp(symbol, "SPADE") != 0)
    {
        return 1;
    }
    return 0;
}

// function to make a copy of a card in order to manipulate it in other packs.
void card_copy(value_t *value, int nr, char *symbol)
{
    value->nr = nr;
    value->symbol = malloc(strlen(symbol) + 1);
    strcpy(value->symbol, symbol);
}

// add_deck = creates a new deck and populates it.
void add_deck(doubly_linked_list_t *packs)
{
    int n;
    scanf("%d", &n);

    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }

    doubly_linked_list_t *pack = dll_create(sizeof(value_t));
    DIE(!pack, "malloc failed");

    int nr;
    char symbol[MAX_SYMBOL];
    int check;
    int cnt = 0;

    value_t *value = malloc(sizeof(value_t));
    DIE(!value, "malloc failed");

    while (cnt < n)
    {
        scanf("%d%s", &nr, symbol);
        int dpsmts = gibberish_card();
        if (dpsmts == 0)
        {
            return;
        }

        check = check_valid_card(nr, symbol);
        if (check == 1)
        {
            printf(INVALID_CARD);
        }
        else
        {
            card_copy(value, nr, symbol);

            dll_add_nth_node(pack, pack->size, value);
            cnt++;
        }
    }
    free(value);

    dll_add_nth_node(packs, packs->size, pack);
    free(pack);
    printf("The deck was successfully created with %d cards.\n", n);
}

// del_deck = deletes a deck
void del_deck(doubly_linked_list_t *packs, int index)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *del_node = dll_remove_nth_node(packs, index);
    doubly_linked_list_t *del_pack = del_node->data;

    free(del_node);
    while (del_pack->size != 0)
    {
        dll_node_t *del_card_node = dll_remove_nth_node(del_pack, 0);
        value_t *del_card = del_card_node->data;
        free(del_card->symbol);
        free(del_card);
        free(del_card_node);
    }
    free(del_pack);

    printf("The deck %d was successfully deleted.\n", index);
}

// del_card = deletes a card
void del_card(doubly_linked_list_t *packs)
{
    int card_index;
    int pack_index;

    scanf("%d%d", &pack_index, &card_index);
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }

    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *pack = dll_get_nth_node(packs, pack_index);

    if (((doubly_linked_list_t *)pack->data)->size == 0 ||
        card_index > ((doubly_linked_list_t *)pack->data)->size - 1)
    {
        printf(CARD, pack_index);
        return;
    }

    dll_node_t *del_card_node = dll_remove_nth_node(pack->data, card_index);
    value_t *del_card = del_card_node->data;
    free(del_card->symbol);
    free(del_card);
    free(del_card_node);

    if (((doubly_linked_list_t *)pack->data)->size == 0)
    {
        dll_node_t *removed = dll_remove_nth_node(packs, pack_index);
        // free(((value_t *)removed->data)->symbol);
        doubly_linked_list_t *var = (doubly_linked_list_t *)removed->data;
        dll_free(&var);
        free(removed);
    }

    printf("The card was successfully deleted from deck %d.\n", pack_index);
}

// add_cards = adds nr_cards cards in a pack with index pack_index.
void add_cards(doubly_linked_list_t *packs)
{
    int nr_cards;
    int pack_index;

    scanf("%d%d", &pack_index, &nr_cards);
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    int nr;
    char symbol[MAX_SYMBOL];
    int check;
    int cnt = 0;

    value_t *value = malloc(sizeof(value_t));
    DIE(!value, "malloc failed");

    while (cnt < nr_cards)
    {
        scanf("%d %s", &nr, symbol);
        int dpsmts = gibberish_card();
        if (dpsmts == 0)
        {
            return;
        }

        check = check_valid_card(nr, symbol);
        if (check == 1)
        {
            printf(INVALID_CARD);
        }
        else
        {
            card_copy(value, nr, symbol);

            dll_add_nth_node(pack, pack->size, value);
            cnt++;
        }
    }

    free(value);

    printf("The cards were successfully added to deck %d.\n", pack_index);
}

// deck_number = shows the number of decks.
void deck_number(doubly_linked_list_t *packs)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    printf("The number of decks is %d.\n", packs->size);
}

// deck_len = shows the number of card of a deck with index pack_index.
void deck_len(doubly_linked_list_t *packs)
{
    int pack_index;
    scanf("%d", &pack_index);
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    printf("The length of deck %d is %d.\n", pack_index, pack->size);
}

// show_deck  = prints a deck with index pack_index.
void show_deck(doubly_linked_list_t *packs)
{
    int pack_index;
    scanf("%d", &pack_index);
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    printf("Deck %d:\n", pack_index);

    dll_node_t *curr = pack->head;
    int i = 0;
    for (i = 0; i < pack->size; i++)
    {
        printf("\t%d %s\n", ((value_t *)curr->data)->nr,
               ((value_t *)curr->data)->symbol);
        curr = curr->next;
    }
}

void print_pack(doubly_linked_list_t *packs, int pack_index)
{
    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    printf("Deck %d:\n", pack_index);

    dll_node_t *curr = pack->head;
    int i = 0;
    for (i = 0; i < pack->size; i++)
    {
        printf("\t%d %s\n", ((value_t *)curr->data)->nr,
               ((value_t *)curr->data)->symbol);
        curr = curr->next;
    }
}

// show_all = shows all decks.
void show_all(doubly_linked_list_t *packs)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    int i = 0;
    for (i = 0; i < packs->size; i++)
    {
        print_pack(packs, i);
    }
}

// function to split one deck by a certain index.
// if the index is 0 or the length, then it does nothing.
void split_deck(doubly_linked_list_t *packs, int pack_index, int index_split)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    if (pack->size == 0 || index_split > pack->size - 1)
    {
        printf(CARD, pack_index);
        return;
    }

    if (index_split == 0 || index_split == pack->size)
    {
        printf("The deck %d was successfully split by index %d.\n",
               pack_index, index_split);
        return;
    }

    doubly_linked_list_t *new_pack = dll_create(sizeof(value_t));
    DIE(!new_pack, "malloc failed");

    dll_node_t *curr = dll_get_nth_node(pack, index_split);

    value_t *aux = malloc(sizeof(value_t));
    DIE(!aux, "malloc failed");

    while (pack->size > index_split)
    {
        card_copy(aux, ((value_t *)curr->data)->nr,
                  ((value_t *)curr->data)->symbol);
        dll_add_nth_node(new_pack, new_pack->size, aux);
        dll_node_t *removed = dll_remove_nth_node(pack, index_split);
        value_t *removed_card = removed->data;
        free(removed_card->symbol);
        free(removed_card);
        curr = removed->next;
        free(removed);
    }

    dll_add_nth_node(packs, pack_index + 1, new_pack);
    free(new_pack);
    free(aux);

    printf("The deck %d was successfully split by index %d.\n",
           pack_index, index_split);
}

// merge_decks = merges 2 decks.
void merge_decks(doubly_linked_list_t *packs, int pack_index1, int pack_index2)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index1 > packs->size - 1 ||
        pack_index2 > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    doubly_linked_list_t *merged_pack = dll_create(sizeof(value_t));
    DIE(!merged_pack, "malloc failed");

    dll_node_t *node1 = dll_get_nth_node(packs, pack_index1);
    doubly_linked_list_t *pack1 = node1->data;

    dll_node_t *node2 = dll_get_nth_node(packs, pack_index2);
    doubly_linked_list_t *pack2 = node2->data;

    dll_node_t *aux1 = pack1->head;
    dll_node_t *aux2 = pack2->head;

    value_t *aux = malloc(sizeof(value_t));
    DIE(!aux, "malloc failed");

    int cnt = 0;

    int min_length;

    if (pack1->size > pack2->size)
        min_length = pack2->size;
    else
        min_length = pack1->size;
    int i = 0;
    for (i = 0; i < min_length; i++)
    {
        card_copy(aux, ((value_t *)aux1->data)->nr,
                  ((value_t *)aux1->data)->symbol);
        dll_add_nth_node(merged_pack, merged_pack->size, aux);
        aux1 = aux1->next;

        card_copy(aux, ((value_t *)aux2->data)->nr,
                  ((value_t *)aux2->data)->symbol);
        dll_add_nth_node(merged_pack, merged_pack->size, aux);
        aux2 = aux2->next;
    }

    while (aux2 != pack2->head)
    {
        card_copy(aux, ((value_t *)aux2->data)->nr,
                  ((value_t *)aux2->data)->symbol);
        dll_add_nth_node(merged_pack, merged_pack->size, aux);
        aux2 = aux2->next;
    }

    while (aux1 != pack1->head)

    {
        card_copy(aux, ((value_t *)aux1->data)->nr,
                  ((value_t *)aux1->data)->symbol);
        dll_add_nth_node(merged_pack, merged_pack->size, aux);
        aux1 = aux1->next;
    }

    free(aux);

    dll_add_nth_node(packs, packs->size, merged_pack);
    free(merged_pack);

    dll_node_t *removed_node;
    dll_node_t *del_pack2;
    dll_node_t *del_pack1;
    if (pack_index1 < pack_index2)
    {
        del_pack2 = dll_remove_nth_node(packs, pack_index2);
        del_pack1 = dll_remove_nth_node(packs, pack_index1);
    }
    else
    {
        del_pack1 = dll_remove_nth_node(packs, pack_index1);
        del_pack2 = dll_remove_nth_node(packs, pack_index2);
    }
    doubly_linked_list_t *del_pack1_v = del_pack1->data;
    doubly_linked_list_t *del_pack2_v = del_pack2->data;
    while (del_pack2_v->size)
    {
        removed_node = dll_remove_nth_node(del_pack2_v, 0);
        free(((value_t *)removed_node->data)->symbol);
        free(removed_node->data);
        free(removed_node);
    }
    free(del_pack2);
    free(del_pack2_v);

    while (del_pack1_v->size)
    {
        removed_node = dll_remove_nth_node(del_pack1_v, 0);
        free(((value_t *)removed_node->data)->symbol);
        free(removed_node->data);
        free(removed_node);
    }
    free(del_pack1_v);
    free(del_pack1);

    printf("The deck %d and the deck %d were successfully merged.\n",
           pack_index1, pack_index2);
}

// reverse_deck = reverse the position of the cards
// HEADS UP if the size of the deck is 1, then u have a special case
// (my implementation with circular doubly linked list fails for that case)
void reverse_deck(doubly_linked_list_t *packs, int pack_index)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;
    dll_node_t *curr = pack->head;

    if (pack->size == 1)
    {
        printf("The deck %d was successfully reversed.\n", pack_index);
        return;
    }

    value_t *aux = malloc(sizeof(value_t));
    DIE(!aux, "malloc failed");
    int i = 0;
    for (i = 0; i < pack->size; i++)
    {
        card_copy(aux, ((value_t *)curr->data)->nr,
                  ((value_t *)curr->data)->symbol);
        dll_node_t *removed = dll_remove_nth_node(pack, 0);
        dll_add_nth_node(pack, pack->size - i, aux);
        curr = curr->next;
        free(((value_t *)removed->data)->symbol);
        free(removed->data);
        free(removed);
    }

    free(aux);

    printf("The deck %d was successfully reversed.\n", pack_index);
}

// shuffle_deck = switch the first and the last half.
void shuffle_deck(doubly_linked_list_t *packs, int pack_index)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    if (packs->size == 0 || pack_index > packs->size - 1)
    {
        printf(DECK);
        return;
    }

    dll_node_t *node = dll_get_nth_node(packs, pack_index);
    doubly_linked_list_t *pack = node->data;

    pack->head = dll_get_nth_node(pack, pack->size / 2);

    printf("The deck %d was successfully shuffled.\n", pack_index);
}

// free_funct = the goddess.
void free_funct(doubly_linked_list_t *packs)
{
    int dpsmts = gibberish();
    if (dpsmts == 0)
    {
        return;
    }
    while (packs->size != 0)
    {
        dll_node_t *current = dll_remove_nth_node(packs, 0);
        doubly_linked_list_t *pack = current->data;
        free(current);
        while (pack->size != 0)
        {
            dll_node_t *card_node = dll_remove_nth_node(pack, 0);
            value_t *card = card_node->data;

            free(card->symbol);
            free(card);
            free(card_node);
        }
        free(pack);
    }
    free(packs);
}

int main()
{
    doubly_linked_list_t *big_hand = dll_create(sizeof(doubly_linked_list_t));
    char command[MAX_STRING_SIZE];
    char whatever[MAX_STRING_SIZE];

    while (1)
    {
        scanf("%s", command);
        if (strncmp(command, "ADD_DECK", 8) == 0)
        {
            add_deck(big_hand);
        }
        else if (strncmp(command, "DEL_DECK", 8) == 0)
        {
            int index;
            scanf("%d", &index);

            del_deck(big_hand, index);
        }
        else if (strncmp(command, "DEL_CARD", 8) == 0)
        {
            del_card(big_hand);
        }
        else if (strncmp(command, "ADD_CARDS", 9) == 0)
        {
            add_cards(big_hand);
        }
        else if (strncmp(command, "DECK_NUMBER", 11) == 0)
        {
            deck_number(big_hand);
        }
        else if (strncmp(command, "DECK_LEN", 8) == 0)
        {
            deck_len(big_hand);
        }
        else if (strncmp(command, "SHUFFLE_DECK", 12) == 0)
        {
            int pack_index;

            scanf("%d", &pack_index);

            shuffle_deck(big_hand, pack_index);
        }
        else if (strncmp(command, "MERGE_DECKS", 11) == 0)
        {
            int pack_index1, pack_index2;
            scanf("%d%d", &pack_index1, &pack_index2);

            merge_decks(big_hand, pack_index1, pack_index2);
        }
        else if (strncmp(command, "SPLIT_DECK", 10) == 0)
        {
            int pack_index, index_split;
            scanf("%d%d", &pack_index, &index_split);

            split_deck(big_hand, pack_index, index_split);
        }
        else if (strncmp(command, "REVERSE_DECK", 12) == 0)
        {
            int pack_index;
            scanf("%d", &pack_index);
            reverse_deck(big_hand, pack_index);
        }
        else if (strncmp(command, "SHOW_DECK", 9) == 0)
        {
            show_deck(big_hand);
        }
        else if (strncmp(command, "SHOW_ALL", 8) == 0)
        {
            show_all(big_hand);
        }
        else if (strncmp(command, "EXIT", 4) == 0)
        {
            free_funct(big_hand);
            break;
        }
        else if (strncmp(command, "SORT_DECK", 9) == 0)
        {
            int pack_index;

            scanf("%d", &pack_index);

            int dpsmts = gibberish();
            if (dpsmts == 0)
            {
                continue;
            }
        }
        else
        {
            printf(INVALID_COMMAND);
            fgets(whatever, MAX_STRING_SIZE, stdin);
        }
    }

    return 0;
}
