#include "node.h"
#include "literal.h"


PoolOfNodes& PoolOfNodes::getInstance() {
  static PoolOfNodes pool;
  return pool;
}

void PoolOfNodes::drainThePool() {
  for ( const Node* node : nodePool ) {
    if (node != nullptr) {
      delete node;
    }
  }
}

