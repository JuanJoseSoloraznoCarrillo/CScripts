#define PY_SSIZE_T_CLEAN
#include <python311/Python.h>

// Function to add two integers
static PyObject* add(PyObject* self, PyObject* args) {
    int a, b;

    // Parse the Python arguments into integers
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL; // Return NULL on error
    }

    // Return the sum as a Python object
    return PyLong_FromLong(a + b);
}

// Method definitions
static PyMethodDef ExampleMethods[] = {
    {"add", add, METH_VARARGS, "Add two integers."},
    {NULL, NULL, 0, NULL} // Sentinel to mark the end of the method definitions
};

// Module definition
static struct PyModuleDef examplemodule = {
    PyModuleDef_HEAD_INIT,
    "example", // Name of the module
    NULL,      // Module documentation (may be NULL)
    -1,        // Size of per-interpreter state of the module
    ExampleMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_example(void) {
    return PyModule_Create(&examplemodule);
}