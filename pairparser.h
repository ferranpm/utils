#ifndef PAIRPARSER_H
#define PAIRPARSER_H

#include "map.h"

struct pairparser;

/**
 * \brief Given the two separators and the text, creates a new instance of pairparser
 *
 * \param txt the text to parse
 * \param pair the separator between key/value
 * \param group the separator between pairs
 * \return A pointer to a pairparser structure
 */
struct pairparser* pairparser_new(char *, const char, const char);

/**
 * \brief Gets the value of the given key
 *
 * \param pp the pairparser structure from which to get the value
 * \param key the key to get the value from
 * \return the string of the value
 */
char* pairparser_get(struct pairparser *, char *);

#endif // PAIRPARSER_H
