#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<errno.h>
typedef struct edge {
	int to;
	int km;
   struct  edge* next;

}edge;
typedef struct city {

	int id;
	char* cityname;
}city;
typedef struct graph
{
	int citycount;
    edge** adjlist;
	city* cities;



}graph;
int citysayi(const char* cityadi)
{
	int citycount = 0;
	FILE* fp = fopen(cityadi, "r");
	if (fp == NULL) {
		printf("Dosya acilamadi!\n");

		return 0;
	}
	char line[100];

		while (fgets(line, 100, fp) != NULL) {
			citycount++;
		}

		fclose(fp);
		return citycount;
}

graph* create(int citycount)

{
	graph* g = malloc(sizeof(graph));
	edge** adjlist = malloc(citycount * sizeof(edge*));
	city* cities = malloc(citycount * sizeof(city));
	g->citycount = citycount;
	g->adjlist = adjlist;
	g->cities = cities;
	for (int i = 0; i < citycount; i++)
	{
		g->cities[i].id = 0;

		g->cities[i].cityname = NULL;
		g->adjlist[i] = NULL;
	}
	return g;
}
void sehiryukle(graph* g, const char* cityadi)
{
	FILE* fp = fopen(cityadi, "r");
	if (fp == NULL)
	{
		printf("dosyaacilamadi");
		return ;
	}
	int id;
	char cityname[100];

		
	while (fscanf(fp, "%d %99s", &id, cityname) == 2)
	{
		if (id < 0 || id>=g->citycount)
		{
			continue;
		}
		
		g->cities[id].id = id;
		g->cities[id].cityname = malloc(strlen(cityname) + 1);
		strcpy(g->cities[id].cityname,  cityname);

	}
	fclose(fp);

}
	void addge(graph * g, int from, int to, int km)
	{
		// 1) from -> to kenarı
		edge* z = malloc(sizeof(edge));
		z->to = to;
		z->km = km;
		z->next = NULL;

		if (g->adjlist[from] == NULL)
		{
			g->adjlist[from] = z;
		}
		else
		{
			edge* p = g->adjlist[from];
			while (p->next != NULL) p = p->next;
			p->next = z;
		}

		// 2) to -> from kenarı (çift yön)
		edge* b = malloc(sizeof(edge));
		b->to = from;
		b->km = km;
		b->next = NULL;

		if (g->adjlist[to] == NULL)
		{
			g->adjlist[to] = b;
		}
		else
		{
			edge* p2 = g->adjlist[to];
			while (p2->next != NULL) p2 = p2->next;
			p2->next = b;
		}
	}




void yolekle(graph* g, char* yoldosya)
{
	FILE* fp = fopen(yoldosya, "r");
	if (fp == NULL)
	{
		printf("dosyaacilamadi");
		return;
	}
	int to;
	int km;
	int from;
	while (fscanf(fp, "%d %d %d", &from, &to, &km) == 3)
	{
		addge(g, from, to, km);
		

	}
	fclose(fp);
}
void print(graph* g)
{
	for (int i = 0; i < g->citycount; i++)
	{
		printf("%s->", g->cities[i].cityname);

		edge* cur = g->adjlist[i];
		if (cur == NULL)
		{
			printf("yol yok");
		}
		while (cur != NULL)
		{
			printf("%s", g->cities[cur->to].cityname);
			printf("(%d) ", cur->km);
		 	
			cur = cur->next;
			}
		
		printf("\n");

	}

}
void bfs(graph* g, int start)
{
	char visited[8];
	int queque[8];
	int front = 0;
	int rear = 0;
	for (int i = 0; i < 8; i++)
	{
	    visited[i] =0;
	}
	visited[start] = 1;
	queque[rear++] = start;
	while (front < rear)
	{
		int u = queque[front++];
		printf("-%s ", g->cities[u].cityname);
		edge* cur = g->adjlist[u];
		while (cur != NULL)
		{
			int v = cur->to;
			if (visited[v] == 0)
			{
				visited[v] = 1;
				queque[rear++] = v;
			}
			cur=cur->next;

		}

	}
}
int main()
{

	int n = citysayi("cities.txt");
	graph* g = create(n);
	sehiryukle(g, "cities.txt");
	yolekle(g, "yollar.txt");
	print(g); 
	printf("\nBFS\n ");
	bfs(g, 0);

	
}















