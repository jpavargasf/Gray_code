//Autor: João Paulo Vargas da Fonseca
//Date: 25/03/2022
//
//Description:  This code uses a binary tree to find a n-bit gray code while also
//              building m-bit gray code, when m<n. Or you can see as building a
//              binary tree, where at depth n there is a n-bit gray code if read
//              from left to right.
//
//How does this work?
//              1.Depth n will always have n bits
//              2.Difference from depth n and n+1 is the less significant bit, whereas
//              n+1 at the left will receive bit 0 and the right 1.
//              3.If a node receives the bit 1, the process described in 2 will be
//              reversed (left receives 1 and right 0) for all nodes generated from
//              this, but this can be reversed again for the next nodes, coming back
//              to the original process
//              4.The n-bit gray code will be at depth n, if read left to right
//
//It is possible to use less memory (each node store 1 bit), but it will require another
//print method
//
//It is possible to store the code into an array, just use a global variable

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct node{
    uint8_t *value;
    struct node *left;
    struct node *right;
};

//depth and depth_limit are always positive for simplification
//reverse assume values -1 (to reverse) and 1 (not reverse)
struct node *rec_gc(struct node *parent,int8_t reverse,uint8_t bit_to_add,uint32_t depth,uint32_t depth_limit){
    struct node *node;
    node = (struct node*)malloc(sizeof(struct node));
    //node->value = NULL
    if(depth!=0){
        uint32_t i = 0;
        node->value = (uint8_t*)malloc((1+depth)*sizeof(uint8_t));

        //copy its parents contents
        while(i<(depth-1)){
            node->value[i] = parent->value[i];
            i++;
        }

        //add the new bit
        node->value[i++] = bit_to_add;
        node->value[i] = '\0';
    }else{
        node->value = NULL;
    }
    if(depth!=depth_limit){
        //index 0 for left and index 1 for right
        uint8_t index_left = 0;

        uint8_t bit_lr[2];

        int8_t reverse_lr[2];

        bit_lr[0] = '0';
        bit_lr[1] = '1';

        reverse_lr[0] = reverse;
        reverse_lr[1] = -reverse;

        if(reverse == -1){
            index_left = 1;
        }

        node->left = rec_gc(node,reverse_lr[index_left],bit_lr[index_left],depth + 1,depth_limit);
        node->right = rec_gc(node,reverse_lr[1-index_left],bit_lr[1-index_left],depth + 1,depth_limit);
    }else{
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct node *gray_code(uint32_t n_bits){
    return rec_gc(NULL,1,0,0,n_bits);
};

void rec_print_gc(struct node *gc,uint32_t depth,uint32_t depth_limit){
    if(depth==depth_limit){
        printf("%s\n",(char*)gc->value);
    }else{
        if(gc->left==NULL||gc->right==NULL) return;//tree not built correctly
        rec_print_gc(gc->left,depth+1,depth_limit);
        rec_print_gc(gc->right,depth+1,depth_limit);
    }
}

//to print gray code is the same of any binary search tree
void print_gray_code(struct node *graycode_root,uint32_t n_bits){
    if(graycode_root==NULL||n_bits==0)  return;
    rec_print_gc(graycode_root,0,n_bits);
}

void free_tree(struct node *node){
    if(node==NULL)  return;
    free_tree(node->left);
    free_tree(node->right);
    free(node->value);
    free(node);
    node = NULL;
}

int main(){
    uint32_t n_bits;
    printf("N-bit gray code generation.\nN = ");
    scanf("%d",&n_bits);
    struct node *gc = gray_code(n_bits);
    print_gray_code(gc,n_bits);
    free_tree(gc);
}
