#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node
{
    char name[128];
    int is_file;
    int created_at;
    int updated_at;
    struct Node *parent;
    struct Node *next;
    struct Node *child;    
} Node;

Node *root = NULL;
Node *current = NULL;

void init();
void prompt();
Node *create_node(char *name, int is_file);
void insert_node(Node *node);
Node* search_node(char *name);
void path(Node *node);

void mkdir(char *name);
void touch(char *name);
void ls();
void enter(char *name);
void back();
void pwd();

int main()
{
    init();

    char command[64];
    char arg[128];

    while (1)
    {
        prompt();
        scanf("%s", command);

        if(strcmp(command, "mkdir") == 0)
        {
            scanf("%s", arg);
            mkdir(arg);
        }
        else if(strcmp(command, "touch") == 0)
        {
            scanf("%s", arg);
            touch(arg);
        }
        else if(strcmp(command, "ls") == 0)
        {
            ls();
        }
         else if(strcmp(command, "enter") == 0)
        {
            scanf("%s", arg);
            enter(arg);
        }
        else if(strcmp(command, "back") == 0)
        {
            back();
        }
        else if(strcmp(command, "pwd") == 0)
        {
            pwd();
        }
        else if(strcmp(command, "exit") == 0)
        {
            printf("Exiting VFSSHell...\n");
            break;
        }
        else
        {
            printf("VFSSHell : command not found: %s\n", command);
        }
    }

    return 0;
}

void init()
{
    root = malloc (sizeof(Node));

    strcpy(root->name, "root");
    root -> is_file = 0;
    root -> created_at = time(NULL);
    root -> updated_at = time(NULL);
    root -> parent     = NULL;
    root -> next       = NULL;
    root -> child      = NULL;

    current = root;

}

void prompt()
{
    printf("\u279c %s ", current->name);
}

Node *created_node(char *name, int is_file)
{
    Node *node = malloc(sizeof(Node));

    strcpy(node -> name, name);
    node -> is_file    = is_file;
    node -> created_at = time(NULL);
    node -> updated_at = time(NULL);
    node -> parent     = current;
    node -> next       = NULL;
    node -> child      = NULL;


    return node;
}

void insert_node(Node *node)
{
    if(current->child == NULL)
    {
        current -> child = node;
    }
    else
    {
        Node *temp = current -> child;
        while (temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = node;
    }
}

void mkdir (char *name)
{
    Node *node = created_node(name, 0);
    insert_node(node);
}

void touch(char *name)
{
    Node *node = created_node(name, 1);
    insert_node(node);
}
void print_node (Node *node)
{
    if(node -> is_file)
    {
        printf("%s\n", node -> name);
    }
    else
    {
        printf("%s\n", node -> name);
    }
}

void ls()
{
    Node *temp = current -> child;
    while (temp != NULL)
    {
        print_node(temp);
        temp = temp -> next;
    }
}

Node *search_node(char *name)
{
    Node *temp = current -> child;
    while (temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
        {
            return temp;
        }
        temp = temp -> next;
    }

    return NULL;
}

void enter(char *name)
{
    Node *node = search_node(name);
    if(node != NULL)
    {
        current = node;
    }
    else
    {
        printf("VFSSHell : no such file or directory : \n");
    }
}

void back()
{
    if(current != root)
    {
        current = current -> parent;
    }
    else
    {
        printf("VFSShell : already root. \n");
    }
}

void path(Node *node)
{
    if(node == root)
    {
        printf("%s/", node -> name);
        return;
    }
    else if(node -> parent != NULL)
    {
        path(node -> parent);
    }
    printf("%s/", node -> name);
}

void pwd()
{
    path(current);
    printf("\n");
}