#ifndef fem_objects_hpp
#define fem_objects_hpp

#include <string>
#include <vector>

namespace fem_objects {

struct node {
  std::size_t id;
  double x;
  double y;
  double z;
};

struct nset {
  std::string id;
  std::vector<std::size_t> nodes;
};

struct element {
  std::size_t id;
  std::string type;
  std::string section;
  std::vector<std::size_t> nodes;
};

struct elset {
  std::string id;
  std::vector<std::size_t> elements;
};

struct layer {
  std::string material;
  double thickness;
  double orientation;
};

struct section {
  std::string id;
  std::vector<layer> layers;
};

struct elastic {
  // isotropic
  double e;
  double nu;

  // lamina
  double e_1;
  double e_2;
  double nu_12;
  double g_12;
  double g_13;
  double g_23;
};

struct expansion {
  // isotropic
  double alpha;

  // lamina
  double alpha_1;
  double alpha_2;
};

struct material {
  std::string id;
  std::string type;
  elastic parameters;
  expansion thermal;
  double density;
};

struct dof {
  std::vector<std::string> dofs;
};

struct boundary {
  std::string id;
  std::string nset;
  std::size_t node;
  std::vector<std::string> dofs;
  double magnitude;
};

struct cload {
  std::string id;
  std::string nset;
  std::size_t node;
  std::string dof;
  double magnitude;
};

struct dload {
  std::string id;
  std::string type;
  std::string elset;
  std::size_t element;
  double magnitude;
};

struct thload {
  std::string id;
  std::string type;
  std::string elset;
  std::size_t element;
  double temperature;
};

struct step {
  std::string id;
  std::string analysis;
  std::string type;
  std::vector<boundary> boundaries;
  std::vector<cload> cloads;
  std::vector<dload> dloads;
  std::vector<thload> thloads;

  // for nonlinear analysis
  std::size_t n_steps;
  std::size_t max_iterations;
};

} // namespace fem_objects

#endif // fem_objects_hpp
