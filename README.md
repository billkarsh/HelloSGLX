HelloSGLX
=========

### What

This is a Windows command-line applet that lets remote applications
talk to SpikeGLX phase30 versions 20220425 and later:

* Set/get parameters.
* Start/Stop runs.
* Start/stop writing.

It integrates easily with most programming/scipting languages. The kit
includes demos for Python and C#.

Your download includes a compiled HelloSGLX.exe, ready to use, nothing
to build.

>*Fetching realtime stream data is not supported because this mode of
communication (shell commands) is too slow to make that practical.*

### Who

HelloSGLX is developed by Bill Karsh of the Tim Harris lab.
Initially hosted/funded by HHMI. Currently supported by {NIH, Wellcome Trust}
grants via {JHU, UCL}.

### Building in Windows

The source code that builds HelloSGLX is included in the Build folder,
though the app has been precompiled for you. This material is mainly
for educational interest.

I build using Qt 5.12.0 (MinGW 64-bit). Compiled components include
supporting DLLs from that Qt version.

### Compiled Software

Included in download.

### Licensing

Use is subject to Janelia Research Campus Software Copyright 1.2 license terms:
[http://license.janelia.org/license](http://license.janelia.org/license).


_fin_

