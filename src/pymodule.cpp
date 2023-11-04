#include <windows.h>
#include <pybind11\pybind11.h>

#define _(x) #x

PYBIND11_MODULE(osutils, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
}
