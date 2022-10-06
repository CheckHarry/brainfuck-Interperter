#include <stdio.h>
#include <string.h>

typedef struct st
{
    int stack[1024];
    int cur_pos;
} st_t;

typedef struct bf_interperter
{
    st_t s;
    int pos;
    int pos_i;
    int pad;
    char mem[1024];

} bf_interperter_t;

void st_init(st_t *s)
{
    memset(s->stack, 0, sizeof(s->stack));
    s->stack[0] = -1;
    s->cur_pos = 1;
}

void st_push(st_t *s, int c)
{
    s->stack[s->cur_pos] = c;
    s->cur_pos++;
}

int st_top(st_t *s)
{
    return s->stack[s->cur_pos - 1];
}

void st_pop(st_t *s)
{
    s->cur_pos--;
}

void bf_init(bf_interperter_t *bf_i)
{
    st_init(&(bf_i->s));
    bf_i->pos = 0;
    bf_i->pos_i = 0;
    bf_i->pad = 0;
    memset(bf_i->mem, 0, sizeof(bf_i->mem));
}

void bf_step(bf_interperter_t *bf_i, char op)
{

    if (bf_i->pad == 0)
    {
        switch (op)
        {
        case '>':
            (bf_i->pos)++;
            break;
        case '<':
            (bf_i->pos)--;
            break;
        case '+':
            bf_i->mem[(bf_i->pos)]++;
            break;
        case '-':
            bf_i->mem[(bf_i->pos)]--;
            break;
        case '.':
            putchar(bf_i->mem[(bf_i->pos)]);
            //printf("%d\n" , bf_i -> mem[(bf_i -> pos)]);
            break;
        case ',':
            bf_i->mem[(bf_i->pos)] = getchar();
            break;
        case '[':
            if (bf_i->mem[(bf_i->pos)] == 0)
            {
                bf_i->pad++; // enter pad mode
            }
            else
            {
                st_push(&(bf_i->s), bf_i->pos_i);
            }

            break;
        case ']':

            if (bf_i->mem[(bf_i->pos)] != 0)
            {
                bf_i->pos_i = st_top(&(bf_i->s)); 
            }
            else
            {
                st_pop(&(bf_i->s));
            }

            break;
        default:
            break;
        }
    }
    else
    {
        /* code */
        switch (op)
        {
        case '[':
            bf_i->pad++;
            break;
        
        case ']':
            bf_i->pad--;
            break;

        default:
            break;
        }
    }
    

    bf_i->pos_i++;
}

void bf_run(bf_interperter_t *bf_i, char *bf_prg, unsigned int size)
{
    while (bf_i->pos_i < size)
    {
        bf_step(bf_i, bf_prg[bf_i->pos_i]);
    }
}
