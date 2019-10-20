/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: graph.h
 */

#ifndef _graph_H_
#define _graph_H_

#include "error.h"
#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define LINE 2048

typedef struct vertex {
  int edge_count;
  char* name;
  struct edge** edge;
  int ecode;
} TVertex;

typedef struct edge {
  TVertex* src;
  TVertex* dest;
  int ecode;
} TEdge;

typedef struct graph {
  int vertex_count;
  int edge_count;
  struct vertex** vertex;
  struct edge** edge;
  int ecode;
} TGraph;

char *sgets(char * str, int num, char **input);
TGraph initGraph();
TVertex* initVertex(TGraph* graph, char* vertex_name);
TEdge* initEdge();
int initVertexEdge(TVertex* vertex);
TGraph getGraph(TParams params);
int addVertex(TGraph* graph, char* vertex_name);
int addEdge(TGraph* graph, char* vertex_src_name, char* vertex_dest_name);
TEdge* getEdge(TGraph* graph, char* vertex_src, char* vertex_dest);
TVertex* getVertex(TGraph* graph, char* vertex_name);
int isVertexValid(TVertex** vertex, int vertex_count, char* vertex_name);
int isEdgeValid(TGraph* graph, char* vertex_src_name, char* vertex_dest_name);
void cleanGraph(TGraph graph);
int isValidGraph(TGraph* graph, TParams* params);

#endif
