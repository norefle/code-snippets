#include "modules/units.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>

#include <boost/units/base_units/imperial/foot.hpp>

namespace module
{


namespace
{

static const std::string kPadding = "               ";
static const auto kColumnWidth = 15;

template<typename Printable>
std::string makeString(Printable&& value)
{
    std::stringstream stringified;
    stringified << boost::units::engineering_prefix << value;

    std::stringstream out;
    out << kPadding.substr(0, kColumnWidth - stringified.str().length()) << stringified.str() << "|";

    return out.str();
}

template<typename Unit>
void printLine(const std::vector<double>& distances, double factor)
{
    std::for_each(std::begin(distances), std::end(distances), [=](double distance){
        std::cout << makeString(Unit(distance * factor * boost::units::si::meters));
    });
}

} // anonymous namespace

bool UnitsModule::execute(const lib::ArgumentCollection& commandLine)
{
    const std::vector<double> distances = { 0.003, 0.3, 0.5, 1, 1.7, 5 };
    const std::vector<double> factors = { 1, 10, 100, 1000, 10000 };


    std::cout << makeString(" ");
    for(auto distance: distances)
    {
        std::cout << makeString(distance);
    }
    std::cout << std::endl;

    for(auto factor: factors)
    {
        std::cout << makeString(factor);

        printLine<boost::units::quantity<boost::units::si::length>>(distances, factor);
        std::cout << std::endl;

        std::cout << makeString(" ");
        printLine<boost::units::quantity<boost::units::imperial::foot_base_unit::unit_type>>(distances, factor);
        std::cout << std::endl;
    }

    return true;
}

} // module
