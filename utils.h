// copyright Ciocoiu Diana-Iulia 313CA

#ifndef UTILS_H_
#define UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define DECK "The provided index is out of bounds for the deck list.\n"
#define CARD "The provided index is out of bounds for deck %d.\n"
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"
#define MAX_STRING_SIZE 256
#define HMAX 10
#define MAX_SYMBOL 20

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                       \
    do                                                         \
    {                                                          \
        if (assertion) {                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__); \
            perror(call_description);                          \
            exit(errno);                                       \
        }                                                      \
    } while (0)

#endif  // UTILS_H_"
