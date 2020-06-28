/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: params.c
 */

#include "params.h"

/**
 * Get TParams structure from terminal options
 *
 * @return TParams
 */
TParams getParams(int argc, char *argv[]) {

  // file
  FILE *file;
  long length;
 
  // params
  TParams params = {
    .show_info = 0,
    .show_help_message = 0,
    .show_debug_messages = 0,
    .ecode = EOK,
    .input = NULL,
    .start_vertex = NULL,
    .end_vertex = NULL
  };

  // don't want getopt() writing to stderr
  opterr = 0;

  // getopt
  int c;
  while ((c = getopt(argc, argv, "hids:e:")) != -1) {
    switch (c) {
      case 'i':
        if(params.show_info) {
	      fprintf(stderr, "Option -i is already used.\n");
          params.ecode = EOPT;
          return params;
	    }
        params.show_info = 1;
        break;
      case 'h':
        if(params.show_help_message) {
	      fprintf(stderr, "Option -h is already used.\n");
          params.ecode = EOPT;
          return params;
	    }
        params.show_help_message = 1;
        return params;
      case 'd':
        if(params.show_debug_messages) {
	      fprintf(stderr, "Option -d is already used.\n");
          params.ecode = EOPT;
          return params;
	    }
        params.show_debug_messages = 1;
        break;
      case 's':
        if(params.start_vertex != NULL) {
	      fprintf(stderr, "Option -s is already used.\n");
          params.ecode = EOPT;
          return params;
	    }
	    if(strcmp(optarg, "") == 0) {
	      fprintf(stderr, "Remove option -s, value can not be empty.\n");
          params.ecode = EOPT;
          return params;
	    }
	    params.start_vertex = malloc(strlen(optarg) + 1);
	    if(params.start_vertex == NULL) {
          params.ecode = EALLOC;
	      fprintf (stderr, "Allocation fails.\n");
          return params;
        }

        strcpy(params.start_vertex, optarg);
        params.start_vertex[strlen(optarg)] = '\0';
        break;
      case 'e':
        if(params.end_vertex != NULL) {
	      fprintf(stderr, "Option -e is already used.\n");
          params.ecode = EOPT;
          return params;
	    }
	    if(strcmp(optarg, "") == 0) {
	      fprintf(stderr, "Remove option -e, value can not be empty.\n");
          params.ecode = EOPT;
          return params;
	    }
	    params.end_vertex = malloc(strlen(optarg) + 1);
	    if(params.end_vertex == NULL) {
	      params.ecode = EALLOC;
	      fprintf (stderr, "Allocation fails.\n");
            return params;
      	  }
          strcpy(params.end_vertex, optarg);
          params.end_vertex[strlen(optarg)] = '\0';
          break;
      case '?':
        if(optopt == 's' || optopt == 'e') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else if(isprint (optopt)) {
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        params.ecode = EOPT;
        return params;
      default:
        fprintf(stderr, "Options error.\n");
        params.ecode = EOPT;
        return params;
    }
  }

  // catch this case: ./hpac
  if(argc == 1) {
    if(params.show_help_message) {
	   fprintf(stderr, "Option -h is already used.\n");
       params.ecode = EOPT;
       return params;
	 }
     params.show_help_message = 1;
     return params;
  // for example catch this case: ./hpac "A B" -s f ggg
  } else if(argv[optind + 1] != NULL) {
    fprintf(stderr, "Option error. Please use optional options before non-options.\n");
    params.ecode = EOPT;
    return params;
  }

  // file is required
  if(argv[optind] == NULL) {
    fprintf(stderr, "File is missing.\n");
    params.ecode = EOPT;
    return params;
  }

  // open file
  file = fopen(argv[optind],"rb");
  if(file != NULL) {
    if(fseek(file, 0, SEEK_END) != 0) {
      params.ecode = EFILE;
      return params;
    }
    length = ftell(file);
    if(length == -1) {
      params.ecode = EFILE;
      return params;
    }
    if(fseek(file, 0, SEEK_SET) != 0) {
      params.ecode = EFILE;
      return params;
    }
    params.input = malloc(length + 1);
    if(params.input == NULL) {
      params.ecode = EALLOC;
      return params;
    }
    if(params.input) {
      fread(params.input, 1, length, file);
      params.input[length] = '\0';
    }
    fclose(file);
  } else { // its not a file, its a raw string
      params.input = malloc(strlen(argv[optind]) + 1);
      if(params.input == NULL) {
        params.ecode = EALLOC;
	    fprintf (stderr, "Allocation fails.\n");
        return params;
      }
      strcpy(params.input, argv[optind]);
  }
 
  return params;
}

void cleanParams(TParams params) {
   free(params.input);
   free(params.start_vertex);
   free(params.end_vertex);
}
