#include <stdio.h>
#include <stdlib.h>

// tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

// A utility function to create a new BST node
struct Node* newNode(int key);
struct Node* insert(struct Node* node, int key);
void inorder(struct Node* root);
struct Node* search(struct Node* root, int key);
struct Node* createTree(const char* fileName);

int height(struct Node* node);

void printLevelOrder(struct Node* root);
void printCurrentLevel(struct Node* root, int level,int *count);

void findLevel(struct Node* root,int key);
void findCurrentLevel(struct Node* root, int level,int key,int* found,int* distance);



int main(){

    struct Node* root;
    printf("\n\n");

    root = createTree("data.txt");
    printf("Tree: ");
    inorder(root);
    printf("\n");

    printf("Depth level of BST: %d\n",height(root));
    printLevelOrder(root);


    while(1){

        int number;
        printf("Key to be searched (0 to exit): ");
        scanf("%d",&number);
        if(number == 0){
            break;
        }


        findLevel(root,number);
    }



    printf("\n\n");
    return 0;
}


struct Node* createTree(const char* fileName){
    struct Node* node = NULL;

    FILE *myFile;
    myFile = fopen(fileName, "r");

    //read file into array
    int number;

    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }

     while( fscanf(myFile, "%d,", &number) > 0 ) 
    {
        node = insert(node,number);
    }
    fclose(myFile);

    return node;
}

struct Node* newNode(int key)
{
    struct Node* temp
        = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

// print tree
void inorder(struct Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct Node* search(struct Node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;
   
    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

int height(struct Node* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void printLevelOrder(struct Node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++){
        int c = 0;
        int *count = &c;
        printCurrentLevel(root, i,count);
        printf("Depth Level %d -> %d\n",i-1,*count);
    }
}

/* Print nodes at a current level */
void printCurrentLevel(struct Node* root, int level , int *count)
{
    if (root == NULL)
        return;
    if (level == 1)
        (*count)++;
        // printf("%d ", root->key);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1,count);
        printCurrentLevel(root->right, level - 1,count);
    }
}

void findLevel(struct Node* root,int key){
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++){
        int f = 0;
        int d= 0;
        int *found = &f;
        int *distance = &d;

        findCurrentLevel(root, i,key,found,distance);

        if((*found) > 0){
            printf("Found at Depth Level %d , %dth element \n",i-1,*found);
            return;
        }
    }
    printf("Not found! \n\n");

}
void findCurrentLevel(struct Node* root, int level,int key,int *found,int* distance){
     if (root == NULL)
        return;
    if (level == 1){
        (*distance)++; // count distance
        if(root->key == key){
            (*found) = (*distance);
        }
    }
        // printf("%d ", root->key);
    else if (level > 1) {
        findCurrentLevel(root->left, level - 1,key,found,distance);
        findCurrentLevel(root->right, level - 1,key,found,distance);
    }
}
