/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: graph.c
 */

#include "graph.h"

/* init graph */
TGraph initGraph() {
   TGraph graph = {
     .ecode = EOK,
     .vertex_count = 0,
     .edge_count = 0,
     .vertex = NULL,
     .edge = NULL
   };
   return graph;
}

/* from input (file or string) parse line by line and vertex by vertex using strtok_r and create graph structure */
TGraph getGraph(TParams params) {

   // init graph
   TGraph graph = initGraph();

   char* vertex_src;
   char* vertex_dest;

   char *end_line;
   char *end_vertex;
   char *line = strtok_r(params.input, "\n", &end_line);

   while(line != NULL) {

      if(params.show_debug_messages)
         fprintf(stderr, "DEBUG: Line: %s\n", line);

      // add src vertex
      if((vertex_src = strtok_r(line," ", &end_vertex)) == NULL) {
         fprintf (stderr, "Format of input file fails on line: `%s`\n", line);
         graph.ecode = EGRAPH;
	     return graph;
      }
      if((graph.ecode = addVertex(&graph, vertex_src)) != EOK) {
         return graph;
      }

      // add dest vertex
      if((vertex_dest = strtok_r(NULL, " ", &end_vertex)) == NULL) {
         fprintf(stderr, "Format of input file fails on line: `%s`\n", line);
         graph.ecode = EGRAPH;
	 return graph;
      }

      if((graph.ecode = addVertex(&graph, vertex_dest))  != EOK) {
          return graph;
      }

      // connect vertex's
      addEdge(&graph, vertex_src, vertex_dest, params.show_debug_messages);

      line = strtok_r(NULL, "\n", &end_line);
   }

   if(params.show_debug_messages)
      fprintf(stderr, "\nDEBUG: getGraph():structure successfully ended.\n\n");

   return graph;
}

/* means, whether is there any(!) possibility find a hamilton paths or hamilton cirtuit */
int isValidGraph(TGraph* graph, TParams* params) {

    // graph has atleast 3 vertices (base condition)
    if(graph->vertex_count < 3) {
        fprintf (stderr, "Graph validation fails. Add more vertices.\n");
        return 0;
    }

    // every vertex has atleast 1 edge (base condition for path)
    if(strcmp(params->start_vertex, params->end_vertex) != 0) {
        for(int i = 0; i < graph->vertex_count; i++) {
            if(graph->vertex[i]->edge_count == 0) {
                fprintf(stderr, "Graph validation fails. Exist vertex without edges.\n");
                return 0;
            }
        }
    } else { // every vertex has atleast 2 edge (base condition for circle)
        for(int i = 0; i < graph->vertex_count; i++) {
            if(graph->vertex[i]->edge_count < 2) {
                fprintf(stderr, "Graph validation fails. Exist vertex without 2 edges.\n");
                return 0;
            }
        }  

    }

    // every vertex has the same edge's count as 1/2 of total vertices count or more (Dirac condition)
    int is_dirac_condition_fulfilled = 1;
    float graph_half_vertex_count = graph->vertex_count / 2;
    for(int i = 0; i < graph->vertex_count; i++) {
        if(graph->vertex[i]->edge_count < graph_half_vertex_count)
            is_dirac_condition_fulfilled = 0;
    }

    if(params->show_debug_messages)
      fprintf (stderr, "DEBUG: Diract condition: %i.\n", is_dirac_condition_fulfilled);

    // every vertex's not connected each other has sum of edge's more than count of all vertex (Ore condition)
    int is_ore_condition_fulfilled = 1;
    for(int i = 0; i < graph->vertex_count; i++) {
        for(int j = 0; j < graph->vertex_count; j++) {
            if(!isEdgeValid(graph, graph->vertex[i]->name, graph->vertex[j]->name) &&
                graph->vertex[i]->edge_count + graph->vertex[j]->edge_count < graph->vertex_count)
                is_ore_condition_fulfilled = 0;
       }
    }


    if(params->show_debug_messages)
       fprintf (stderr, "DEBUG: Ore condition: %i.\n", is_ore_condition_fulfilled);

    // for every natural number k < ½ u is count of vertex with count of edges smaller than k (Pos condition)
    int is_posova_condition_fulfilled = 1;
    for(int k = 0; k < graph->vertex_count / 2; k++) {
        int vertex_count_with_edge_under_k = 0;
        for(int i = 0; i < graph->vertex_count; i++) {
           if(graph->vertex[i]->edge_count < k)
              vertex_count_with_edge_under_k++;
        }
        if(vertex_count_with_edge_under_k >= k)
           is_posova_condition_fulfilled = 0;
    }

    if(params->show_debug_messages)
       fprintf (stderr, "DEBUG: Posova condition: %i.\n", is_posova_condition_fulfilled);

    return 1;
}

