/**
 *
 *
 **/

#include <Python.h>

static PyObject * html_strip(PyObject *, PyObject *);
PyMODINIT_FUNC inithtmlstrip(void);


static PyObject *
html_strip(PyObject *self, PyObject *args) {
  
  PyObject * arg_in;
  PyObject * result;
  Py_ssize_t html_len;
  Py_UNICODE * html_in;
  Py_UNICODE * buf;
  Py_UNICODE c;
  int i_in, i_buf;

  // get input html
  if (!PyArg_ParseTuple(args, "O", &arg_in)) {
    return NULL;
  }
  if (!PyUnicode_Check(arg_in)) {
    PyErr_SetString(PyExc_TypeError, "this module only supports unicode strings.");
    return NULL;
  }

  html_in = PyUnicode_AS_UNICODE(arg_in);
  html_len = PyUnicode_GetSize(arg_in);

  // output buffer
  buf = (Py_UNICODE*) malloc(html_len * sizeof(Py_UNICODE));
  if (buf == NULL) {
    return PyErr_NoMemory();  
  }

  // ....
  i_buf = 0;
  for (i_in = 0; i_in < html_len; i_in++) {
    c = html_in[i_in];

    // cut spaces
    if (Py_UNICODE_ISSPACE(c)) {
      // remove all spaces until meeting a non-space character
      while (Py_UNICODE_ISSPACE(c)) {
        c = html_in[++i_in];  
      }

      // leave one space if the next charater is not a '<'
      if (c != (Py_UNICODE)('<')) {
        buf[i_buf++] = (Py_UNICODE)(' ');
      }
    }

 
    if (c) {
      buf[i_buf++] = c;
    }
  }

  result = PyUnicode_FromUnicode(buf, i_buf);
  free(buf);
  return result;

};



static PyMethodDef Methods[] = {

     { "strip",  html_strip, METH_VARARGS, "strip whitespace from html."},
     {NULL, NULL, 0, NULL}        /* Sentinel */

};



PyMODINIT_FUNC
inithtmlstrip(void) {

     Py_InitModule("htmlstrip", Methods);

}
