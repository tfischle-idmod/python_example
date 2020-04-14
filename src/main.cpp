#include <pybind11/pybind11.h>
#include <math.h>

int add(int i, int j) {
    return i + j;
}

double calculate_current_immunity(float t_infection, float rate, float postchallenge_peak_immunity)
{
    double current_immunity = 0.0;

    if (t_infection > 30)   // !!!can t_infection be negative e.g.math.floor(-0.1) != 0
    {
        double temp = postchallenge_peak_immunity * std::pow((t_infection / 30), -rate);
        return temp < 1.0 ? 1.0 : temp; //t in this equation is measured in months, not days
    }

    return postchallenge_peak_immunity < 1.0 ? 1.0 : postchallenge_peak_immunity;
}


/*
    def poly_4(self):
        a,b,c,d,e = config.params.poly_4_fertility_coefficients
        if self.age < config.params.minimum_fertility_age or self.age > config.params.maximum_fertility_age:
            return 0
        else:
            x = self.age
            return max(0, a *x**4 + b*x**3 + c*x**2 + d*x + e)
*/            
            
float poly_4(float a, float b, float c, float d, float e, float age, float minimum_fertility_age, float maximum_fertility_age)
{
    if (age < minimum_fertility_age || age > maximum_fertility_age)
    {
        return 0;
    }
    else
    {
        float result = a * std::pow(age, 4) + b* std::pow(age, 3) + c* std::pow(age, 2) + d*age + e;
        return result > 0 ? result : 0;
    }
}

namespace py = pybind11;

PYBIND11_MODULE(python_example, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: python_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");
    
    m.def("calculate_current_immunity", &calculate_current_immunity, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");
    
    m.def("poly_4", &poly_4, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
