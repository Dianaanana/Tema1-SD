// copyright 2022 Ciocoiu Diana-iulia 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t *
dll_create(unsigned int data_size)
{
    /* TODO */
    doubly_linked_list_t *list = (doubly_linked_list_t *)
                                 malloc(sizeof(doubly_linked_list_t));
    DIE(!list, "failed malloc.\n");

    // initialise all
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista 
 * se afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere?
 */
dll_node_t *
dll_get_nth_node(doubly_linked_list_t *list, unsigned int n)
{
    /* TODO */
    if (!list)
    {
        printf("u have no list.\n");
        return NULL;
    }

    if (n >= list->size)
    {
        n = n % list->size;
    }

    dll_node_t *current;
    current = list->head;
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        current = current->next;
    }

    return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care 
 e adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei.
 */
void dll_add_first_node(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
    DIE(!new_node, "failed malloc.\n");

    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);

    if (list->size == 0)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->head = new_node;

        list->size++;

        return;
    }

    dll_node_t *current;
    current = list->head;

    new_node->next = current;
    new_node->prev = current->prev;

    current->prev->next = new_node;
    current->prev = new_node;

    list->head = new_node;

    list->size++;

    return;
}

void dll_add_last_node(doubly_linked_list_t *list, const void *data)
{
    dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
    DIE(!new_node, "failed malloc.\n");

    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);

    dll_node_t *current = list->head;
    dll_node_t *last = current->prev;

    last->next = new_node;
    new_node->prev = last;
    new_node->next = current;
    current->prev = new_node;

    list->size++;

    return;
}

void dll_add_nth_node(doubly_linked_list_t *list, unsigned int n,
                      const void *data)
{
    /* TODO */
    if (!list)
    {
        printf("u dont have a list.\n");
        return;
    }

    if (n == 0 || list->size == 0)
    {
        dll_add_first_node(list, data);
        return;
    }

    if (n < list->size)
    {
        dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
        DIE(!new_node, "failed malloc.\n");

        new_node->data = malloc(list->data_size);
        memcpy(new_node->data, data, list->data_size);

        dll_node_t *current = dll_get_nth_node(list, n - 1);

        new_node->prev = current;
        new_node->next = current->next;

        dll_node_t *aux = current->next;

        current->next = new_node;
        aux->prev = new_node;

        list->size++;

        return;
    }

    if (n >= list->size)
    {
        dll_add_last_node(list, data);
        return;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Este responsabilitatea apelantului sa elibereze memoria
 * acestui nod.
 */

dll_node_t *dll_remove_first_node(doubly_linked_list_t *list)
{
    dll_node_t *curr = list->head;
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->head = curr->next;

    list->size--;

    return curr;
}

dll_node_t *dll_remove_last_node(doubly_linked_list_t *list)
{
    dll_node_t *curr = list->head->prev;
    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->size--;

    return curr;
}

dll_node_t *
dll_remove_nth_node(doubly_linked_list_t *list, unsigned int n)
{
    /* TODO */
    if (!list)
    {
        printf("u dont have this list.\n");
        return NULL;
    }

    if (list->size == 1)
    {
        dll_node_t *current = list->head;
        list->head = NULL;
        list->size--;

        return current;
    }

    if (n == 0 && list->size != 1)
    {
        dll_node_t *curr = dll_remove_first_node(list);
        return curr;
    }

    if (n >= list->size)
    {
        dll_node_t *curr = dll_remove_last_node(list);
        return curr;
    }

    dll_node_t *curr = list->head;

    if (n < list->size - n)
    {
        unsigned int count = n;

        while (count)
        {
            curr = curr->next;
            count--;
        }
    }
    else
    {
        unsigned int count = list->size - n;

        while (count)
        {
            curr = curr->prev;
            count--;
        }
    }

    dll_node_t *prev = curr->prev;

    prev->next = curr->next;
    curr->next->prev = prev;

    list->size--;

    return curr;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t *list)
{
    /* TODO */
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void dll_free(doubly_linked_list_t **pp_list)
{
    /* TODO */
    if (!(*pp_list))
    {
        printf("nononono\n");
        return;
    }

    dll_node_t *current;
    current = (*pp_list)->head;

    dll_node_t *aux;
    unsigned int i;
    for (i = 0; i < (*pp_list)->size; i++)
    {
        aux = current->next;
        free(current->data);
        free(current);
        current = aux;
    }

    free(*pp_list);
    *pp_list = NULL;
}

// /*
//  * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri
//  STIM
//  * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
//  * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
//  * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
//  * circulara, pana cand sunt afisate valorile tuturor nodurilor.
//  */
void dll_print_ints_right_circular(dll_node_t *start)
{
    /* TODO */
    if (start == NULL)
    {
        return;
    }

    dll_node_t *aux = start;

    printf("%d ", *(int *)aux->data);
    while (aux->next != start)
    {
        aux = aux->next;
        printf("%d ", *(int *)aux->data);
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri 
 STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in 
 nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void dll_print_int_list(doubly_linked_list_t *list)
{
    /* TODO */
    if (list == NULL || list->size == 0)
    {
        return;
    }

    dll_node_t *current;
    current = list->head;

    printf("%d ", *(int *)current->data);
    while (current != NULL && current->next != list->head)
    {
        current = current->next;
        printf("%d ", *(int *)current->data);
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri 
 STIM ca stocheaza string-uri. Functia afiseaza o singura data toate valorile
  string stocate in nodurile din lista, separate printr-un spatiu, incepand de 
  la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void dll_print_strings_left_circular(dll_node_t *start)
{
    /* TODO */
    if (start == NULL)
    {
        return;
    }

    dll_node_t *aux = start;

    printf("%s ", (char *)aux->data);
    while (aux->prev != start)
    {
        aux = aux->prev;
        printf("%s ", (char *)aux->data);
    }

    printf("\n");
}

/*
 *Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void dll_print_string_list(doubly_linked_list_t *list)
{
    /* TODO */
    if (list == NULL)
    {
        return;
    }

    dll_node_t *current = list->head->prev;

    printf("%s ", (char *)current->data);
    while (current != NULL && current != list->head)
    {
        current = current->prev;
        printf("%s ", (char *)current->data);
    }

    printf("\n");
}

