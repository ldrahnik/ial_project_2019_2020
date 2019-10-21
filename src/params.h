/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: params.h
 */

#ifndef _params_H_
#define _params_H_

#include "string.h"

#include "error.h"

typedef struct params {
  int show_info; // option i
  int show_debug_messages; // option d
  int show_help_message; // option h
  int ecode; // error code
  char* start_vertex; // command option s
  char* end_vertex; // command option e
  char* input; // graph
} TParams;

TParams getParams(int argc, char *argv[]);
void cleanParams(TParams params);

#endif
