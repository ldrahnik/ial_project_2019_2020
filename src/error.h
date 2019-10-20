/**
 * Name: Adam Láníček, Holden Ďurovič, Honza Novotný, Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 14.11.2018
 * Email: <xlanic04@stud.fit.vutbr.cz>, <xdurov01@stud.fit.vutbr.cz>, <xnovot1e@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File: error.h
 */

#ifndef _error_H_
#define _error_H_

enum ecodes {
  EOK = 0,               	// ok
  EOPT = 1,              	// invalid option (unknown option, unknown option character, required value when is option used is missing)
  EALLOC = 2,            	// allocation problem
  EFILE = 3,             	// problem with opening file (function fseek, ..)
  VERTEX_IS_NOT_VALID = 4, 	// start/end vertex is not found
  EGRAPH = 5,                   // graph has no vertices etc.
  EFILE_FORMAT = 6,		// 2 vertices on one file, delimeter can be space, semicolon, comma
  ETHREAD = 7,	 		// pthread (function pthread_create, ..)
};

#endif
