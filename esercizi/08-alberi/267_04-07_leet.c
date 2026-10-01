//
//  main.c
//  leet
//
//  Created by Francesco Roscio Ricon on 04/07/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

typedef struct TreeNode* Tree;

void funzione(int *max, Tree t, int sum);
void intermedia(Tree t, int *m);
void scorri(Tree t, int *val);

int maxPathSum(struct TreeNode* root) {
    int massimo=INT_MIN;
    scorri(root, &massimo);
    return massimo;
}
void scorri(Tree t, int *val)
    {
        if(t==NULL)
            return;
        int p=INT_MIN;
        intermedia(t, &p);
        if(p>*val)
            *val=p;
    scorri(t->left, val);
    scorri(t->right, val);
    }


void intermedia(Tree t, int *m)
    {
    int *sx=0;
    int *dx=0;
    funzione(sx, t->left, 0);
    funzione(dx, t->right, 0);
    if(*sx+(*dx)>*m)
        *m=(*sx)+(*dx);
    }


void funzione(int *max, Tree t, int sum)
    {
        if(t==NULL)
            return;
        int val=sum;
        val=val+t->val;
        if(val>sum)
            sum=val;
        if(sum>*max)
            *max=sum;
    funzione(max, t->left, sum);
    funzione(max, t->right, sum);
    }
