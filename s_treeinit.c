#include "s_treeinit.h"

int treeint_init(struct st_root *tree)
{
    tree = calloc(sizeof(struct st_root), 1);
    assert(tree);
    return 0;
}

static void __treeint_destroy(struct st_node *n)
{
    if (st_left(n))
        __treeint_destroy(st_left(n));

    if (st_right(n))
        __treeint_destroy(st_right(n));

    struct treeint *i = treeint_entry(n);
    free(i);
}

int treeint_destroy()
{
    assert(tree);
    if (st_root(tree))
        __treeint_destroy(st_root(tree));

    free(tree);
    return 0;
}

struct treeint *treeint_insert(int a)
{
    struct st_node *p = NULL;
    enum st_dir d;
    for (struct st_node *n = st_root(tree); n;) {
        struct treeint *t = container_of(n, struct treeint, st_n);
        if (a == t->value)
            return t;

        p = n;

        if (a < t->value) {
            n = st_left(n);
            d = LEFT;
        } else if (a > t->value) {
            n = st_right(n);
            d = RIGHT;
        }
    }

    struct treeint *i = calloc(sizeof(struct treeint), 1);
    if (st_root(tree))
        st_insert(&st_root(tree), p, &i->st_n, d);
    else
        st_root(tree) = &i->st_n;

    i->value = a;
    return i;
}

struct treeint *treeint_find(int a)
{
    struct st_node *n = st_root(tree);
    while (n) {
        struct treeint *t = treeint_entry(n);
        if (a == t->value)
            return t;

        if (a < t->value)
            n = st_left(n);
        else if (a > t->value)
            n = st_right(n);
    }

    return 0;
}

int treeint_remove(int a)
{
    struct treeint *n = treeint_find(a);
    if (!n)
        return -1;

    st_remove(&st_root(tree), &n->st_n);
    free(n);
    return 0;
}

/* ascending order */
static void __treeint_dump(struct st_node *n, int depth)
{
    if (!n)
        return;

    __treeint_dump(st_left(n), depth + 1);

    struct treeint *v = treeint_entry(n);
    printf("%d\n", v->value);

    __treeint_dump(st_right(n), depth + 1);
}

void treeint_dump()
{
    __treeint_dump(st_root(tree), 0);
}