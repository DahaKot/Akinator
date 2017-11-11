#include "tree.h"

void Akinator();
void Akinator_Dump(struct Tree *ak);
void Akinator_Leaf_Dump(struct Leaf *leaf, int leaf_num);
int Am_I_Right();

int main() {
    Akinator();

    return 0;
}

void Akinator() {
    //starting tree
    struct Tree *akinator_t = Tree_Construct("Does your charachter have fur?\n");
    Tree_AddRight(akinator_t, akinator_t->root, "Cat");
    Tree_AddLeft(akinator_t, akinator_t->root, "Is your charachter human?\n");
    Tree_AddLeft(akinator_t, akinator_t->root->left, "Frog\n");
    Tree_AddRight(akinator_t, akinator_t->root->left, "Elena Konstantinovna\n");

    struct Leaf *c_leaf = akinator_t->root;

    printf("Yes - y, No - n, Quit = q\n");
    printf("%s", c_leaf->data);

    char *ans = calloc(DATA_LEN, sizeof(char));
    fgets(ans, DATA_LEN, stdin);
    ans[strlen(ans) - 1] = '\0';

    while (ans != "q") {
        if (strcmp(ans, "y") == 0) {
            c_leaf = c_leaf->right;
            printf("%s", c_leaf->data);
            if (c_leaf->left == NULL && c_leaf->right == NULL) {
                if (Am_I_Right() == 1) {
                    break;
                }
                else {
                    char *name = calloc(DATA_LEN, sizeof(char));
                    fgets(name, DATA_LEN, stdin);
                    name[strlen(name) - 1] = '\0';

                    printf("What is the difference between my and your charachter?\n");
                    char *diff = calloc(DATA_LEN, sizeof(char));
                    fgets(diff, DATA_LEN, stdin);
                    diff[strlen(diff) - 1] = '\0';

                    strcat(diff, "?");
                    char *string = calloc(DATA_LEN, sizeof(char));
                    strncpy(string, "Is your charachter \0", strlen("Is your charachter \0"));
                    //printf("New string is: %s", string);
                    strcat(string, diff);

                    Tree_AddLeft(akinator_t, c_leaf, c_leaf->data);
                    Tree_AddRight(akinator_t, c_leaf, name);

                    c_leaf->data = string;
                    printf("\nChiao!\n");
                    break;
                }
            }
        }
        else if (strcmp(ans, "n") == 0) {
            c_leaf = c_leaf->left;
            printf("%s", c_leaf->data);
            if (c_leaf->left == NULL && c_leaf->right == NULL) {
                if (Am_I_Right() == 1) {
                    break;
                }
                else {
                    char *name = calloc(DATA_LEN, sizeof(char));
                    fgets(name, DATA_LEN, stdin);
                    name[strlen(name) - 1] = '\0';

                    printf("What is the difference between my and your charachter?\n");
                    char *diff = calloc(DATA_LEN, sizeof(char));
                    fgets(diff, DATA_LEN, stdin);
                    diff[strlen(diff) - 1] = '\0';

                    strcat(diff, "?");
                    char *string = calloc(DATA_LEN, sizeof(char));
                    strncpy(string, "Is your charachter \0", strlen("Is your charachter \0"));
                    //printf("New string is: %s", string);
                    strcat(string, diff);

                    Tree_AddLeft(akinator_t, c_leaf, c_leaf->data);
                    Tree_AddRight(akinator_t, c_leaf, name);

                    c_leaf->data = string;
                    printf("\nChiao!\n");
                    break;
                }
            }
        }
        else {
            printf("I can't understand you. Try again\n");
            printf("%s", c_leaf->data);
        }
        fgets(ans, DATA_LEN, stdin);
        ans[strlen(ans) - 1] = '\0';
    }

    Tree_Dump(akinator_t, __LINE__);
    Akinator_Dump(akinator_t);
}

void Akinator_Dump(struct Tree *ak) {
    FILE *Dump_f = fopen("ADump.txt", "w");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "digraph Tree {\n");
    fclose(Dump_f);

    Akinator_Leaf_Dump(ak->root, 1);

    Dump_f = fopen("ADump.txt", "a");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "}");
    fclose(Dump_f);

    system ("dot -Tpng ADump.txt -o ADump.png");
    system("ADump.png");
}

void Akinator_Leaf_Dump (struct Leaf *leaf, int leaf_num) {
    if (leaf == NULL) {
        return ;
    }

    int left = lefts;
    Akinator_Leaf_Dump(leaf->left, lefts++);

    FILE *Dump_f = fopen("ADump.txt", "a");
    assert(Dump_f != NULL);

    fprintf(Dump_f, "node%d [label=\"%s\"];\n", leaf_num, leaf->data);
    if (leaf->left != NULL) {
        fprintf(Dump_f, "edge [color = red];\n");
        fprintf(Dump_f, "node%d -> node%d;\n", leaf_num, left);
    }
    if (leaf->right != NULL) {
        fprintf(Dump_f, "edge [color = green];\n");
        fprintf(Dump_f, "node%d -> node%d;\n", leaf_num, rights);
    }

    //printf("%s", leaf->data);

    fclose(Dump_f);

    Akinator_Leaf_Dump(leaf->right, rights++);
}

int Am_I_Right() {
    printf("\nAm I right?\n");

    char *ans = calloc(DATA_LEN, sizeof(char));
    fgets(ans, DATA_LEN, stdin);
    ans[strlen(ans) - 1] = '\0';

    if (strcmp(ans, "y") == 0) {
        printf("Chiao!\n");
        return 1;
    }
    else if (strcmp(ans, "n") == 0) {
        printf("Who is your character?\n");
        return 0;
    }
    else {
        printf("I can't understand you. Try again\n");
        Am_I_Right();
    }
}