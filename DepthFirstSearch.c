#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node{
    char data[255];
    int weightData;
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


void sort(char* unsortedVertexArr[], int numVertex, char* sortedVertexArr[]) {
    for (int i = 0; i < numVertex; i++) {
        char lowest[255];
        int k = 0;
        while (strcmp(unsortedVertexArr[k], " ") == 0) {
            k++;
        }
        strcpy(lowest, unsortedVertexArr[k]);
        int index = k;
        for (int j = 0; j < numVertex; j++) {
            if (strcmp(unsortedVertexArr[j], " ") != 0 && strcmp(lowest, unsortedVertexArr[j]) > 0) {
                strcpy(lowest, unsortedVertexArr[j]);
                index = j;
            }
        }
        sortedVertexArr[i] = (char*)malloc(strlen(lowest)+1*sizeof(char));
        strcpy(sortedVertexArr[i], lowest);
        strcpy(unsortedVertexArr[index], " ");
    }
}



void insertEdge(struct Node** head, char edgeName[], int weight){
    struct Node* ptr = *head;
    if (ptr == NULL) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->weightData = weight;
        new->next = NULL;
        *head = new;
        return;
    }

    while(ptr->next != NULL && strcmp(ptr->data, edgeName) == -1) {
        if (strcmp(ptr->next->data, edgeName) == 1) {
            struct Node* new = (struct Node*) malloc(sizeof(struct Node));
            strcpy(new->data, edgeName);
            new->weightData = weight;
            new->next = ptr->next;
            ptr->next = new;
            return;
        }
        ptr = ptr->next;
    }
    if (strcmp(ptr->data, edgeName) == 1) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->weightData = weight;
        new->next = ptr;
        *head = new;
        return;
    }
    if (strcmp(ptr->data, edgeName) == -1) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->weightData = weight;
        new->next = NULL;
        ptr->next = new;
        return;
    }

    return;
}


int countEdgeOut(struct Node* head) {
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


int checkEdgeIn(struct Node* head, char edgeName[]) {
    if (head == NULL) {
        return 0;
    }
    while(head) {
        if (strcmp(head->data, edgeName) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}


//insert at end
void enqueue(struct Node** head, char edgeName[]){
    struct Node* ptr = *head;
    if (ptr == NULL) {
        struct Node* new = (struct Node*) malloc(sizeof(struct Node));
        strcpy(new->data, edgeName);
        new->next = NULL;
        *head = new;
        return;
    }

    while(ptr->next != NULL) {
        if (strcmp(ptr->data, edgeName) == 0) return;
        ptr = ptr->next;
    }
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    strcpy(new->data, edgeName);
    new->next = NULL;
    ptr->next = new;
    return;
}


//return 1 if a node is already in the visited list
int checkVisited(char name[], struct Node* vhead) {
    while (vhead) {
        if (strcmp(name, vhead->data) == 0) return 1;
        vhead = vhead->next;
    }
    return 0;
}


//remove first node in queue
void pop(struct Node** head){
    struct Node* current = *head;

    if (current == NULL) return;
    
    (*head) = current->next;
    free(current);
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


void DFS(struct Node** vhead, char vertexName[], struct Node* arrEdgePtr, char* vertexArr[], int numVertex, struct Node** arrEdge) {
    if (checkVisited(vertexName, *vhead) == 0) {
        enqueue(vhead, vertexName);
        while (arrEdgePtr) {
            strcpy(vertexName, arrEdgePtr->data);
            int index = vertexIndex(vertexArr, vertexName, numVertex);
            DFS(vhead, vertexName, arrEdge[index], vertexArr, numVertex, arrEdge);
            arrEdgePtr = arrEdgePtr->next;
        }
    }
    else {
    }
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
    char **unsortedVertexArr;
    unsortedVertexArr = malloc(numVertex * sizeof(char*));
    char vertexName[255];

    for (int i = 0; i < numVertex; i++) {
        fscanf(fp, "%s", vertexName);
        unsortedVertexArr[i] = (char*)malloc(strlen(vertexName)+1*sizeof(char));
        strcpy(unsortedVertexArr[i], vertexName);
    }  

    char **vertexArr;
    vertexArr = malloc(numVertex * sizeof(char*));
    sort(unsortedVertexArr, numVertex, vertexArr);

    //create array of ptrs representing edges
    struct Node** arrEdge = malloc(numVertex * sizeof(*arrEdge));
    for (int i = 0; i < numVertex; i++) {
        arrEdge[i] = NULL;
    }
    
    
    //insert edges for both the new vertex and its adjacent vertex's index
    char newVertexName[255];
    int weight;
    while(fscanf(fp, "%s %s %d", vertexName, newVertexName, &weight) != EOF) {
        int index = vertexIndex(vertexArr, vertexName, numVertex);
        insertEdge(&arrEdge[index], newVertexName, weight);
    }


    //query
    struct Node* vhead = NULL;
    for (int i = 0; i < numVertex; i++) {
        if (checkVisited(vertexArr[i], vhead) == 0) {
            strcpy(vertexName, vertexArr[i]);
            int index = vertexIndex(vertexArr, vertexName, numVertex);
            DFS(&vhead, vertexName, arrEdge[index], vertexArr, numVertex, arrEdge);
        }
    }
    print_list(vhead);
    

    //free malloc
    for (int i = 0; i < numVertex; i++) {
        free(vertexArr[i]);
        free(unsortedVertexArr[i]);
        while (arrEdge[i] != NULL) {
            struct Node* tempPtr = arrEdge[i];
            arrEdge[i] = arrEdge[i]->next;
            free(tempPtr);
        }
    }
    while (vhead != NULL) {
        struct Node* tempPtr = vhead;
        vhead = vhead->next;
        free(tempPtr);
    }

    free(arrEdge);
    free(vertexArr);
    free(unsortedVertexArr);

    return EXIT_SUCCESS;

}