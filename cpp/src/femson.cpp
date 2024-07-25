#include "femson.hpp"

void fem_objects::from_json(json const& j, node& n) {
  j.at("id").get_to(n.id);
  j.at("x").get_to(n.x);
  j.at("y").get_to(n.y);
  j.at("z").get_to(n.z);
}

void fem_objects::from_json(json const& j, nset& n) {
  j.at("id").get_to(n.id);
  j.at("nodes").get_to(n.nodes);
}

void fem_objects::from_json(json const& j, element& e) {
  j.at("id").get_to(e.id);
  j.at("type").get_to(e.type);
  j.at("section").get_to(e.section);
  j.at("nodes").get_to(e.nodes);
}

void fem_objects::from_json(json const& j, elset& e) {
  j.at("id").get_to(e.id);
  j.at("elements").get_to(e.elements);
}

void fem_objects::from_json(json const& j, layer& l) {
  j.at("material").get_to(l.material);
  j.at("thickness").get_to(l.thickness);
  j.at("orientation").get_to(l.orientation);
}

void fem_objects::from_json(json const& j, section& s) {
  j.at("id").get_to(s.id);
  j.at("layers").get_to(s.layers);
}

void fem_objects::from_json(json const& j, material& m) {
  j.at("id").get_to(m.id);
  j.at("type").get_to(m.type);

  if (m.type == "isotropic") {
    j.at("elastic").at("E").get_to(m.parameters.e);
    j.at("elastic").at("nu").get_to(m.parameters.nu);

    j.at("expansion").at("alpha").get_to(m.thermal.alpha);
  }

  else if (m.type == "lamina") {
    j.at("elastic").at("E_1").get_to(m.parameters.e_1);
    j.at("elastic").at("E_2").get_to(m.parameters.e_2);
    j.at("elastic").at("nu_12").get_to(m.parameters.nu_12);
    j.at("elastic").at("G_12").get_to(m.parameters.g_12);
    j.at("elastic").at("G_13").get_to(m.parameters.g_13);
    j.at("elastic").at("G_23").get_to(m.parameters.g_23);

    j.at("expansion").at("alpha_1").get_to(m.thermal.alpha_1);
    j.at("expansion").at("alpha_2").get_to(m.thermal.alpha_2);
  }

  else
    throw std::runtime_error("material \"" + m.type + "\" not supported.");

  j.at("density").get_to(m.density);
}

void fem_objects::from_json(json const& j, dof& d) {
  j.at("dofs").get_to(d.dofs);
}

void fem_objects::from_json(json const& j, boundary& b) {
  j.at("id").get_to(b.id);

  if (j.contains("nset") and j.contains("node")) {
    throw std::runtime_error(
        "when defining boundary, it must have "
        "defined either \"node\" or \"nset\".");
  }

  if (j.contains("nset")) {
    j.at("nset").get_to(b.nset);
  }

  else if (j.contains("node")) {
    j.at("node").get_to(b.node);
  }

  j.at("dofs").get_to(b.dofs);
  j.at("magnitude").get_to(b.magnitude);
}

void fem_objects::from_json(json const& j, cload& c) {
  j.at("id").get_to(c.id);

  if (j.contains("nset") and j.contains("node")) {
    throw std::runtime_error(
        "when defining cload, it must have "
        "defined either \"node\" or \"nset\".");
  }

  if (j.contains("nset")) {
    j.at("nset").get_to(c.nset);
  }

  else if (j.contains("node")) {
    j.at("node").get_to(c.node);
  }

  j.at("dof").get_to(c.dof);

  j.at("magnitude").get_to(c.magnitude);
}

void fem_objects::from_json(json const& j, dload& d) {
  j.at("id").get_to(d.id);
  j.at("type").get_to(d.type);

  if (j.contains("elset") and j.contains("element")) {
    throw std::runtime_error(
        "when defining dload, it must have "
        "defined either \"element\" or \"elset\".");
  }

  if (j.contains("elset")) {
    j.at("elset").get_to(d.elset);
  }

  else if (j.contains("element")) {
    j.at("element").get_to(d.element);
  }

  j.at("magnitude").get_to(d.magnitude);
}

void fem_objects::from_json(json const& j, thload& t) {
  j.at("id").get_to(t.id);
  j.at("type").get_to(t.type);

  if (j.contains("elset") and j.contains("element")) {
    throw std::runtime_error(
        "when defining thload, it must have "
        "defined either \"element\" or \"elset\".");
  }

  if (j.contains("elset")) {
    j.at("elset").get_to(t.elset);
  }

  else if (j.contains("element")) {
    j.at("element").get_to(t.element);
  }

  j.at("temperature").get_to(t.temperature);
}

void fem_objects::from_json(json const& j, step& s) {
  j.at("id").get_to(s.id);
  j.at("analysis").get_to(s.analysis);
  j.at("type").get_to(s.type);

  if (s.type == "nonlinear") {
    if (j.contains("steps")) {
      j.at("steps").get_to(s.n_steps);
    }

    else {
      s.n_steps = 10;
    }

    if (j.contains("maximum iterations")) {
      j.at("maximum iterations").get_to(s.max_iterations);
    }

    else {
      s.max_iterations = 50;
    }
  }

  if (j.contains("boundaries")) {
    j.at("boundaries").get_to(s.boundaries);
  }

  if (j.contains("cloads")) {
    j.at("cloads").get_to(s.cloads);
  }

  if (j.contains("dloads")) {
    j.at("dloads").get_to(s.dloads);
  }

  if (j.contains("thloads")) {
    j.at("thloads").get_to(s.thloads);
  }
}

std::vector<bool> femson::get_dofs(std::vector<std::string> const& dofs) {
  // get dofs (6 dofs per node)
  std::vector<bool> dofs_vec(6);

  for (auto const& dof : dofs) {
    if (dof == "u") {
      dofs_vec[0] = true;
    }

    else if (dof == "v") {
      dofs_vec[1] = true;
    }

    else if (dof == "w") {
      dofs_vec[2] = true;
    }

    else if (dof == "rx") {
      dofs_vec[3] = true;
    }

    else if (dof == "ry") {
      dofs_vec[4] = true;
    }

    else if (dof == "rz") {
      dofs_vec[5] = true;
    }

    else {
      throw std::runtime_error("degree of freedom \"" + dof + "\" not valid");
    }
  }

  return dofs_vec;
}