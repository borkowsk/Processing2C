# Processing2C version 0.26

**Scripts &amp; libraries for porting Processing Application (mainly simulations) into C++**

In my professional work as a computer simulation creator, I use Processing to create prototypes of models, which I often reimplement in C++. This often means repeating a coder job that has already been done, which I don't like, so I finally created an automatic translator.
However, the Processing interface is quite extensive and I don't use most of its functionalities, so the library still contains a lot of `"not implemented"` functions and classes!

**Quick start**

It need *SymShellLight* library, which is loaded as a submodule!
So go into your choice directory and run:

```console
$ git clone --recursive https://github.com/borkowsk/Processing2C.git
```

Then go into _Processing2C/_ and and run _config.sh_ bash script.

For update submoduled library to most recent version, go to Processing2C top folder and use:

```console
$ git submodule update --remote --recursive
```

For much more information see: 
*   __How to do__ doc:   [scripts/doc*.md](https://github.com/borkowsk/Processing2C/blob/master/scripts/docEN.md)
*   __Interface__ documentation in doc,pdf & html format [docs/interface.*](https://github.com/borkowsk/Processing2C/blob/master/docs/Interface.pdf) 
*   __Doxygen__ documentation could be created. __Doxyfile__ is in _docs_ subdirectory.

**SOFTWARE REQUIREMENTS**

Curently tested only on __UBUNTU from version 18.04__ to __22.04__ on source codes for __Processing 3.x__ .

Toolbox need the following tools available: 

**bash**, **sed**, **cmake**, **make** , **gcc** , **g++** , **ninja** (package ninja-build)


**NOT IMPLEMENTED**

Functions already declared but still not implemented are listed in _[not_implemented.h](https://github.com/borkowsk/Processing2C/blob/master/docs/not_implemented.h)_ file. 

**SPONSORS**

This tool was initially created for my private educational experiment, but when it proved useful, it was used for two European grants: __HumanAI__ and __GuestXR__, so its further development is partly due to this funding.

**COFFE 🍵**

If You find this software useful to You, buy me a coffee. Software development is a job that consumes huge amounts of coffee 😥.

https://www.buymeacoffee.com/wborkowsk


