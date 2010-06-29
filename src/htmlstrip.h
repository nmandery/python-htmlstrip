#include <Python.h>


const wchar_t * HTML_COMMENT_START = L"<!--";
const wchar_t * HTML_COMMENT_END   = L"-->";


static PyObject * html_strip(PyObject *, PyObject *);
PyMODINIT_FUNC inithtmlstrip(void);


/**
 * build a Py_UNICODE from wchar_t
 * returns a pointer to a Py_UNICODE or NULL
 * if there was not enough memory available
 */
Py_UNICODE * unicode_from_chars(const wchar_t * , int );


