/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: hpac.c
 *
 * Assignment:
 *
 * Cestu v grafu, ve které se vyskytuje každý vrchol právě jednou, nazýváme Hamiltonovou cestou. Má-li tato cesta počátek a konec v jednom jediném vrcholu, pak se jedná o Hamiltonův cyklus v grafu. 
 * Vytvořte program pro hledání Hamiltonovy cesty (pro dva zadané vrcholy) a Hamiltonova cyklu v neorientovaném grafu. 
 * Pokud existuje více řešení, nalezněte všechna. Výsledky prezentujte vhodným způsobem. Součástí projektu bude načítání grafů ze souboru a vhodné testovací grafy. V dokumentaci uveďte teoretickou složitost úlohy a porovnejte ji s
 * experimentálními výsledky.
 *
 * Description:
 *
 * This file contains start function called main() which calls methods getParams() from modul Params, method getGraph() from modul Graph etc. 
 * Also there is finalized params setting start_vertex, end_vertex (at this moment because when are unset params start_vertex, end_vertex is
 * used first graph vertex for them)
 * After this is called main algorithm placed in method algorithm() using recursion so calling itself for next each vertex on the way.
 * When last algorithm() is ended program end with EOK or given error code.
 */

#include "hpac.h"

/* count of algorithm() calls */
int algorithm_calls_count = 0;

/* results */
int results_hamilton_path_count = 0;
int results_hamilton_cycle_count = 0;

const char *HELP_MSG = {
  "HPAC - Hamilton paths and cirtuits\n\n"	
  "Example of usage:\n\n"
  "./hpac [-s <start>] [-e <end>] [-d] [-i] <inline graph|file contains graph>\n\n"
  "Options:\n"
  "-s start vertex [ OPTIONAL ], default is first vertex in file\n"
  "-e end vertex [ OPTIONAL ], default is first vertex in file\n"
  "-d debug [ OPTIONAL ], show debug messages\n"
  "-i info [ OPTIONAL ], show info about executed algorithm\n"
};

/* clean params structures and graph structures */
void cleanAll(TParams params, TGraph graph) {
   cleanParams(params);
   cleanGraph(graph);
}

