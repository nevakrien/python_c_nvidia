#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include <omp.h>

static PyObject* scale_array(PyObject* self, PyObject* args) {
    PyObject* input_obj = NULL;
    double scale_factor;
    if (!PyArg_ParseTuple(args, "Od", &input_obj, &scale_factor)) {
        return NULL; // Error in parsing arguments.
    }

    PyArrayObject* input_array = (PyArrayObject*)PyArray_FROM_OTF(input_obj, NPY_DOUBLE, NPY_ARRAY_ENSUREARRAY | NPY_ARRAY_ENSURECOPY);

    if (input_array == NULL) {
        return NULL; // Error in converting to array or making a copy.
    }


    // Get a pointer to the array data.
    double* data = (double*)PyArray_DATA(input_array);
    npy_intp size = PyArray_SIZE(input_array);

    // Perform the scaling operation with OpenMP, potentially offloading to a GPU.
    #pragma omp target teams distribute parallel for map(tofrom:data[0:size])
    for (npy_intp i = 0; i < size; ++i) {
        data[i] *= scale_factor;
    }

    // Return the new, scaled array.
    return (PyObject*)input_array;
}

static PyMethodDef MyMethods[] = {
    {"scale_array", scale_array, METH_VARARGS, "Extract array data and shape."},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef pygpu = {
    PyModuleDef_HEAD_INIT, "pygpu", NULL, -1, MyMethods
};

PyMODINIT_FUNC PyInit_pygpu(void) {
    import_array(); // Crucial! Initializes NumPy API.
    return PyModule_Create(&pygpu);
}
