//
// Created by dasch on 10.11.2017.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mem.h>

typedef char * data_t;

static const size_t DATA_LEN = 50;
static const size_t MAX_LEN = 100;
static int lefts = 2;
static int rights = 1000;

struct Leaf {
    data_t data;
    struct Leaf *left;
    struct Leaf *right;

    struct Leaf *parent;
};

struct Tree {
    size_t len;
    struct Leaf *root;
};

struct Leaf *Leaf_Construct(data_t value);
void Leaf_Destruct(struct Leaf **old_one);
struct Tree *Tree_Construct(data_t value);
void Tree_Destruct(struct Tree **old_one);
int Tree_Ok(struct Tree *tree);
void Tree_Dump(struct Tree *tree, size_t line);
void Leaf_Dump(struct Leaf *leaf, int leaf_num);
void Tree_AddLeft(struct Tree *tree, struct Leaf *leaf, data_t value);
void Tree_AddRight(struct Tree *tree, struct Leaf *leaf, data_t value);

#endif //TREE_TREE_H
