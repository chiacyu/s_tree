#include "s_tree.c"
#include <stddef.h> /* offsetof */

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (offsetof(type, member))))

#define treeint_entry(ptr) container_of(ptr, struct treeint, st_n)

struct treeint {
    int value;
    struct st_node st_n;
};

static struct st_root *tree;

int treeint_init(struct st_root **tree);
static void __treeint_destroy(struct st_node *n);
int treeint_destroy(struct st_root *tree);
struct treeint *treeint_insert(struct st_root *tree, int a);
struct treeint *treeint_find(int a);
int treeint_remove(struct st_root *tree, int a);
static void __treeint_dump(struct st_node *n, int depth);
void treeint_dump(struct st_root *tree);