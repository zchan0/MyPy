/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Brian A. Malloy and James F. Power
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "includes/ast.h"

extern int yyparse();
extern void end_scanner();
extern void init_scanner(FILE *);
extern "C" {
  int yydebug;
}

static FILE *open_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open file \"%s\"\n", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

NullNode* NullNode::instance = nullptr;

int main(int argc, char * argv[]) {
  FILE *input_file = stdin;
  if (argc > 1) { /* user-supplied filename */
    input_file = open_file(argv[1]);
  }
  init_scanner(input_file);
  yydebug = 0;  /* Change to 1 if you want debugging */

  try {
    if ( yyparse() == 0 ) {
      fclose(input_file);
      end_scanner();
      PoolOfNodes::getInstance().add(NullNode::getInstance());
      PoolOfNodes::getInstance().drainThePool();
      std::cout << "Program syntactically correct" << std::endl;
      return EXIT_SUCCESS;
    }
  }
  catch ( const std::string& msg ) {
    std::cout << msg << std::endl;
    return EXIT_FAILURE;
  }
  catch ( ... ) {
    std::cout << "Uncaught exception: " << std::endl;
  }
}

