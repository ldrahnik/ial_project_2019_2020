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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h> // isprint

#include "error.h"

typedef struct params {
  uint32_t show_info :1; // option i
  uint32_t show_debug_messages :1; // option d
  uint32_t show_help_message :1; // option h
  uint32_t ecode :3; // error code
  char* start_vertex; // command option s
  char* end_vertex; // command option e
  char* input; // graph
} TParams;

TParams getParams(int argc, char *argv[]);
void cleanParams(TParams params);

#endif
