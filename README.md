What it is
==========

A simple C module to strip whitespace from HTML

Reduce the size of HTML pages/fragments by removing whitespace,
which means spaces, tabs and newlines, and HTML comment tags.

Why?
====

GZIP does a far better job compressing content on its way to the 
client, so whats this thing good for?
Well, this module is intended for reducing the storage size
of webpages instead of just their transfer size. This 
is of benefit when pages or even just fragments of them 
are cached on the server. 
In a quick test the average reduction size was between 10-20%.


Drawbacks
=========

There is no special treatment of Javascript. This results in a few 
possible problems: 

* single line comments "//" will cause the rest of the script to
  be commented out because the newlines are removed.
* lines without a semicolon at the end will cause a bug whithout
  a newline at the end
