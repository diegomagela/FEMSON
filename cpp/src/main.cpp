#include <chrono>
#include <iostream>

#include "input.hpp"

int main(int argc, char *argv[]) {

  std::string filename{};

  if (argc > 1) {
    filename = argv[1];
  }

  else {
    filename = "input.femson";
  }

  // example of usage

  input femson(filename);

  // model nodes

  auto const nodes = femson.get_nodes();
  auto const n_nodes = nodes.size();

  for (auto const &node : nodes) {

    auto const id = node.id;
    auto const x_coord = node.x;
    auto const y_coord = node.y;
    auto const z_coord = node.z;

    // fill model node container

  }

  return EXIT_SUCCESS;
}