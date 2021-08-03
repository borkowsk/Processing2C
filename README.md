# Processing2C

**Scripts &amp; libraries for porting Processing Application (mainly simulations) into C++**

In my professional work as a computer simulation creator, I use Processing to create prototypes of models, which I often reimplement in C++. This often means repeating a coder job that has already been done, which I don't like, so I finally created an automatic translator.
However, the Processing interface is quite extensive and I don't use most of its functionalities, so the library still contains a lot of `"not implemented"` functions and classes!

**Quick start**

It need *SYMSHELLLIGHT* library in sister directory _SymShellLight/_ !

So go into your choice directory and run:

```console
$ git clone https://github.com/borkowsk/SymShellLight.git
$ git clone https://github.com/borkowsk/Processing2C.git
```

Then go into _Processing2C/_ and and run _config.sh_ bash script.

For much more information see: 
*   How to do doc:   [scripts/doc*.md](https://github.com/borkowsk/Processing2C/blob/master/scripts/docEN.md)
*   Interface documenation in doc,pdf & html format   [docs/interface.*](https://github.com/borkowsk/Processing2C/blob/master/docs/Interface.pdf) 

**SOFTWARE REQUIREMENTS**

Curently tested only on __UBUNTU 18.04__ and __UBUNTU 20.04__ on source codes for __Processing 3.x__ .

Toolbox need the following tools available: 

**bash**, **sed**, **cmake**, **make** , **gcc** , **g++**


**NOT IMPLEMENTED**

Functions already declared but still not implemented are listed in _[not_implemented.h](https://github.com/borkowsk/Processing2C/blob/master/not_implemented.h)_ file. 


