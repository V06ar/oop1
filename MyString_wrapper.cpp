#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "MyString.h"

typedef struct {
    PyObject_HEAD
        MyString* impl;
} PyMyString;

static void PyMyString_dealloc(PyMyString* self) {
    delete self->impl;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int PyMyString_init(PyMyString* self, PyObject* args, PyObject* kwds) {
    const char* str = "";
    if (!PyArg_ParseTuple(args, "|s", &str)) {
        return -1;
    }
    self->impl = new MyString(str);
    return 0;
}

static PyObject* PyMyString_size(PyMyString* self, PyObject* Py_UNUSED(ignored)) {
    return PyLong_FromSize_t(self->impl->size());
}

static PyObject* PyMyString_str(PyMyString* self) {
    return PyUnicode_FromString(self->impl->c_str());
}

static PyMethodDef PyMyString_methods[] = {
    {"size", (PyCFunction)PyMyString_size, METH_NOARGS, "Returns size of MyString"},
    {NULL, NULL, 0, NULL}
};

// »нициализаци€ структуры PyTypeObject по позици€м C-структуры
static PyTypeObject PyMyStringType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "MyString.MyString",            /* tp_name */
    sizeof(PyMyString),             /* tp_basicsize */
    0,                              /* tp_itemsize */
    (destructor)PyMyString_dealloc, /* tp_dealloc */
    0,                              /* tp_vectorcall_offset */
    0,                              /* tp_getattr */
    0,                              /* tp_setattr */
    0,                              /* tp_as_async */
    0,                              /* tp_repr */
    0,                              /* tp_as_number */
    0,                              /* tp_as_sequence */
    0,                              /* tp_as_mapping */
    0,                              /* tp_hash */
    0,                              /* tp_call */
    (reprfunc)PyMyString_str,       /* tp_str */
    0,                              /* tp_getattro */
    0,                              /* tp_setattro */
    0,                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "MyString C++ wrapper",         /* tp_doc */
    0,                              /* tp_traverse */
    0,                              /* tp_clear */
    0,                              /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    0,                              /* tp_iter */
    0,                              /* tp_iternext */
    PyMyString_methods,             /* tp_methods */
    0,                              /* tp_members */
    0,                              /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    (initproc)PyMyString_init,      /* tp_init */
    0,                              /* tp_alloc */
    PyType_GenericNew,              /* tp_new */
};

static struct PyModuleDef mystringmodule = {
    PyModuleDef_HEAD_INIT,
    "MyString",
    "Python wrapper for MyString C++ class.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_MyString(void) {
    PyObject* m;
    if (PyType_Ready(&PyMyStringType) < 0)
        return NULL;

    m = PyModule_Create(&mystringmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyMyStringType);
    if (PyModule_AddObject(m, "MyString", (PyObject*)&PyMyStringType) < 0) {
        Py_DECREF(&PyMyStringType);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}