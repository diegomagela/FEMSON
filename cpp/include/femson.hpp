#ifndef femson_hpp
#define femson_hpp

#include "fem_objects.hpp"
#include "json.hpp"

namespace fem_objects {
using json = nlohmann::json;

void from_json(json const& j, node& n);
void from_json(json const& j, nset& n);
void from_json(json const& j, element& e);
void from_json(json const& j, elset& e);
void from_json(json const& j, layer& l);
void from_json(json const& j, section& s);
void from_json(json const& j, material& m);
void from_json(json const& j, dof& d);
void from_json(json const& j, boundary& b);
void from_json(json const& j, cload& c);
void from_json(json const& j, dload& d);
void from_json(json const& j, thload& t);
void from_json(json const& j, step& s);

}  // namespace fem_objects

namespace femson {
std::vector<bool> get_dofs(std::vector<std::string> const& dofs);

}  // namespace femson

#endif  // femson_hpp