/* init edge */
TEdge* initEdge() {

   // malloc edge
   TEdge* edge = malloc(sizeof(TEdge));
   if(edge == NULL) {
      edge->ecode = EALLOC;
      return edge;
   }

   // init data
   edge->src = NULL;
   edge->dest = NULL;
   edge->ecode = EOK;

   return edge;
}

/* init new edge in graph structure */
int initGraphEdge(TGraph* graph) {

   // realloc one more space for pointer to vertex above
   TEdge** graph_new_edge = realloc(graph->edge, sizeof(TEdge) * (graph->edge_count + 1));
   if(graph_new_edge == NULL) {
      return EALLOC;
   } else {
      graph->edge = graph_new_edge;
   }

   graph->edge[graph->edge_count] = NULL;
   graph->edge_count++;

   return EOK;
}

/* init new edge in vertex structure (linked to graph edge's - for better access and algorithm simplification) */
int initVertexEdge(TVertex* vertex) {

   // realloc one more space for pointer to vertex above
   TEdge** vertex_new_edge = realloc(vertex->edge, sizeof(TEdge) * (vertex->edge_count + 1));
   if(vertex_new_edge == NULL) {
        return EALLOC;
   } else {
      vertex->edge = vertex_new_edge;
   }

   vertex->edge[vertex->edge_count] = NULL;
   vertex->edge_count++;

   return EOK;
}

/* add if not exist */
int addEdge(TGraph* graph, char* vertex_src_name, char* vertex_dest_name, int show_debug_messages) {
   int ecode = EOK;

   if(isVertexValid(graph->vertex, graph->vertex_count, vertex_src_name) && isVertexValid(graph->vertex, graph->vertex_count, vertex_dest_name)) {
      if(isEdgeValid(graph, vertex_src_name, vertex_dest_name) == 0) {

	     // init edge
         TEdge* edge = initEdge();
         if(edge->ecode) {
            return edge->ecode;
         }

	     // link src, dest vertex
         TVertex* vertex_src = getVertex(graph, vertex_src_name);
         TVertex* vertex_dest = getVertex(graph, vertex_dest_name);
 	     edge->src = vertex_src;
 	     edge->dest = vertex_dest;

         // init graph edge
         if((ecode = initGraphEdge(graph)) != EOK) {
            return ecode;
         }
         graph->edge[graph->edge_count - 1] = edge;

         // init vertex_src edge
         if((ecode = initVertexEdge(vertex_src)) != EOK) {
            return ecode;
         }
	     vertex_src->edge[vertex_src->edge_count - 1] = edge;

         // init vertex_dest edge
         if((ecode = initVertexEdge(vertex_dest)) != EOK) {
            return ecode;
         }
	     vertex_dest->edge[vertex_dest->edge_count - 1] = edge;

         if(show_debug_messages) {
            fprintf(stderr, "DEBUG: Edge: %s - %s\n", graph->edge[graph->edge_count - 1]->src->name, graph->edge[graph->edge_count - 1]->dest->name);
            fprintf(stderr, "DEBUG: Edge: %s - %s\n", graph->edge[graph->edge_count - 1]->dest->name, graph->edge[graph->edge_count - 1]->src->name);
	        fprintf(stderr, "DEBUG: Edge count: %i\n", graph->edge_count);
         }
      }
   }

   return EOK;
}

