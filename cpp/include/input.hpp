#ifndef input_hpp
#define input_hpp

#include "femson.hpp"
#include <string>

class input {
public:
  input(std::string const &filename);

  auto const &get_filename() const { return _filename; }
  auto const &get_name() const { return _name; }
  auto const &get_nodes() const { return _nodes; }
  auto const &get_nsets() const { return _nsets; }
  auto const &get_elements() const { return _elements; }
  auto const &get_elsets() const { return _elsets; }
  auto const &get_sections() const { return _sections; }
  auto const &get_materials() const { return _materials; }
  auto const &get_steps() const { return _steps; }

private:
  void read_femson();

private:
  using nodes = std::vector<fem_objects::node>;
  using nsets = std::vector<fem_objects::nset>;
  using elements = std::vector<fem_objects::element>;
  using elsets = std::vector<fem_objects::elset>;
  using sections = std::vector<fem_objects::section>;
  using materials = std::vector<fem_objects::material>;
  using steps = std::vector<fem_objects::step>;

  nodes _nodes;
  nsets _nsets;
  elements _elements;
  elsets _elsets;
  sections _sections;
  materials _materials;
  steps _steps;

private:
  std::string _filename;
  std::string _name;
};

#endif // input_hpp
