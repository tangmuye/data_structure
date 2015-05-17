/*************************************************************************
	> Author: Yves
	> E-mail: ty@msn.cn
	> File Name: BiTreeNew.cpp
	> Description: ...
	> Created  Time: 2015-05-17. 15:51:24
	> Modified Time: 2015-05-17. 15:51:24
 ************************************************************************/

#include<stack>
#include<cstdlib>
#include<stdio.h>
#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct tagBiTreeNode
{
    ElemType data;
    struct tagBiTreeNode* leftChild;
    struct tagBiTreeNode* rightChild;
}BiTreeNode, *pBiTreeNode;//指向BiTNode的指针

static void CreatBiTree(pBiTreeNode *p);//创建二叉树
static void VisitTree(pBiTreeNode p);
//前序递归遍历
static void PreOrderRecursiveTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));
//前序非递归遍历
static void PreRecursiveTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));
//中序递归遍历
static void InOrderRecursiveTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));
//中序非递归遍历
static void InOrdeTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));
//后序递归遍历
static void PostOrderRecursiveTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));
//后序非递归遍历
static void PostOrderTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level));

static void CreatBiTree(pBiTreeNode *p)
{
    /*Here we creat the tree in preorder, so the input 
    sequences must comply with the preorder*/
    ElemType c;
    cin>>c;
    if(c != '#')
    {
		*p = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    	(*p)->data = c;
        CreatBiTree(&(*p)->leftChild);
        CreatBiTree(&(*p)->rightChild);
    }else
    {
		*p = NULL;
		return;
    }
}

static void VisitTree(pBiTreeNode p, const int level)
{
	cout<<p->data<<" is on the level "<<level<<"."<<endl;
}

static void PreOrderRecursiveTraversal(pBiTreeNode p, int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	if(p == NULL)
	{
		return;
	}
	VisitTree(p, level);
	PreOrderRecursiveTraversal(p->leftChild, level + 1, VisitTree);
	PreOrderRecursiveTraversal(p->rightChild, level + 1, VisitTree);
}
static void PreRecursiveTraversal(pBiTreeNode p,int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	stack<pBiTreeNode> s;
	if(p == NULL)
	{
		return;
	}
	while(!s.empty() || p != NULL)
	{
		while(p != NULL)
		{
			VisitTree(p, level);
			s.push(p);
			p = p->leftChild;
		}if(!s.empty())
		{
			p = s.top;
			s.pop();
			p = p->right;	
		}
	}
}
static void InOrderRecursiveTraversal(pBiTreeNode p,int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	if(p == NULL)
	{
		return;
	}
	InOrderRecursiveTraversal(p->leftChild, level + 1, VisitTree);
	VisitTree(p, level);
	InOrderRecursiveTraversal(p->rightChild, level + 1, VisitTree);
}
static void InOrdeTraversal(pBiTreeNode p,int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	
}
static void PostOrderRecursiveTraversal(pBiTreeNode p,int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	if(p == NULL)
	{
		return;
	}
	PostOrderRecursiveTraversal(p->leftChild, level + 1, VisitTree);
	PostOrderRecursiveTraversal(p->rightChild, level + 1, VisitTree);
	VisitTree(p, level);
}
static void PostOrderTraversal(pBiTreeNode p,int level, void (*VisitTree)(pBiTreeNode p, const int level))
{
	stack<pBiTreeNode> s;
	pBiTreeNode pCurrentNode;
	pBiTreeNode pPrecedingNode = NULL;
	s.push(p);
	while(!s.empty())
	{
		pCurrentNode = s.top();
		/*There is two cases:
		* 1, the lefechild and the rightchild is all NULL, meaning it is a leaf node,so we can visit it directly.
		* 2, the preceding node is not NULL,in addtion, it is the rightchild or the leftchild of the curretn node.
		* Notice because of our order of pushing nodes into stack, it is sure that the two nodes(leftchild,rightchild)
		* have accessed yet if one of conditions satisfies: 
		*          pPrecedingNode == pCurrentNode->leftChild  or
		*          pPrecedingNode == pCurrentNode->rightChild))
		* of course, pPrecedingNode != NULL must be satisfied.
		*/
		if((pCurrentNode->leftChild == NULL && pCurrentNode->rightChild == NULL)
			|| (pPrecedingNode != NULL && (pPrecedingNode == pCurrentNode->leftChild 
					|| pPrecedingNode == pCurrentNode->rightChild)))
		{
			VisitTree(pCurrentNode, level);
			s.pop();
			pPrecedingNode = pCurrentNode;
		}else
		{
			if(pCurrentNode->rightChild != NULL)
			{
				s.push(pCurrentNode->rightChild);
			}
			if(pCurrentNode->leftChild != NULL)
			{
				s.push(pCurrentNode->leftChild);
			}
		}
	}
}


int main(void)
{
    pBiTreeNode root;
    cout<<"Please input the node of the tree(preorder sequence):  "<<endl;
    CreatBiTree(&root);
    cout<<endl;

    cout<<"Traverse the tree in preorder:  "<<endl;
    PreOrderRecursiveTraversal(root,1,&VisitTree);
    cout<<endl;
    
    cout<<"Traverse the tree in preorder(non-recursive):  "<<endl;
    PreRecursiveTraversal(root, 1, &VisitTree);
    cout<<endl;
    
    cout<<"Traverse the tree in inorder:  "<<endl;
    InOrderRecursiveTraversal(root, 1, &VisitTree);
    cout<<endl;
    
    /*cout<<"Traverse the tree in inorder(non-recursive):  "<<endl;
    InOrderTraversal(root, 1, &VisitTree);
    cout<<endl;
*/
    cout<<"Traverse the tree in posteorder:  "<<endl;
    PostOrderRecursiveTraversal(root, 1, &VisitTree);
    cout<<endl;
    
    cout<<"Traverse the tree in postorder(non-recursive):  "<<endl;
    PostOrderTraversal(root, 1, &VisitTree);
    cout<<endl;
    
    return 0;
}
