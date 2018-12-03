// Kruskal's MST using union-find trees

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numVertices, numEdges;
int *parent, numTrees;
int *weight;		//me added. original = int

struct edge {
	int tail, head;
	double weight;			//double changed
};
typedef struct edge edgeType;
edgeType *edgeTab;

int find(int x)
// Find root of tree containing x
{
	int i, j, root;

	// Find root
	for (i = x;
		parent[i] != i;
		i = parent[i])
		;
	root = i;
	// path compression - make all nodes on path
	// point directly at the root
	for (i = x;
		parent[i] != i;
		j = parent[i], parent[i] = root, i = j)
		;
	return root;
}

void unionFunc(int i, int j)
// i and j must be roots!
{
	if (weight[i]>weight[j])
	{
		parent[j] = i;
		weight[i] += weight[j];
	}
	else
	{
		parent[i] = j;
		weight[j] += weight[i];
	}
	numTrees--;
}

double weightAscending(const void* xin, const void* yin)
// Used in call to qsort()
{
	edgeType *x, *y;

	x = (edgeType*)xin; 
	y = (edgeType*)yin;
	return x->weight - y->weight;
}

int main()
{
	int i;
	int root1, root2;
	double MSTweight = 0;	//double changed

	scanf("%d", &numVertices);
	
	numEdges = (numVertices * (numVertices - 1)) / 2;	//compute number of edges

	edgeTab = (edgeType*)malloc(numEdges * sizeof(edgeType));
	parent = (int*)malloc(numVertices * sizeof(int));
	weight = (int*)malloc(numVertices * sizeof(int));			//double changed
	if (!edgeTab || !parent || !weight)
	{
		printf("error 2\n");
		exit(0);
	}

	int j = 0;
	//me changing. input x and y coordinates
	for (i = 0; i < numVertices; i++)
	{
		scanf("%d %d", &edgeTab[i].tail, &edgeTab[i].head);
	}

	int edgeCount = 0;
	//permutate all edges to find all edge connections
	for (i = 0; i < numVertices; i++)
	{
		for (j = i + 1; j < numVertices; j++)
		{
			double finalY = edgeTab[j].head - edgeTab[i].head;
			finalY = pow(finalY, 2);
			double finalX = edgeTab[j].tail - edgeTab[i].tail;
			finalX = pow(finalX, 2);
			double ans = finalX + finalY;
			ans = sqrt(ans);

			if (edgeCount < numEdges) //room in array
			{
				/*weight[weightCount] = ans;
				weightCount++;*/
				edgeTab[edgeCount].weight = ans;
				printf("%lf\n", edgeTab[edgeCount].weight);
				edgeCount++;
			}
			
		}
	}

	for (i = 0; i < numEdges; i++)
	{
		printf("%d\n", edgeTab[i].weight);
	}
		
	for (i = 0; i<numVertices; i++)
	{
		parent[i] = i;
		weight[i] = 1;
	}
	numTrees = numVertices;
	qsort(edgeTab, numEdges, sizeof(edgeType), weightAscending);
	for (i = 0; i<numEdges; i++)
	{
		root1 = find(edgeTab[i].tail);
		root2 = find(edgeTab[i].head);
		if (root1 == root2)
			printf("%d %d %d discarded\n", edgeTab[i].tail, edgeTab[i].head,
				edgeTab[i].weight);
		else
		{
			printf("%d %d %d included\n", edgeTab[i].tail, edgeTab[i].head,
				edgeTab[i].weight);
			MSTweight += edgeTab[i].weight;
			unionFunc(root1, root2);
		}
	}
	if (numTrees != 1)
		printf("MST does not exist\n");
	printf("Sum of weights of spanning edges %d\n", MSTweight);
	free(edgeTab);
	free(parent);
	free(weight);
}