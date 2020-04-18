#include <boost/python.hpp>
#include <CellularAutomata.hpp>

using namespace boost::python;

// Defines a python module which will be named "pylib"
BOOST_PYTHON_MODULE(pylibcaflu)
{

	class_< CellularAutomata >("CellularAutomata", init<int, int>())
	.def_readonly("EMPTY", &CellularAutomata::EMPTY)
	.def_readonly("SUSCEPTIBLE", &CellularAutomata::SUSCEPTIBLE)
	.def_readonly("INFECT", &CellularAutomata::INFECT)
	.def_readonly("RECOVER", &CellularAutomata::RECOVER)
	.def_readonly("DIE", &CellularAutomata::DIE)
    .def_readonly("P_INFECT", &CellularAutomata::P_INFECT)
	.def_readonly("P_RECOVER", &CellularAutomata::P_RECOVER)
	.def_readonly("P_DIE", &CellularAutomata::P_DIE)
    .def("clear", &CellularAutomata::clear)
    .def("random", &CellularAutomata::random)
    .def("update", &CellularAutomata::update)
    .def("setProb", &CellularAutomata::setProb)
    .def("getState", &CellularAutomata::getState)
    .def("getStatistic", &CellularAutomata::getStatistic)
    .def("setDays2R", &CellularAutomata::setDays2R);

}
