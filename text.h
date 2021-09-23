#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "Token.h"
#include "buffer.h"
#define T Token
#include "vector.h"

enum TEXT_ERRORS
{
    TEXT_SUCCESS = 0,
    TEXT_BAD_FILE = 256, TEXT_ALLOCATION_FAILED,
    TOKENIZING_FAILED, VECTOR_OF_TOKENS_CONSTRUCTING_FAILED
};

struct Text
{
    const char   *name;
    Buffer        buff;
    vector_Token  tokens;
    bool          null_terminated;
};

TEXT_ERRORS text_ctor_by_file (Text *_this, FILE *pfile);
TEXT_ERRORS text_tokenize (Text *_this, const char *delim, bool null_term);

#endif