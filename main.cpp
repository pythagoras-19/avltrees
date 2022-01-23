/* Populate a tree via a text file (input.txt) 
Make sure that after every insert, the tree is balanced. At the end, display the tree in level format. 
Make sure to include the height and the balance factor of every node in your output. 
Redirect the display to  an output file (output.txt)*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct node // for tree
{
    int key;
   // node* next; //maybe not
    int height; // we can calculate balance with this
    node* left;
    node* right;
    node* current;
    node* next;
    
    //node* front;
    //node* rear;
};
/*
struct Node //for queues
{
    node* current;
    int value;
    Node* next;
    Node* prev;
    Node* left;
    Node* right;
};
*/
int max(int height1, int height2)
{
    std::cout << "in max function with " << height1 << " " << height2 << std::endl;
    int max = 0;
    if (height1 > height2)
    {
        max = height1;
    }
    else if (height2 > height1)
    {
        max = height2;
    }
    else //they are the same dont matter
    {
        max = height1;
    }
    return max;
}
int height(node* node)
{
    //std::cout << "height()\n";
    int height =-999;
    if(!node)
    {
        return -1;
    }
    return node->height;
}
int getBalance(node* node)
{
    //std::cout << "getBalance()\n";
    return (height(node->left) - height(node->right));
}
//QUEUES
bool isEmpty(node *&front)    // checking if our queue is empty
{
	if(!front)                // if queue has no elements
	{
		return true;        // queue is empty
	}
	else return false;      // else queue is NOT empty
}
void dequeue(node* &front, node* &rear) // remove from front
{
    //std::cout << "dequeue()\n";
    //FILE* fp;
    //const char fileName[100] = "output.txt";
    //fp = fopen(fileName, "w");
	node* temp; // used to hold the item we want to delete
	//this is where we need to focus
	if(front)  // if there is an item there that we can dequeue
	{
        //fprintf(fp, "%d", front->value);
		temp = front;         // temp = front value so we can dequeue temp
		front = front->next;  // make our new front the element after front
		delete temp;          // dequeue
		if(!front)            // empty list, can't dequeue
		{
			rear = NULL;
		}
	}
}
//pass by alias to affect front and rear directly
void enqueue(node* &front, node* &rear, node* myNode) // put it at the end 
{
    //std::cout << "enqueue()\n";
    node* nn = new node;
    //std::cout << "1" << myNode->key << std::endl;
    nn = myNode;      // new node value gets our passed value
	nn->next = NULL;        // end value
	//differentiate between an empty queue and not empty queue
	if(!front) // checking if empty
	{
		//std::cout << "In !front(), nn->value: " << nn->value << std::endl;
		rear = front = nn; // first assignment so both the rear and front get nn as their value
		//assign rear and front with the Node nn
	}
	else //not an empty list, insert another node
	{
		//std::cout << "In else(), nn->value: " << nn->value << std::endl;
		rear->next = nn; // the old rear's next member points to our new node
		rear = nn;       // nn becomes the new rear in our list (enqueue happens at the rear)
	}
}
/*
void traverse(Node* front, Node* rear)
{
	std::cout << "In traverse() " << std::endl;
	Node* currentNode;
	for(currentNode = front; currentNode; currentNode = currentNode->next)
	{
		std::cout << currentNode->value << std::endl;
	}
}
*/

