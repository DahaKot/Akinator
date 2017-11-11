//
// Created by dasch on 10.11.2017.
//
#include "tree.h"

struct Leaf *Leaf_Construct(data_t value) {
    struct Leaf *new_one = calloc(1, sizeof(struct Leaf));
    assert(new_one != NULL);

    new_one->data = calloc(DATA_LEN, sizeof(char));
    assert(new_one->data != NULL);
    strncpy(new_one->data, value, strlen(value));

    new_one->left = NULL;
    new_one->right = NULL;

    return new_one;
}

void Leaf_Destruct(struct Leaf **old_one) {
    if (*old_one != NULL) {
        free((*old_one)->left);
        free((*old_one)->right);
        (*old_one)->left = NULL;
        (*old_one)->right = NULL;
    }
    free(*old_one);
    *old_one = NULL;
}

struct Tree *Tree_Construct(data_t value) {
    struct Tree *new_one = calloc(1, sizeof(struct Tree));
    assert(new_one != NULL);

    new_one->len = 1;
    new_one->root = Leaf_Construct(value);

    return new_one;
}

void Tree_Destruct(struct Tree **old_one) {
    if (*old_one != NULL) {
        free((*old_one)->root);
        (*old_one)->root = NULL;
    }
    free(*old_one);
    *old_one = NULL;
}

int Tree_Ok(struct Tree *tree) {
    if (tree == NULL || tree->root == NULL || tree->len < 1) {
        return 0;
    }

    return 1;
}

void Tree_Dump(struct Tree *tree, size_t line) {
    FILE *Dump_f = fopen("Dump.txt", "w");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "digraph Tree {\nroot [label = \"Tree\\nTree len = %d\"];\n", tree->len);
    fclose(Dump_f);

    //printf("Tree dump on line %d\n", line);
    Leaf_Dump(tree->root, 1);

    Dump_f = fopen("Dump.txt", "a");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "}");
    fclose(Dump_f);

    system ("dot -Tpng Dump.txt -o Dump.png");
    system("Dump.png");
}

void Leaf_Dump(struct Leaf *leaf, int leaf_num) {
    if (leaf == NULL) {
        return ;
    }

    int left = lefts;
    Leaf_Dump(leaf->left, lefts++);

    FILE *Dump_f = fopen("Dump.txt", "a");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "node%d [shape=record, label=\"{<name> node%d\\n%p|"
            "<data> data:\\ %s|{<left> left\\n%p|<right> right\\n%p}}\"];\n",
            leaf_num, leaf_num, leaf, leaf->data, leaf->left, leaf->right);
    if (leaf->left != NULL) {
        fprintf(Dump_f, "edge [color = red];\n");
        fprintf(Dump_f, "\"node%d\":left -> \"node%d\":name;\n", leaf_num, left);
    }
    if (leaf->right != NULL) {
        fprintf(Dump_f, "edge [color = green];\n");
        fprintf(Dump_f, "\"node%d\":right -> \"node%d\":name;\n", leaf_num, rights);
    }

    //printf("%s", leaf->data);

    fclose(Dump_f);

    Leaf_Dump(leaf->right, rights++);
}

void Tree_AddLeft(struct Tree *tree, struct Leaf *leaf, data_t value) {
    assert(tree != NULL);
    if (!Tree_Ok(tree)) {
        Tree_Dump(tree, __LINE__);
        return ;
    }
    assert(leaf != NULL);
    assert(leaf->left == NULL);

    leaf->left = Leaf_Construct(value);
    tree->len++;

    if (!Tree_Ok(tree)) {
        Tree_Dump(tree, __LINE__);
        return ;
    }
}

void Tree_AddRight(struct Tree *tree, struct Leaf *leaf, data_t value) {
    assert(tree != NULL);
    if (!Tree_Ok(tree)) {
        Tree_Dump(tree, __LINE__);
        return ;
    }
    assert(leaf != NULL);
    assert(leaf->right == NULL);

    leaf->right = Leaf_Construct(value);
    tree->len++;

    if (!Tree_Ok(tree)) {
        Tree_Dump(tree, __LINE__);
        return ;
    }
}