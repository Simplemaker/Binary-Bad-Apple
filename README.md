# Binary Video File Extractor and Viewer

This repository contains a toolkit for extracting video to a binary format,
and a viewer written in c.

## Tools

 - `extract.py` takes a video file "Bad Apple.webm" (not provided) and 
 produces a binary video file "Bad Apple.bin"

 - `view.py` can be configured to display frames from the binary video 
 format.

 - `main.c` is a video viewer. It relies on an external char array for
 the video data.

 - `makefile` provides rules for converting the binary video file to 
 a compiled object file, and for building the c viewer.
