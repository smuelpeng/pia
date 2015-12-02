pia documentation
-----------------

The docbook source in `pia.xml` is used to generate the Unix
man-page `pia.3` and the plain text `pia.txt`. The tools
`xsltproc` and `lynx` are required to regenerate these files.

The script `pia-fetch.sh` pulls the latest version of `pia.c`
and `pia.h` from the GitHub master to the current directory.
