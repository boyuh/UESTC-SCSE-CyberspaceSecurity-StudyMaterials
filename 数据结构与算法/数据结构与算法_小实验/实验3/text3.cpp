#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
typedef struct BTREE 
{ 
  char data; 
  struct BTREE *left; 
  struct BTREE *right; 
}BTNode,*BTree;

void PostOrder(BTNode* bt);
int search(char s[],int l,int h,char t);
BTNode* Create(char pOrder[],int *i,char iOrder[],int low,int high);

int main(){
	int t;
    int p;
    int k;
    char preOrder[100], inOrder[100];
    cin >> preOrder >> inOrder;
    p = strlen(preOrder);
    t = strlen(inOrder);
    if (t != p) {
        cout << "error" << endl; return 0;
	}
    for (int i = 0; i < t; i++)
    {
        for (k = 0; k < t; k++)
        {
            if (preOrder[i] == inOrder[k])break;
        }
        if (k == t) { cout << "error" << endl; return 0;}
    }
	int n=p;
	int i=0;
	BTNode* bt=new BTNode;
	bt=Create(preOrder,&i,inOrder,0,n-1);
	PostOrder(bt);
	return 0;
}

//后序遍历输出
void PostOrder(BTNode* bt){
	if (bt == NULL) return;
	PostOrder(bt->left);
	PostOrder(bt->right);
	cout<<bt->data;
	
} 

//查找
int search(char s[],int l,int h,char t){
	int res=-1,m;
	for(m=l;m<=h;m++){
		if (s[m]==t){
			res=m+1;
			break;
		}
	}
	return res-1;
}

//建立二叉树 
BTNode* Create(char *pOrder,int* i,char *iOrder,int low,int high){
	if(low==high){
		BTNode* root=new BTNode;
		root->data=iOrder[low];
		root->left=NULL;
		root->right=NULL;
		(*i)++;
		return root;
	}else if(low<high){
		BTNode* root=new BTNode;
		char x=pOrder[*i];
		(*i)++;
		int pos=search(iOrder,low,high,x);
		if(pos!=-1){
			root->data=x;
			root->left=Create(pOrder,i,iOrder,low,pos-1);
			root->right=Create(pOrder,i,iOrder,pos+1,high);	
			return root;
		}
	}else{
		return NULL;
	}
}
