#include <stdio.h>
#include <stdlib.h>

#define N 8

int data[N] = {1,5,3,4,6,6,2,8};

typedef struct node {
    int key;
    struct node *left, *right;
}NODE;

typedef struct queue{
    struct queue *nextQueueItem;
    struct node *treeNode;
}QE;

QE *newQueueItem(NODE *node);
void enqueue(QE **queue, NODE *node);
NODE *dequeue(QE **queue);
int  queueLength(QE *queue);
void printByLevel(NODE *rootNode);
NODE *newNode(int key);
NODE *insertNewNode(NODE *rootNode, int newKey);
NODE *findNodeToBeParent(NODE *rootNode, int newKey);
NODE *insert(NODE *parentNode, NODE *nweNode);

QE *newQueueItem(NODE *node){
    QE *q = (QE *)malloc(sizeof(QE));
    q->treeNode = node;
    q->nextQueueItem = NULL;
    return q;
}

void enqueue(QE **queue, NODE *node){
    if(NULL == node) return;
    QE *q = *queue;
    if(NULL == q){
       *queue = newQueueItem(node); 
    }else{
        while(q->nextQueueItem){
            q = q->nextQueueItem;
        }
        q->nextQueueItem = newQueueItem(node);
    }
}

NODE *dequeue(QE **queue){
    if(*queue == NULL)return NULL;
    QE *q = *queue;
    *queue = q->nextQueueItem;
    return q->treeNode;
}

int queueLength(QE *queue){
    int n =0;
    while(queue){
        n++;
        queue = queue->nextQueueItem;
    }
    return n;
}

void printByLevel(NODE *rootNode){
    if(NULL == rootNode){
        return;
    }
    int nodeCountPerLevel;
    QE *queue = 0;
    enqueue(&queue, rootNode);
    while(1){
        nodeCountPerLevel = queueLength(queue);
        if(0 == nodeCountPerLevel) break;
        while(0 < nodeCountPerLevel){
            NODE *node = dequeue(&queue);
            printf("%d ", node->key);
            if(NULL != node->left){
                enqueue(&queue,node->left);
            }
            if(NULL != node->right){
                enqueue(&queue, node->right);
            }
            nodeCountPerLevel--;
        }
        printf("\n");
    }
}

NODE *newNode(int key){
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

NODE *findNodeToBeParent(NODE *rootNode, int newKey){
    NODE *parent = NULL;
    NODE *currentNode = rootNode;
    while(currentNode){
        parent = currentNode;
        if(newKey < currentNode->key){
            currentNode = currentNode->left;
        }else if(newKey > currentNode->key){
            currentNode = currentNode->right;
        }else{
            return NULL;
        }
    }
    return parent;
}

NODE *insert(NODE *parentNode, NODE *newNode){
    if(newNode->key > parentNode->key){
        parentNode->right = newNode;
    }else{
        parentNode->left = newNode;
    }
}

NODE *insertNewNode(NODE *rootNode, int newKey){
    NODE *node = newNode(newKey);
    if(NULL == rootNode){
        return node; 
    }
    NODE *parentNode = findNodeToBeParent(rootNode, newKey);
    if(NULL == parentNode) return NULL;
    insert(parentNode, node);
}

int main(){
    int i;
    NODE *root = NULL;
    root = insertNewNode(root,data[0]);
    for(i = 1; i < N; i++){
        insertNewNode(root,data[i]);
    }
    if(NULL == root){
        printf("No item in the Binary Search Tree\n");
        return 0;
    }
    printByLevel(root);
}