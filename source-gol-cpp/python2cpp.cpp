#include <boost/python.hpp>
#include <CellularAutomata.hpp>

using namespace boost::python;

// Defines a python module which will be named "pylib"
BOOST_PYTHON_MODULE(pylibca)
{

	class_< CellularAutomata >("CellularAutomata", init<int, int>())
    .def("clear", &CellularAutomata::clear)
    .def("random", &CellularAutomata::random)
    .def("update", &CellularAutomata::update)
    .def("setProb", &CellularAutomata::setProb)
    .def("getState", &CellularAutomata::getState);

}