/* main */
int main(int argc, char *argv[]) {
  int ecode = EOK;

  // get params
  TParams params = getParams(argc, argv);
  if(params.ecode != EOK) {
    cleanParams(params);
    return params.ecode;
  }

  // help message
  if(params.show_help_message) {
    printf("%s", HELP_MSG);
    cleanParams(params);
    return ecode;
  }

  if(params.show_debug_messages) {
    fprintf(stderr, "\nDEBUG: getParams() successfully ended.\n\n");

    fprintf(stderr, "DEBUG: Input: \"%s\".\n", params.input);
    fprintf(stderr, "DEBUG: Start vertex: \"%s\".\n", params.start_vertex);
    fprintf(stderr, "DEBUG: End vertex: \"%s\".\n", params.end_vertex);
    fprintf(stderr, "DEBUG: Show help message: \"%d\".\n\n", params.show_help_message);
  }

  // get graph
  TGraph graph = getGraph(params);
  if(graph.ecode != EOK) {
    cleanAll(params, graph);
    return params.ecode;
  }

  if(params.show_debug_messages)
    fprintf(stderr, "\nDEBUG: getGraph() successfully ended.\n\n");

  // default value start_vertex
  if(params.start_vertex == NULL) {
    params.start_vertex = malloc(strlen(graph.vertex[0]->name) + 1);
    if(params.start_vertex == NULL) {
       cleanAll(params, graph);
       return EALLOC;
    }
    strcpy(params.start_vertex, graph.vertex[0]->name);
  } else {
    if(!isVertexValid(graph.vertex, graph.vertex_count, params.start_vertex)) {
       fprintf(stderr, "Start vertex value: '%s' is not valid vertex.\n", params.start_vertex);
       cleanAll(params, graph);
       return EOPT;
    }
  }

  // default value end_vertex
  if(params.end_vertex == NULL) {
    params.end_vertex = malloc(strlen(graph.vertex[0]->name) + 1);
    if(params.end_vertex == NULL) {
       cleanAll(params, graph);
       return EALLOC;
    }
    strcpy(params.end_vertex, graph.vertex[0]->name);
  } else {
    if(!isVertexValid(graph.vertex, graph.vertex_count, params.end_vertex)) {
       fprintf(stderr, "End vertex value: '%s' is not valid vertex.\n", params.end_vertex);
       cleanAll(params, graph);
       return EOPT;
    }
  }

  // validate graph
  if(!isValidGraph(&graph, &params)) {
    cleanAll(params, graph);
    return EGRAPH;
  }

  if(params.show_debug_messages) {
    fprintf(stderr, "\nDEBUG: getGraph():validation successfully ended.\n\n");

    fprintf(stderr, "DEBUG: Start vertex: \"%s\".\n", params.start_vertex);
    fprintf(stderr, "DEBUG: End vertex: \"%s\".\n", params.end_vertex);
    fprintf(stderr, "DEBUG: Start graph vertex: \"%s\".\n", graph.vertex[0]->name);
    fprintf(stderr, "DEBUG: End graph vertex: \"%s\".\n", graph.vertex[graph.vertex_count - 1]->name);
    fprintf(stderr, "DEBUG: Graph vertex count: \"%i\".\n", graph.vertex_count);
    for(int i = 0; i < graph.vertex_count; i++) {
      fprintf(stderr, "DEBUG: Vertex: \"%s\".\n", graph.vertex[i]->name);
      fprintf(stderr, "DEBUG: Vertex edge count: \"%i\".\n", graph.vertex[i]->edge_count);
      for(int j = 0; j < graph.vertex[i]->edge_count; j++) {
        if(strcmp(graph.vertex[i]->edge[j]->dest->name, graph.vertex[i]->name) == 0) {
          fprintf(stderr, "DEBUG: Vertex edge: \"%s - \"%s.\n", graph.vertex[i]->edge[j]->dest->name, graph.vertex[i]->edge[j]->src->name);
        } else {
          fprintf(stderr, "DEBUG: Vertex edge: \"%s - \"%s.\n", graph.vertex[i]->edge[j]->src->name, graph.vertex[i]->edge[j]->dest->name);
        }
      }
    }
    fprintf(stderr, "DEBUG: Graph edge count: \"%i\".\n", graph.edge_count);
    for(int j = 0; j < graph.edge_count; j++) {
      fprintf(stderr, "DEBUG: Edge: \"%s - \"%s.\n", graph.edge[j]->src->name, graph.edge[j]->dest->name);
    }
  }

  // main algorithm

  // arguments
  TVertex** vertex_out = malloc(sizeof(TVertex));
  vertex_out[0] = getVertex(&graph, params.start_vertex);

  // run algorithm
  if(params.show_debug_messages)
    fprintf(stderr, "\nDEBUG: main algorithm (brutal force) successfully started.\n\n");

  algorithm(&params, &graph, 1, vertex_out);

  // results
  // cycle
  if(strcmp(params.start_vertex, params.end_vertex) == 0) {
    printf("Results: %i\n", results_hamilton_cycle_count);
  } 
  // path
  else {
    printf("Results: %i\n", results_hamilton_path_count);
  }

  // statistics
  if(params.show_info)
     fprintf(stderr, "\nSTATISTICS: method algorithm() called: %i\n", algorithm_calls_count);

  if(params.show_debug_messages)
    fprintf(stderr, "\nDEBUG: main algorithm successfully ended.\n\n");

  // clean
  cleanAll(params, graph);

  if(params.show_debug_messages)
    fprintf(stderr, "\nDEBUG: clean*() successfuly ended.\n\n");

  return ecode;
}

