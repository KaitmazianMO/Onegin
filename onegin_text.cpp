#include "onegin_text.h"

#include <string.h>

static int default_line_comparator (const void *l, const void *r);
static void write_nlines_to_file (vector_Token *tokens, size_t nLines, FILE *file);
static void print_title (FILE* file, const char *str);

ONEGIN_TEXT_ERROR onegin_text_ctor (OneginText *_this, FILE *finput)
{
    assert (_this);
    assert (finput);

    if (text_ctor_by_file (&_this->text, finput))
        return ONEGIN_TEXT_CONSTRUCTING_FAILED;

    if (text_tokenize (&_this->text, "\n", NULL_TERMINATED))
    {
        return ONEGIN_TEXT_TOKENIZING_FAILED;
    }

    return ONEGIN_TEXT_SUCCESS;
}

ONEGIN_TEXT_ERROR onegin_text_sort (OneginText *_this, token_comporator_t cmp)
{
    assert (_this);
    assert (cmp);

    qsort (_this->text.tokens.data.data, 
    _this->text.tokens.size, sizeof (Token), 
    cmp ? cmp : default_line_comparator);

    return ONEGIN_TEXT_SUCCESS;
}

ONEGIN_TEXT_ERROR onegin_text_dump (OneginText *_this, FILE *fout, const char *title)
{
    assert (_this);
    assert (fout);
    assert (title);

    print_title (fout, title);
    write_nlines_to_file (&_this->text.tokens, _this->text.tokens.size, fout);

    return ONEGIN_TEXT_SUCCESS;
}

ONEGIN_TEXT_ERROR onegin_text_dtor (OneginText *_this)
{
    if (text_dtor (&_this->text))
        return ONEGIN_TEXT_DESTRUCTING_FAILED;

    return ONEGIN_TEXT_SUCCESS;
}

int default_line_comparator (const void *l, const void *r)
{
    assert (l);
    assert (r);

    const Token *line1 = ((const Token *)l);
    const Token *line2 = ((const Token *)r);

    assert (line1->beg != NULL);
    assert (line2->beg != NULL);

    return strcmp (line1->beg, line2->beg);
}

static void write_nlines_to_file (vector_Token *tokens, size_t n_lines, FILE *file)
{
   assert (file != NULL);
   assert (tokens  != NULL);

   const size_t writable = MIN (n_lines, tokens->size); 
   for (size_t i = 0; i < writable; ++i)
   {
       Token tok = {};
       vec_get_elem_Token (tokens, i, &tok);
       fprintf (file, "%.*s\n", (int)tok.size, tok.beg);
   }
}

static void print_title (FILE* file, const char *str)
{
    #define PrintLine(sym) for (size_t i = 0; i < 100; ++i)     \
                               {                                \
                               fprintf (file, "%c", (sym));     \
                                   if (i == 99)                 \
                                       fprintf (file, "\n");    \
                               }

    fprintf (file, "\n\n\n");
    PrintLine('-')
    PrintLine('|')
    PrintLine('|')
    PrintLine('-')

    fprintf (file, "\n\n\n\n\n\n%60s\n\n\n\n\n\n", str);

    PrintLine('-')
    PrintLine('|')
    PrintLine('|')
    PrintLine('-')
    fprintf (file, "\n\n\n");

    #undef PrintLine
}