/* init vertex */
TVertex* initVertex(TGraph* graph, char* vertex_name) {

   // malloc vertex
   TVertex* vertex = malloc(sizeof(TVertex));
   if(vertex == NULL) {
     vertex->ecode = EALLOC;
     return vertex;
   }
   vertex->ecode = EOK;

   // init data
   vertex->ecode = EOK;
   vertex->edge = NULL;
   vertex->edge_count = 0;
   vertex->name = malloc(strlen(vertex_name) + 1);
   if(vertex->name == NULL) {
     vertex->ecode = EALLOC;
     return vertex;
   }

   vertex->name[0] = '\0';
   strcpy(vertex->name, vertex_name);

   // realloc one more space for pointer to vertex above
   TVertex** graph_new_vertex = realloc(graph->vertex, sizeof(TVertex) * (graph->vertex_count + 1));
   if(graph_new_vertex == NULL) {
     vertex->ecode = EALLOC;
     return vertex;
   } else {
     graph->vertex = graph_new_vertex;
   }
   graph->vertex[graph->vertex_count] = NULL;
   graph->vertex_count++;

   return vertex;
}   char* vertex_src = NULL;
   char* vertex_dest = NULL;

/* add if not exist */
int addVertex(TGraph* graph, char* vertex_name) {
   if(isVertexValid(graph->vertex, graph->vertex_count, vertex_name) == 0) {

     // init vertex
     TVertex* vertex = initVertex(graph, vertex_name);
     if(vertex->ecode) {
       return vertex->ecode;
     }

     // add vertex
     graph->vertex[graph->vertex_count - 1] = vertex;
   }
   return EOK; // even if u want add the same vertex multiple times, return EOK
}

/* return 1 if edge exist otherwise 0 */
int isEdgeValid(TGraph* graph, char* vertex_src_name, char* vertex_dest_name) {

  for(int i = 0; i < graph->edge_count; i++) {
    if((strcmp(graph->edge[i]->src->name, vertex_src_name) == 0 &&
       strcmp(graph->edge[i]->dest->name, vertex_dest_name) == 0) || 
       (strcmp(graph->edge[i]->src->name, vertex_dest_name) == 0 &&
       strcmp(graph->edge[i]->dest->name, vertex_src_name) == 0)) {
      return 1;	
    }
  }
  return 0;
}

/* call isEdgeValid before this: (getEdge()) IS REQUIRED */
TEdge* getEdge(TGraph* graph, char* vertex_src_name, char* vertex_dest_name) {
  TEdge* edge = NULL;
  for(int i = 0; i < graph->edge_count; i++) {
    if((strcmp(graph->edge[i]->src->name, vertex_src_name) == 0 &&
       strcmp(graph->edge[i]->dest->name, vertex_dest_name) == 0) || 
       (strcmp(graph->edge[i]->src->name, vertex_dest_name) == 0 &&
       strcmp(graph->edge[i]->dest->name, vertex_src_name) == 0)) {
      edge = graph->edge[i];
      break;
    } 
  }
  return edge;
}

/* return 1 if edge exist otherwise 0 */
int isVertexValid(TVertex** vertex, int vertex_count, char* vertex_name) {
  for(int i = 0; i < vertex_count; i++) {
    if(strcmp(vertex[i]->name, vertex_name) == 0)
      return 1;
  }
  return 0;
}

/* call isVertexValid before this: (getVertex()) IS REQUIRED */
TVertex* getVertex(TGraph* graph, char* vertex_name) {
  TVertex* vertex = NULL;
  for(int i = 0; i < graph->vertex_count; i++) {
    if(strcmp(graph->vertex[i]->name, vertex_name) == 0) {
      vertex = graph->vertex[i];
      break;
    }
  }
  return vertex;
}

/* clean graph structures */
void cleanGraph(TGraph graph) {

   // graph edge's
   for(int i = 0; i < graph.edge_count; i++) {
      free(graph.edge[i]);
   }
   free(graph.edge);

   // graph vertex's
   for(int i = 0; i < graph.vertex_count; i++) {
      free(graph.vertex[i]->edge);
      free(graph.vertex[i]->name);
      free(graph.vertex[i]);
   }
   free(graph.vertex);
}
