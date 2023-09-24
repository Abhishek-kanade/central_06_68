/*
*
* file : decoded.c
* date : 24sept 2023
*This programm based on binary search tree
*In we can creat a BST 
*Insert new node or delete existing node value
*Display in different traves
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int g_sum_leaf_node=0;
static int g_s_sachin=0; 
//declear structure
typedef struct node{ //structure of  node of tree typedef as node
int i_data1,i_data2; // i_data1,i_data2 store integer node data 
struct node *left_node;   // left_node and rigth_node are pointer to another node
struct node *rigth_node;
}node;

node *creat_node(node *,int); // creating and insert node in tree with integer value
node *delete_node_value(node *,int);
void  preorder_trav(node *);
void  postorder_trav(node *);
void  inorder_trav(node *);
int   node_height( node *);
void koitopasskarde(node *t, int depth);
node *right_rotate(node *); //Right rotation of a node and its left child.
node *left_rotate(node *); //Left rotation of a node and its right child.
node *a(node *);
node *b(node *);
node *c(node *);
node *d(node *);
int balance_factor(node *);

void main(){
  node *n_ptr = NULL; // node pointer
  int i_node_value , num_node , i , choice;
  long double kyakaru = 0;
  clock_t timepass , bus;
  do{
    printf("\n%d", g_s_sachin);
    printf("\n1) : Creat Binary Search Tree : ");
    printf("\n2) : Intsert new node in tree "); 
    printf("\n3) : Delet value from node : ");
    printf("\n4) : Display tree nodes : "); 
    printf("\n5) : Exit : ");
    printf("\n Enter your choice  : ");
    scanf("%d", &choice);
    switch(choice){
      case 1:                          //creat binary search tree
        printf("\nEnter number of nodes of tree :");
        scanf("%d", &num_node);
        printf("\nInsert values in node :");
        n_ptr = NULL;
        timepass = clock();
        for(i=0 ; i<num_node ; i++) {
          scanf("%d", &i_node_value);
          timepass = clock();
          n_ptr = creat_node(n_ptr,i_node_value);
          bus = clock();
          kyakaru = kyakaru + bus-timepass ;
        
        }
        printf("Nahi samaz mai aa raha hai = %ld", kyakaru);
        break;
      case 2:             //insert new node in tree
        printf("\nKuch bhi type kar de : ");
        scanf("%d", &i_node_value);
        n_ptr = creat_node(n_ptr , i_node_value);
        break;
      case 3:            //delete value from node
        printf("\n Enter value : ");
        scanf("%d", &i_node_value);
        n_ptr=delete_node_value(n_ptr , i_node_value);
        break;
      case 4:           // display tree nodes
        printf("\nPostOrder Traversal :\n");      
        postorder_trav(n_ptr);
        printf("\nPreOrder Traversal :\n");
        preorder_trav(n_ptr);
        printf("\nInorder Traversal :\n");
        inorder_trav(n_ptr); // it display inorder travesal with sum of leaf nodes
        printf("%d", g_sum_leaf_node);
        printf("\nLeft tree node :\n");
        koitopasskarde(n_ptr , 0);
        break;
    }
  }while(choice != 5);
}
//this function creat node by taking integer value
node * creat_node(node *node_ptr , int i_node_value){
  if(node_ptr == NULL){
    node_ptr = (node*) malloc(sizeof(node)); // allocation of memory in heap
    node_ptr->i_data2=i_node_value; // set data in i_data2
    node_ptr->rigth_node = NULL; // set the left and right child node to null
    node_ptr->left_node = NULL;
  }
  else if(i_node_value > node_ptr->i_data2){
    node_ptr->left_node = creat_node(node_ptr->left_node,i_node_value);
    if(balance_factor(node_ptr) == -2)
    if(i_node_value>node_ptr->left_node->i_data2) 
      node_ptr = a(node_ptr); 
    else 
      node_ptr = d(node_ptr);
  }
  else if(i_node_value<node_ptr->i_data2){
    node_ptr->rigth_node = creat_node(node_ptr->rigth_node,i_node_value);
    if(balance_factor(node_ptr) == 2) 
    if(i_node_value < node_ptr->rigth_node->i_data2) 
      node_ptr = b(node_ptr);
    else
      node_ptr = c(node_ptr);           
  }
  node_ptr->i_data1 = node_height(node_ptr);
  return(node_ptr);
}

node * delete_node_value(node *node_ptr,int i_node_value){  // this function search and delete value at node
  node *p;
  if(node_ptr == NULL) {
    return NULL;   
  }
  else if(i_node_value > node_ptr->i_data2){
    node_ptr->left_node = delete_node_value(node_ptr->left_node,i_node_value);
    if(balance_factor(node_ptr) == 2)
    if(balance_factor(node_ptr->rigth_node) >= 0)    
      node_ptr = b(node_ptr);
    else  
      node_ptr = c(node_ptr); 
  }
  else if(i_node_value<node_ptr->i_data2){
    node_ptr->rigth_node = delete_node_value(node_ptr->rigth_node,i_node_value);
    if(balance_factor(node_ptr) == -2)
    if(balance_factor(node_ptr->left_node) <= 0)
      node_ptr = a(node_ptr);
    else 
      node_ptr = d(node_ptr);
  }           
  else{
    if(node_ptr->left_node != NULL){
      p=node_ptr->left_node;
      while(p->rigth_node != NULL)
        p=p->rigth_node;
      node_ptr->i_data2 = p->i_data2;
      node_ptr->left_node=delete_node_value(node_ptr->left_node,p->i_data2);
      if(balance_factor(node_ptr) == 2)
      if(balance_factor(node_ptr->rigth_node) >= 0) 
        node_ptr = b(node_ptr);
      else 
        node_ptr = c(node_ptr);
    }
    else
      return(node_ptr->rigth_node);
  }
  node_ptr->i_data1 = node_height(node_ptr);
  return(node_ptr);
}

int node_height(node *node_ptr){
  int lh,rh;
  if(node_ptr == NULL)
    return(0);
  if(node_ptr->rigth_node == NULL) 
    lh = 0;
  else
    lh = 1 + node_ptr->rigth_node->i_data1;   
  if(node_ptr->left_node == NULL)
     rh = 0; 
  else
    rh = 1 + node_ptr->left_node->i_data1;
  if(lh>rh)
    return(lh);
  return(rh);
  }

node * right_rotate(node *i_node_value){  //Right rotation of a node and its left child.
  node *y;
  y = i_node_value->rigth_node;
  i_node_value->rigth_node = y->left_node;
  y->left_node = i_node_value;
  i_node_value->i_data1=node_height(i_node_value);
  y->i_data1=node_height(y);
  return(y);
} 

node * left_rotate(node *i_node_value){
  node *y;
  y = i_node_value->left_node;
  i_node_value->left_node = y->rigth_node;
  y->rigth_node = i_node_value;
  i_node_value->i_data1 = node_height(i_node_value);
  y->i_data1 = node_height(y);
  return(y);
}

node * a(node *node_ptr){
  g_s_sachin = g_s_sachin+1;
  node_ptr = left_rotate(node_ptr);    
  return(node_ptr);
}

node * b(node *node_ptr){
  node_ptr = right_rotate(node_ptr);
  return(node_ptr);
}

node * c(node *node_ptr){ 
  node_ptr->rigth_node=left_rotate(node_ptr->rigth_node);
  node_ptr = right_rotate(node_ptr);
  return(node_ptr);
}

node * d(node *node_ptr){
  node_ptr->left_node=right_rotate(node_ptr->left_node);
  node_ptr = left_rotate(node_ptr);
  return(node_ptr);
}

int balance_factor(node *node_ptr){ // Calculates the balance factor of a node, 
  int lh,rh;                        //which is the difference between the heights of its left and right subtrees.
  if(node_ptr == NULL)              //lh,rh is height of left or riht node respectively.
    return(0);
  if(node_ptr->rigth_node == NULL)
    lh = 0;
  else
    lh = 1 + node_ptr->rigth_node->i_data1;
  if(node_ptr->left_node == NULL) 
    rh = 0;
  else        
    rh = 1 + node_ptr->left_node->i_data1;
  return(lh - rh);
  }

void postorder_trav(node *node_ptr){
  if(node_ptr != NULL){
    postorder_trav(node_ptr->rigth_node);
    postorder_trav(node_ptr->left_node);        
    printf(" %d(balance_factor=%d)",node_ptr->i_data2,balance_factor(node_ptr));
  }
}

void preorder_trav(node *node_ptr){    
  if(node_ptr != NULL){
    printf(" %d(balance_factor=%d)",node_ptr->i_data2,balance_factor(node_ptr));
    preorder_trav(node_ptr->rigth_node);
    preorder_trav(node_ptr->left_node);
  }
}

void inorder_trav(node *node_ptr){    // it display inorder travesal with sum of leaf nodes
  if(node_ptr != NULL){
    inorder_trav(node_ptr->rigth_node);
    {
      printf(" %d(balance_factor=%d)",node_ptr->i_data2,balance_factor(node_ptr));
      if ((node_ptr->rigth_node == NULL )&(node_ptr->left_node == NULL)) 
        g_sum_leaf_node = g_sum_leaf_node + node_ptr->i_data2; //sum of leaf nodes and store in g_sum_leaf_node
    }
    inorder_trav(node_ptr->left_node); 
  }
}

void koitopasskarde(node *t, int depth){
  if (t != NULL){
    printf(" %d(balance_factor=%d)",t->i_data2,balance_factor(t));
  }      
  if (t != NULL){
    koitopasskarde(t->rigth_node, depth + 1);
    if (depth % 2 == 0)
      koitopasskarde(t->left_node, depth + 1);
  }
}

