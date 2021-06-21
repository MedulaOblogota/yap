#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct node
{
    int data;
    struct node* left, *right;
};

int height(struct node* node)
{
  if (NULL == node)
  {
    return 0;
  }
  int lheight = height(node->left);
  int rheight = height(node->right);

  if (lheight > rheight)
  {
    return lheight + 1;
  }
  else
  {
    return rheight + 1;
  }
}

void printSameLevel(struct node*node, int level)
{
  if ((NULL == node) || (level < 0))
  {
    return;
  }
  if (level == 0)
  {
    printf("%d,",node->data);
  }
  if (level > 0)
  {
    printSameLevel(node->left, level -1);
    printSameLevel(node->right, level -1);
  }
}
void printLevelOrder(struct node* node)
{
  int h = height(node);

  //printf("%d\n", node->data);

  for (int i = 0; i < h; ++i)
  {
    printSameLevel(node, i);
  }
}


struct node* newNode(int data)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

void printLevelOrderQueue(struct node *node)
{
  queue_t *queue = QueueCreate();

  if (NULL == node)
  {
    return;
  }

  QueueEnqueue(queue, node);
  while (!QueueIsEmpty(queue))
  {
    struct node *removed = QueuePeek(queue);
    QueueDequeue(queue);

    if (NULL == removed)
    {
      printf("\n");
      removed = QueuePeek(queue);
      QueueDequeue(queue);
    }

    if (NULL != removed)
    {
      printf("%d, ", removed->data);
      if (NULL != removed->left)
      {
        if (NULL != removed->right)
        {
          QueueEnqueue(queue,removed->left);
          QueueEnqueue(queue,removed->right);
          QueueEnqueue(queue, NULL);
        }
        else
        {
          QueueEnqueue(queue,removed->left);
          QueueEnqueue(queue, NULL);
        }
      }
      else
      {
        if (NULL != removed->right)
        {
          QueueEnqueue(queue,removed->right);
          QueueEnqueue(queue, NULL);
        }
      }
    }
  }
}
/* Driver program to test above functions*/
int main()
{
    struct node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(6);
    root->left->left->right = newNode(7);

    printf("height of tree is %d\n", height(root));
    printf("Level Order traversal of binary tree is \n");
    //printLevelOrder(root);
    printLevelOrderQueue(root);
    return 0;
}
