#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node{
    char data[255];
    struct Node* next;
};


int vertexIndex(char *vertexArr[], char edgeName[], int numVertex) {
    for (int i = 0; i < numVertex; i++) {
        if (strcmp(vertexArr[i], edgeName) == 0) {
            return i;
        }
    }
    return 0;
}


void insertEdge(struct Node** head, char edgeName[]){
    struct Node* ptr = *head;
    if (ptr == NULL) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->next = NULL;
        *head = new;
        return;
    }

    while(ptr->next != NULL && strcmp(ptr->data, edgeName) == -1) {
        if (strcmp(ptr->next->data, edgeName) == 1) {
            struct Node* new = (struct Node*) malloc(sizeof(struct Node));
            strcpy(new->data, edgeName);
            new->next = ptr->next;
            ptr->next = new;
            return;
        }
        ptr = ptr->next;
    }
    if (strcmp(ptr->data, edgeName) == 1) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->next = ptr;
        *head = new;
        return;
    }
    if (strcmp(ptr->data, edgeName) == -1) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->next = NULL;
        ptr->next = new;
        return;
    }

    return;
}


int countEdge(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    int count = 0;
    while(head) {
        count++;
        head = head->next;
    }
    return count;
}


void print_list(struct Node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }
    while(head) {
        printf("%s",head->data);
        if (head->next != NULL) printf(" ");
        head = head->next;
    }
    printf("\n");
}


int main(int argc, char** argv){
    
    FILE *fp;
    fp = fopen(argv[1], "r");

    if(fp == NULL) {
        printf("error\n");
        exit(0);
        return 0;
    }

    int numVertex;
    fscanf(fp, "%d", &numVertex);

    
    //create array of strings representing vertices
    //char *vertexArr[numVertex];
    char **vertexArr;
    vertexArr = malloc(numVertex * sizeof(char*));
    char vertexName[255];

    for (int i = 0; i < numVertex; i++) {
        fscanf(fp, "%s", vertexName);
        vertexArr[i] = (char*)malloc(strlen(vertexName)+1*sizeof(char));
        strcpy(vertexArr[i], vertexName);
    }


    //create array of ptrs representing edges
    struct Node** arrEdge = malloc(numVertex * sizeof(*arrEdge));
    for (int i = 0; i < numVertex; i++) {
        arrEdge[i] = NULL;
    }
    
    
    //insert edges for both the new vertex and its adjacent vertex's index
    char newVertexName[255];
    while(fscanf(fp, "%s %s", vertexName, newVertexName) != EOF) {
        int index = vertexIndex(vertexArr, vertexName, numVertex);
        insertEdge(&arrEdge[index], newVertexName);

        index = vertexIndex(vertexArr, newVertexName, numVertex);
        insertEdge(&arrEdge[index], vertexName);
    }


    //queries
    fp = fopen(argv[2], "r");
    char command[255];
    while(fscanf(fp, "%s", command) != EOF) {
        if (strcmp(command, "d") == 0) {
            fscanf(fp, "%s", vertexName);
            int index = vertexIndex(vertexArr, vertexName, numVertex);
            printf("%d\n",countEdge(arrEdge[index]));
        }
        if (strcmp(command, "a") == 0) {
            fscanf(fp, "%s", vertexName);
            int index = vertexIndex(vertexArr, vertexName, numVertex);
            print_list(arrEdge[index]);
        }
    }

    //free malloc
    for (int i = 0; i < numVertex; i++) {
        free(vertexArr[i]);
        while (arrEdge[i] != NULL) {
            struct Node* tempPtr = arrEdge[i];
            arrEdge[i] = arrEdge[i]->next;
            free(tempPtr);
        }
    }
    free(arrEdge);
    free(vertexArr);

    return EXIT_SUCCESS;

}