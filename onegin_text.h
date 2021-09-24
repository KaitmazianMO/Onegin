#ifndef ONEGIN_TEXT_H_INCLUDED
#define ONEGIN_TEXT_H_INCLUDED

#include <stdio.h>

#include "text.h"

enum ONEGIN_TEXT_ERROR
{
    ONEGIN_TEXT_SUCCESS = 0,
    ONEGIN_TEXT_CONSTRUCTING_FAILED = 256, ONEGIN_TEXT_DESTRUCTING_FAILED,
    ONEGIN_TEXT_TOKENIZING_FAILED,
};

typedef int (*token_comporator_t) (const void *l, const void *r);

struct OneginText
{
    Text text;
};

ONEGIN_TEXT_ERROR onegin_text_ctor            (OneginText *_this, FILE *finput);
ONEGIN_TEXT_ERROR onegin_text_sort            (OneginText *_this, token_comporator_t cmp);
ONEGIN_TEXT_ERROR onegin_text_rhyme_formating (OneginText *_this, token_comporator_t cmp);
ONEGIN_TEXT_ERROR onegin_text_dump            (OneginText *_this, FILE *fout, const char *title);
ONEGIN_TEXT_ERROR onegin_text_dtor            (OneginText *_this);

#endif