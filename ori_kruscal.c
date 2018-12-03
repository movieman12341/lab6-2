//// Kruskal's MST using union-find trees
//
//#include <stdio.h>
//#include <stdlib.h>
//
//int numVertices,numEdges;
//int *parent,*weight,numTrees;
//
//struct edge {
//  int tail,head,weight;
//};
//typedef struct edge edgeType;
//edgeType *edgeTab;
//
//int find(int x)
//// Find root of tree containing x
//{
//int i,j,root;
//
//// Find root
//for (i=x;
//     parent[i]!=i;
//     i=parent[i])
//  ;
//root=i;
//// path compression - make all nodes on path
//// point directly at the root
//for (i=x;
//     parent[i]!=i;
//     j=parent[i],parent[i]=root,i=j)
//  ;
//return root;
//}
//
//void unionFunc(int i,int j)
//// i and j must be roots!
//{
//if (weight[i]>weight[j])
//{
//  parent[j]=i;
//  weight[i]+=weight[j];
//}
//else
//{
//  parent[i]=j;
//  weight[j]+=weight[i];
//}
//numTrees--;
//}
//
//int weightAscending(const void* xin, const void* yin)
//// Used in call to qsort()
//{
//edgeType *x,*y;
//
//x=(edgeType*) xin;
//y=(edgeType*) yin;
//return x->weight - y->weight;
//}
//
//int main()
//{
//int i,MSTweight=0;
//int root1,root2;
//
//scanf("%d %d",&numVertices,&numEdges);
//edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
//parent=(int*) malloc(numVertices*sizeof(int));
//weight=(int*) malloc(numVertices*sizeof(int));
//if (!edgeTab || !parent || !weight)
//{
//  printf("error 2\n");
//  exit(0);
//}
//for (i=0;i<numEdges;i++)
//  scanf("%d %d %d",&edgeTab[i].tail,&edgeTab[i].head,&edgeTab[i].weight);
//for (i=0;i<numVertices;i++)
//{
//  parent[i]=i;
//  weight[i]=1;
//}
//numTrees=numVertices;
//qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);
//for (i=0;i<numEdges;i++)
//{
//  root1=find(edgeTab[i].tail);
//  root2=find(edgeTab[i].head);
//  if (root1==root2)
//    printf("%d %d %d discarded\n",edgeTab[i].tail,edgeTab[i].head,
//      edgeTab[i].weight);
//  else
//  {
//    printf("%d %d %d included\n",edgeTab[i].tail,edgeTab[i].head,
//      edgeTab[i].weight);
//    MSTweight+=edgeTab[i].weight;
//    unionFunc(root1,root2);
//  }
//}
//if (numTrees!=1)
//  printf("MST does not exist\n");
//printf("Sum of weights of spanning edges %d\n",MSTweight);
//free(edgeTab);
//free(parent);
//free(weight);
//}