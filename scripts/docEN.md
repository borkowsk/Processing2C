Processing2C - scripts and library for application porting from Processing to C++
=================================================================================

Scripts are used to transform a project in _Processing_ into a project in C ++ on __linux__ 
systems. The target platform must have a C++ compiler (preferably __gcc__) and __cmake__ and __make__ programs.

Of course, you also need the attached library that implements the Processing interface and the SymShellLight package libraries that provide graphics in __X11__, __MS Windows__, and __SVG__ graphics for running applications on servers that cannot be accessed by _GUI_ but only through a text terminal.

The translation was implemented using the __sed__ program, so the syntax context is always limited to one line, which forces some changes from the PDE code to be made before translation. Sometimes minor additions are also required in the resulting C ++ code, which we try to limit by the set of directives in comments such as:

    - /*_reference*/ translated into '&'
    - /*_pubext*/ translated into 'public virtual'
    - /*_interfunc*/ translated into 'virtual'
    - /*_forcebody*/ translated into '=0'
    - /*_downcast*/ translated into 'std::dynamic_pointer_cast\<\1\>'
    - /*_dncast*/ translated into 'std::dynamic_pointer_cast\<\1\>'
    - /*_upcast*/ translated into 'static_cast\<p\1\>'
    - /*_tmpfree*/ translated into '_free_ptr_to\<\1\>'
    - /*_tmpptr*/ translated into '*'


**Visibility of identifiers - the biggest semantic difference between PDE and C++:**

In _Processing_, the order in which you enter global identifiers does not matter - they are all visible everywhere.

The first step to solve this problem is to create a _project_at_once.cpp_ file, which uses the #include directive to include all result files _\*.cpp_ *in alphabetical order*.

Global variables that are indistinguishable from local in a single-line context must be specially marked. The comment that starts with three slashes ('///') is selected, which is also used by programs for automatic code documentation. The same applies to global functions if they are used before definition. Then, just like for global variables, you have to force generating an announcing declaration.

The scripts also find class declarations and make foreshadowing from them, which reduces this problem somewhat, but does not eliminate it. Unfortunately, class announcement declarations only work partially in C++. You cannot create a class object or use any of its properties without fully defining the class. Only reordering the #include directives in the output _project_at_once.cpp_ file can help here.

Also, in _Processing_, variables and functions have separate namespaces. This means that a global variable can have the same name as a local method and both will be distinguished. Such name mixing is not allowed in C++ because function and method identifiers can also appear without the parentheses '()' in a pointer context. Hence a local method with the same name as the global variable will hide that variable, and vice versa, leading to strange phenomena. We try to detect such situations for symbols from the _Processingu_ interface and warn the user about them.

**Classes:**

Default class settings pose a serious problem: in _Processing_ all content of the class is public by default, but private in C++. On the other hand, methods in Processing are virtual by default, not in C ++. The first problem has so far been solved partially for class declarations that have an opening '{' on the same line. The issue of virtual functions is solved by the directive /\*_interfunc\*/.

The third problem is how classes are inherited in _JAVA_ and _Processing_. In this languages, a class can have only one base class and any number of implemented interfaces. However, there can be any number of base classes in C ++, but no interfaces.

We solve this by translating the interfaces to abstract C++ classes without fields and method implementations. To achieve this, it is necessary to use the directives /\*_interfunc\*/ and /\*_forcebody\*/ in the definition of the interface, and the directive /\*_pubext\*/ must be used in the definition of the class implementing interface before each ADDITIONAL interface.

Using the __super__ keyword representing the base class in _Processing_ cannot be translated automatically as it would require a multi-line context with remembering the base class name.
(see https://stackoverflow.com/questions/357307/how-to-call-a-parent-class-function-from-derived-class-function/357380#357380)
We only deal with simple situations when it comes to calling the constructor, provided that the syntax is somewhat unnatural.

The last point is ';' required in C ++ after class declaration. Fortunately, _Processing_ tolerates such semicolons, so you can insert them
in the PDE file.

These solutions allowed me to use Processing2C for my simulation models, but it's not convenient. I plan to write a separate applet which, when inserted into the translation stream, will deal with class declarations as a whole.

**String concatenations**

In _Processing_, string constants are treated as objects of type __String__, which in turn are concatenated with almost any other underlying variable type. In C ++, the conversion of string constants to __Processing :: String__ must be enforced explicitly by adding a constructor call in expressions.

The scripts add such a call in detected concatenation operations, but unfortunately the C ++ compiler often signals "warning" at this point. In general, it is better to simplify concatenation as much as possible before translation.

I have some ideas on how to improve it, but it takes quite a lot of work and testing, and the current solution works somehow.

 
What changes should be made to the PDE files?
---------------------------------------------

Before translating to C ++, you should make some changes to the _Processing_ code and check whether the program works by accident.

1) Parentheses '{' opening class definitions must be moved to the class declaration line. Everything (including the base class and possible interfaces) from the keyword class to '{' must be on one line.

2) After the closing parenthesis, we add ';'. For _Processing_ it makes no difference, but in C ++ it is required.

3) Global variables that should be visible in all project files should be commented using a triple slash instead of a double slash (i.e. '///' and not '//'). The same should be done for global functions.
The character '{', if it is to appear on a line, must follow the declaration and '///' must follow it.

4) We rename variables and object fields with the same names as functions or methods used in the same contexts.

5) We supplement the interfaces and implementing classes with the necessary directives

6) Files defining more basic classes should be named alphabetically earlier than files using these classes, because the scripts use the alphabetical order of placing files in the project. You can also change after translation the order in files are attached (#include) to the file _project_at_once.cpp_.





/********************************************************************/
/*               PROCESSING2C  version 2020-11-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/