//rotations
node* rightRotation(node* x)
{
    node* y = x->left;
    node* z = y->right;
    //the rotation
    x->left = z;
    y->right = x;
    //created a null leaf node to solidify concept
    //node* nullLeafNode;
    //nullLeafNode->height = -1;
    // recalculate the heights of x and y
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
node* leftRotation(node* x)
{
    std::cout << "leftRotation(" << x->key << ")" << std::endl;
    node* y = x->right;
    node* z = y->left;
    std::cout << "here\n";
    x->right = z;
    y->left = x;
    std::cout << "here1\n";
   // node* nullLeafNode = new node;
   // nullLeafNode->height = -1;
    //recalculate the heights of x and y
    //x->height = max(y->height, nullLeafNode->height) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    //y->height = max(nullLeafNode->height, z->height) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

   return y;
}
node* doubleRotationLeft(node* x)
{
    /*
    //left inside heavy "+ -", rotate left, then rotate right
    node* y = x->left;
    node* z = y->right;
    //rotate left
    y->left = z;
    //rotate right
    x->left = z;
    y->right = x;
    */
    //node* nullLeafNode;
    //nullLeafNode->height = -1;
    // recalculate the heights of x and y
 /*
 UPDATED
    node* w = x->left;
    node* y = w->right;
    node* z = y->left;
    //left rotation
    y->left = w;
    w->right = z;
    x->left = y;
    //right rotation
    z = y->right; // z =NULL with height of -1
    y->right = x; // the rotation
    x->left = z; // the rotation
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
*/
    x->left = leftRotation(x->left);
    x = rightRotation(x);
    return x;
    
}
node* doubleRotationRight(node* x)
{
    //right inside heavy "- +", rotate right, then rotate left
    /*
    node* y = x->right;
    node* z = y->left;
    //rotate right
    y->right = z;
    //rotate left
    x->right = z;
    y->left = x;
   // node* nullLeafNode;
    //nullLeafNode->height = -1;
    //recalculate the heights of x and y
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

   return y;
   */
  x->right = rightRotation(x->right);
  x = leftRotation(x);
  return x;

}


//new AVL tree function to rebalance our tree so it is an AVL tree
//this makes it easier to search and find elements within a tree
node* rebalance(node* node)
{
    std::cout << "in rebalance(" << node->key << ")" << std::endl;
    /*
    std::cout << "rebalance() with " << node->key << std::endl;
    std::cout << "node->right->height: " << node->right->height << std::endl;
    std::cout << "node->left->height: " << node->left->height << std::endl;// SEG FAULTS HERE because there is no node->left
    int maxHeight = max(node->left->height, node->right->height);
    std::cout << "maxHeight: " << maxHeight << std::endl;
    */
    node->height = max(height(node->left), height(node->right)) + 1; // + 1 because we start at 0
    int balance = getBalance(node); // our trigger to rotate!
    std::cout << "balance of " << node->key << "= " << balance << std::endl;
    //height of null (empty leaf node) = -1

    //if balance = 2, tree is left heavy, move to the left
    //evaluate the balance of the middle node,
    //if the middle node is positive : do a right rotation
    if(balance > 1 && (getBalance(node->left) > 0))
    {
        //single right rotation
        std::cout << "single right rotation on : "  << node->key << std::endl;
        return rightRotation(node);
    }
    else if(balance > 1 && (getBalance(node->left) < 0))
    {
        //double rotation of leaf/node
        std::cout << "double rotation left on: " << node->key << std::endl;
        return doubleRotationLeft(node);
    }
    //if balance = -2, tree is right heavy, move to the right
    //evaluate the balance of the middle node,
    //if the middle node is negative :  do a left rotation
    if(balance < -1 && (getBalance(node->right) < 0))
    {
        //single left rotation
        std::cout << "single left rotation on : "  << node->key << std::endl;
        return leftRotation(node);
    }
    else if (balance < -1 && (getBalance(node->right) > 0))
    {
        //double rotation of leaf/node
        std::cout << "double rotation right on: " << node->key << std::endl;
        return doubleRotationRight(node);
    }
    else return node;
}
//helper funciton to find min value node in the subtree rooted at 'current'
//used in a delete where the node has two children and we need to 
//restructure the subtree or entire tree
node* getMinimumKey(node* current)
{
    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
// A utility function to do
// inorder traversal of BST
void inorder(node* root)
{
    if (root != NULL) {
        inorder(root->left);
        int bal = getBalance(root);
        std::cout << root->key << ", height: " << root->height << " balance: " << bal << std::endl;
        inorder(root->right);
    }
}
//iterative function to search in the subtree rooted at 'current' and set its parent.
//current and parent are passed by reference
void searchKey(node*& current, int key, node*& parent)
{
    while(current != NULL && current->key != key)
    {
        parent = current; // update the parent to the current node
        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        
    }
}
bool searchNoRecursion(node* leaf, int key){
    bool found=false;
    
    //use a while loop and not recursion. Leaf is being changed
    //each and every time to point to the left or right, going down
    //the tree.
    while (leaf && !found){ 
        if (key==leaf->key){
            found=true;
        }else if (key < leaf->key)
            leaf = leaf->left; //replaces recursion
        else
            leaf = leaf->right;
    }
    return found;
}


//how professor did insert() operations:
//this function is mine
//this function is for inserting a new node
node* newNode(int key)
{
    std::cout << "newNode(" << key << ")\n";
    node* newNode = new node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    std::cout << "returning " << newNode->key << std::endl;
    return newNode;
}
// he did the insert() this way:
node* insert(node* node, int key)
{
    //recursive Code for inserting a node 
    //When insert happens set height to 0 for the node     
    std::cout << "insert(" << key << ")\n";
    //place to insert
    if (node == NULL)
    {
        return(newNode(key)); // returns to initial call in main() for first root insert
        // else returns to its respective call below dependent on if the key is < or > than the node->key
        //dont need to rebalance initial insert()
    }
    //elements in tree find leaf position
    std::cout << "node->key = " << node->key << std::endl;
    if (key < node->key)
    {
        std::cout << node->key << "'s left child is now: " << key << std::endl;
        node->left  = insert(node->left, key);
    }
    else
    {
        std::cout << node->key << "'s right child is now: " << key << std::endl;
        node->right = insert(node->right, key);
    }
    node = rebalance(node);  //update heights and rebalance after EVERY insert()
    return node;

}


//printing level by level
void printLevel(node* root)
{
    if (root == NULL)
    {
        return;
    }
    FILE* fp;
    const char fileName[100] = "output.txt";
    fp = fopen(fileName, "w");
    //else create a queue
    node* front = NULL;
    node* rear = NULL;
    node* current = root;
    int nodesOnCurrentLevel = 0;
    int nodesInNextLevel = 0;
    enqueue(front, rear, root); // inserted root node in queue
   // Node* current = front;
    current = front;
    nodesOnCurrentLevel ++; // nodesOnCurrentLevel = 1
    while(nodesOnCurrentLevel != 0)
    //while (!(isEmpty(front))) //while there is at least one discovered node
    {
        current = front;
        //dequeue and display
        //dequeue(front, rear); //removing from front
        int bal = getBalance(current);
        std::cout << current->key << "- (height: " << current->height << ", bal: " << bal << ")" << " ";
        fprintf(fp, "%d - ", current->key);
        fprintf(fp, "(height: %d, balance: %d) ", current->height, bal);
        //nodesOnCurrentLevel--;
        //std::cout << current->key << " ";
        //dequeue(front,rear);
        //nodesOnCurrentLevel--;
       // std::cout << "current->left->key: " << current->left->key << std::endl;
        if(current->left != NULL)// curr needs to be updated
        {
            enqueue(front, rear, current->left);
            nodesInNextLevel++;
        }
        if (current->right != NULL)
        {
            enqueue(front, rear, current->right);
            nodesInNextLevel++;
        }
        //std::cout << current->value << " ";
        //fprintf(fp, "%s", "\n");
        dequeue(front, rear); //removing from front
        nodesOnCurrentLevel--;
        //std::cout << std::endl;
        
        if(nodesOnCurrentLevel == 0)
        {
            nodesOnCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
            std::cout << std::endl;
            fprintf(fp, "%s", "\n");
        }
        
    }
   

}

//read from file
//line by line insert into tree
//delete when read delete
//print out data at the end
int main()
{
    FILE *fp;
    char line[255]; // line of chars
    //int line[20];
    int number[20];
    char deleteWord[] = "delete";
    const char fileName[100] = "input.txt";
    fp = fopen(fileName, "r");
    node* root = NULL;
    while(fscanf(fp, "%s", line) != EOF)
    {
        std::cout << "line is now: " << line << std::endl;
        
        if(strcmp(line, deleteWord) == 0) //read "delete"
        {
            fscanf(fp, "%s", line); // read one more to get value of node we want to delete
            std::cout << "line is now: " << line << std::endl;
           // deleteNode(root, line);
        }
        else
    
        {
            std::cout << "inserting " << line << std::endl;
            root = insert(root, atoi(line));//typecasted line to an integer because insert uses comparisons
            //root = insert(root, *line);
            std::cout << "root is now: " << root->key << std::endl;
        }
    }

    //std::cout << "Opened " << fileName << std::endl;
    fclose(fp); //close the file
    std::cout << "done\n";
    //inorder(root);

    //display the tree in level format
    /*Now that we are balanced lets print level by level*/
    std::cout<<"\n\nPrint Level:\n";
    printLevel(root);
    return 0;
}
/*
    Node* front = NULL;
    Node* rear = NULL;

    enqueue(front, rear,root->key);
    enqueue(front, rear, (int)nullptr);
    while(true) // while queue not empty
    {
        Node* current = front;
        dequeue(front, rear);
        if(current != nullptr)
        {
            std::cout << current->value << " "; // all nodes on same level will print on same line separated by a " " 
            //if it has a left child we add it to the queue
            if (root->left != nullptr)
            {
                enqueue(front, rear, root->left->key);
            }
            //if it has a right child we add it to the queue
            if (root->right != nullptr)
            {
                enqueue(front, rear, root->right->key);
            }
        }
        else // current == NULL
        {
            //print a new line and check if the queue became empty
            std::cout << std::endl;
            if (isEmpty(front))//if queue is empty 
            {
                break;
            }
            enqueue(front, rear, NULL); //enqueue the last NULL
        }
    }
*/
/*
Node* front = NULL;
    Node* rear = NULL;
    node* curr = root;
    int nodesOnCurrentLevel = 0;
    int nodesInNextLevel = 0;
    enqueue(front, rear, root);
    Node* current = front;
    nodesOnCurrentLevel ++; // nodesOnCurrentLevel = 1
    while(nodesOnCurrentLevel != 0)
    {
        Node* current = front;
        //dequeue and display
        std::cout << front->value << " ";
        dequeue(front,rear);
        nodesOnCurrentLevel--;
        enqueue(front, rear, curr->left);
        nodesInNextLevel++;
        enqueue(front, rear, curr->right);
        nodesInNextLevel++;
        if(nodesOnCurrentLevel == 0)
        {
            nodesOnCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
            std::cout << std::endl;
        }
    }
*/
/*
//delete operations
void deleteNode(node*& root, char* number)//char* number)
{
    //search for the node with the value
    //BinaryTree *leaf; // just a pointer to a node to use during taversal to try to find our 'key'

    node* parent = NULL;//pointer to store the parent of the current node
    node* current = root;//starting with the root node
    bool booleanValForFoundInSearch = searchNoRecursion(current,*number);
    std::cout << "Found: " << booleanValForFoundInSearch << std::endl;
    if(booleanValForFoundInSearch == true)
    {
        searchKey(current, atoi(number), parent); // search key in the BST And set its parent pointer

        //no children-- it is a leaf node
            if(current->left == NULL && current->right == NULL)
            {
                if(current != root)//if the node to be deleted is NOT a root node, the set its parent left or right child to NULL
                {
                    if(parent->left == current)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }   
                }
                else // if the tree has only a root node, set it to null
                {
                    root = NULL;
                }
                delete(current); //deallocate memory
            }
        //two children
            else if(current->left && current->right)
            {
                node* successor = getMinimumKey(current->right);//find its inorder successor node
                int successorValue = successor->key; // store successor value
                //recursively delete the successor.
                //successor will have at most one child (the right child)
                char buffer[40];
                deleteNode(root, (char*)successor->key); //had to typecast it to char*
                //itoa(successor->key,buffer,10));
                current->key = successorValue; // copy value of the successor to the current node
            }

        //one child
            else
            {
                node* child;
                //choosing a child
                if(current->left)
                {
                    child = current->left;
                }
                else
                {
                    child = current->right;
                }
                //if the node to be deleted is NOT a root node,
                //set its parent to its child
                if(current != root)
                {
                    if(current == parent->left)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                }
                //if the node to be deleted IS ROOT NODE, set the root to child
                else
                {
                    root = child;
                }
                delete(current); //deallocate the memory
            }
        
    }

}
*/
 /*
    if (root == nullptr)
    {
        return;
    }
    Node* front = NULL;
    Node* rear = NULL;
    enqueue(front, rear, root);
    enqueue(front, rear, nullptr);
    while(true)
    {
        Node* current = front;
        dequeue(front, rear);
        if(current != nullptr)
        {
            std::cout << current->value << " ";
            if (root->left != nullptr)
            {
                enqueue(front, rear, root->left);
            }
            if(root->right != nullptr)
            {
                enqueue(front, rear, root->right);
            }
        }
        else
        {
            std::cout << std::endl;
            if(isEmpty(front))
            {
                break;
            }
            enqueue(front, rear, nullptr);
        }
    }
    */
   //insert operations
//recursively insert, tail rescursive, no return ops, ideal, nothing to do on return of recursion
//make connection on insert
//below is the old insert()
/*
void insert(node *& leaf, int item){
    if (!leaf){// Insertion place found.
        leaf = new node;
        leaf->right = NULL;
        leaf->left = NULL;
        leaf->key = item;
        leaf->height = 0; // NEW FOR THIS AVL Tree
    }
    else if (item < leaf->key)
        insert(leaf->left, item) ;    //Insert in left subtree.
    else if (item > leaf->key)
        insert(leaf->right, item) ;   //Insert in right subtree.	
}
*/
/*
// here is the new insert() from AVL tree lecture
//old insert updated with AVL traits that I did:

node* insert(node *& leaf, int item){
    if (!leaf){// Insertion place found.
        leaf = new node;
        leaf->right = NULL;
        leaf->left = NULL;
        leaf->key = item;
        leaf->height = 0; // NEW FOR THIS AVL Tree
        return (leaf); // NEW FOR THIS AVL Tree
    }
    else if (item < leaf->key)
        //insert(leaf->left, item) ;    //Insert in left subtree.
        leaf->left = insert(leaf->left, item);
    else if (item > leaf->key)
        //insert(leaf->right, item) ;   //Insert in right subtree.	
        leaf->right = insert(leaf->right, item);
    //leaf = balance(leaf, key); //new AVL TREE
    leaf = rebalance(leaf); // update heights and rebalance
    return leaf;
}
*/
