/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: hpac.h
 */

#ifndef _hpac_H_
#define _hpac_H_

#include "params.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <pthread.h>
#include <signal.h>
#include <semaphore.h> 

#define MAXTHREADS 10000

/* arguments for pthread for algorithm */
typedef struct pthread_args {
  struct params* params;
  struct graph* graph;
  TVertex** vertex_out;
  int vertex_out_count;
} Tpthread_args;

void cleanAll(TParams params, TGraph graph);
int main(int argc, char *argv[]);
int algorithm(TParams* params, TGraph* graph, int vertex_out_count, TVertex** vertex_out);
void cleanThreadArg(Tpthread_args* threadarg);
void cleanThreadArgs(Tpthread_args** threadargs, int thread_counts);

#endif
