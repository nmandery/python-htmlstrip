#include "htmlstrip.h"

static PyObject *
html_strip(PyObject *self, PyObject *args) {
  
  PyObject * arg_in;
  PyObject * result;
  Py_ssize_t html_len;
  Py_UNICODE * html_in;
  Py_UNICODE * buf;
  Py_UNICODE * html_comment_start;
  Py_UNICODE * html_comment_end;
  int html_comment_start_len, html_comment_end_len;
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

  // html comment strings
  html_comment_start_len = wcslen(HTML_COMMENT_START);
  html_comment_start = unicode_from_chars( 
    HTML_COMMENT_START, 
    html_comment_start_len
    );
  if (html_comment_start == NULL) {
    free(buf);  
    return PyErr_NoMemory();  
  };

  html_comment_end_len = wcslen(HTML_COMMENT_END);
  html_comment_end = unicode_from_chars( 
    HTML_COMMENT_END, 
    html_comment_end_len
    );
  if (html_comment_end == NULL) {
    free(buf);  
    free(html_comment_start);  
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
      else {
         // also leave one space if the last character in the compressed 
         // html was no closing tag
         if ((i_buf>0) && (c == (Py_UNICODE)('<')) && (buf[i_buf-1] != (Py_UNICODE)('>') )) {
          buf[i_buf++] = (Py_UNICODE)(' ');
        }         
      }
    }

    // cut html comments
    int end_comment = i_in + html_comment_start_len;
    if (end_comment < html_len) {
      if (memcmp( 
          &html_in[i_in],
          html_comment_start,
          sizeof(Py_UNICODE) * html_comment_start_len) == 0) {
      
        int cut_comment = 1;
        // do not cut browser specific comments like <!--[if IE] ...
        if (end_comment < html_len) {
            if (html_in[end_comment] == (Py_UNICODE)('[')) {
              cut_comment = 0;  
            }
        }

        if (cut_comment == 1) {
          // delete the char to prevent it from being appended
          c = (Py_UNICODE)(NULL);
          i_in += html_comment_start_len;

          while ((i_in + html_comment_end_len) <= html_len) {
            if (memcmp(&html_in[i_in], html_comment_end,
                    sizeof(Py_UNICODE)*html_comment_end_len) == 0) {
              break;
            }
            // cut 
            i_in++; 
          }
          i_in += html_comment_end_len;
        }


      }
    }

 
    if (c) {
      buf[i_buf++] = c;
    }
  }

  result = PyUnicode_FromUnicode(buf, i_buf);

  free(html_comment_end);
  free(html_comment_start);
  free(buf);
  return result;

};


Py_UNICODE * 
unicode_from_chars(const wchar_t * str, int len) {

  int i;
  Py_UNICODE * puni = (Py_UNICODE *)malloc(
    (len+1)*sizeof(Py_UNICODE)
    ); 

  if (puni == NULL) {
    // could not malloc enough memory
    return NULL; 
  }

  for (i=0; i<len; i++) {
    puni[i] = (Py_UNICODE)str[i];  
  }

  // finalize
  puni[len] = (Py_UNICODE)(0);

  return puni;
};



static PyMethodDef Methods[] = {

     { "strip",  html_strip, METH_VARARGS, "strip whitespace from html."},
     {NULL, NULL, 0, NULL}        /* Sentinel */

};


PyMODINIT_FUNC
inithtmlstrip(void) {

     Py_InitModule("htmlstrip", Methods);

}
