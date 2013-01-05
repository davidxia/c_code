#ifndef SPELL_H
#define SPELL_H

/* Define the maximum size for words in dictionary */
#define SPELL_SIZE 31


int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word);
#endif

