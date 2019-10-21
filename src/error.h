/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
 * Date: 20.10.2019
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: error.h
 */

#ifndef _error_H_
#define _error_H_

enum ecodes {
  EOK = 0, // ok
  EOPT = 1, // invalid option (unknown option, unknown option character, required value when is option used is missing)
  EALLOC = 2, // allocation problem
  EFILE = 3, // problem with opening file (function fseek, ..)
  VERTEX_IS_NOT_VALID = 4, // start/end vertex is not found
  EGRAPH = 5, // graph has no vertices etc.
  EFILE_FORMAT = 6, // for example 2 vertices on a line etc. (delimeter can be space, semicolon, comma)
};

#endif
