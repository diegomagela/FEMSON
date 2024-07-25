#include "input.hpp"

#include <filesystem>
#include <fstream>

input::input(std::string const &filename) : _filename(filename) {
  std::fstream const file(_filename);

  if (not file.is_open()) {
    throw std::runtime_error("cannot open the file \"" + _filename + "\".");
  }

  std::filesystem::path const file_path{_filename};

  // DEBUG
  _name = file_path.stem().generic_string();

  if (file_path.extension() == ".femson") {
    read_femson();
  }

  else {
    throw std::runtime_error("file extension not supported.");
  }
}

void input::read_femson() {
  std::ifstream input(_filename);
  nlohmann::json const j = nlohmann::json::parse(input);

  // Fill fem objects

  _nodes = j.at("nodes");
  _nsets = j.at("nsets");
  _elements = j.at("elements");
  _elsets = j.at("elsets");
  _sections = j.at("sections");
  _materials = j.at("materials");
  _steps = j.at("steps");
}