/* 
 * algorithm - finding Hamilton path and circle using brute force method
 * vertex_out - is array of vertices contains already visited vertices 
*/
int algorithm(TParams* params, TGraph* graph, int vertex_out_count, TVertex** vertex_out) {

  algorithm_calls_count++;

  // from previous node 
  TVertex* vertex = vertex_out[vertex_out_count - 1];

  if(params->show_debug_messages)
    fprintf(stderr, "DEBUG: Vertex %s. Init.\n", vertex->name);

  // loop every vertex connected "from" vertex you have
  for(int i = 0; i < vertex->edge_count; i++) {

    // next vertex
    TVertex* vertex_next = NULL;
    if(strcmp(vertex->edge[i]->dest->name, vertex->name) == 0) {
      vertex_next = vertex->edge[i]->src;
    } else {
      vertex_next = vertex->edge[i]->dest;
    }

    if(params->show_debug_messages)
       fprintf(stderr, "DEBUG: Vertex %s. Params start_vertex: %s, Params end_vertex: %s, Vertex %s, Next vertex %s, End vertex %s, Graph vertex count %i, Vertex_out_count %i\n", vertex->name, params->start_vertex, params->end_vertex, vertex->name, vertex_next->name, params->end_vertex, graph->vertex_count, vertex_out_count);

    // can not go into end_vertex if it's not a last one (!)
    if(strcmp(vertex_next->name, params->end_vertex) == 0 && ((graph->vertex_count != vertex_out_count && strcmp(params->start_vertex, params->end_vertex) == 0) || (graph->vertex_count != vertex_out_count + 1 && strcmp(params->start_vertex, params->end_vertex) != 0))) {
       continue;
    }

    // is next one last one? if its a cycle, end is already counted DIFFERENT VS path is not counted (thats why +1 for non cycle, means not the same start and end vertex) 
    if(strcmp(vertex_next->name, params->end_vertex) == 0 && ((graph->vertex_count == vertex_out_count && strcmp(params->start_vertex, params->end_vertex) == 0) || (graph->vertex_count == vertex_out_count + 1 && strcmp(params->start_vertex, params->end_vertex) != 0))) {

      // cycle
      if(strcmp(params->start_vertex, params->end_vertex) == 0) {
         results_hamilton_cycle_count++;

         if(params->show_debug_messages)
            fprintf(stderr, "DEBUG: Vertex %s. Hamilton cycle found.\n", vertex->name);

         for(int j = 0; j < graph->vertex_count - 1; j++)
            printf("%s %s\n", vertex_out[j]->name, vertex_out[j + 1]->name);

         printf("%s %s\n", vertex_out[graph->vertex_count - 1]->name, params->end_vertex);
         printf("\n");
      }

      // path 
      else { 
         results_hamilton_path_count++;

         if(params->show_debug_messages)
            fprintf(stderr, "DEBUG: Vertex %s. Hamilton path found.\n", vertex->name);

         for(int j = 0; j < graph->vertex_count - 2; j++)
            printf("%s %s\n", vertex_out[j]->name, vertex_out[j + 1]->name);

         printf("%s %s\n", vertex_out[graph->vertex_count - 2]->name, params->end_vertex);
         printf("\n");
      }

      break;
    }

    // next one is valid? can i go there? or it will be twice or previous vertex? (mean i can not)
    if(isVertexValid(vertex_out, vertex_out_count, vertex_next->name) == 0)  {

       // arguments
       TVertex** vertex_out_next = malloc(sizeof(TVertex) * vertex_out_count + 1);
       if(vertex_out_next == NULL) {
          return EALLOC;
       }

       for(int i = 0; i < vertex_out_count; i++) {
          vertex_out_next[i] = vertex_out[i];

          if(params->show_debug_messages)
             fprintf(stderr, "DEBUG: Vertex %s. Init vertex_out_next %i : %s.\n", vertex->name, i, vertex_out_next[i]->name);
       }

       int vertex_out_count_next = vertex_out_count + 1;
       vertex_out_next[vertex_out_count] = vertex_next;

       if(params->show_debug_messages)
          fprintf(stderr, "DEBUG: Vertex %s. Next vertex: %s. Run child.\n", vertex->name, vertex_next->name);

       algorithm(params, graph, vertex_out_count_next, vertex_out_next);
    }
  }

  if(params->show_debug_messages)
     fprintf(stderr, "DEBUG: Vertex %s. End.\n", vertex->name);

  // clean
  free(vertex_out);

  return EOK;
} 
