#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "LinearAssignment.hpp"

namespace py = pybind11;


PYBIND11_MODULE(pylinassignment, m)
{
  m.doc() = "pylinassignment";

  m.def("linear_assignment", &linear_assignment, R"pbdoc(
         Solve a (rectangular) linear-assignment problem given a 2d-numpy-array cost-matrix
  )pbdoc");
}
