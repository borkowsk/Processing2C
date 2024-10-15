/// @file
/// @brief An application that corrects and splits the Processing code before the real translation.
///        PL.: Aplikacja poprawiająca i dzieląca kod Processing-u przed właściwym tłumaczeniem.
/// @author 'borkowsk'
/// @date 2024-10-15 (last modification)
///
//#include <locale>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>

std::string   OutDir="./";        ///< Where byproducts (e.g. class headers) have to put?
std::ofstream mylog;              ///< Mainly for error checking.
bool EXTRACT_CLASSES=false;       ///< Make separate header file for all detected classes.
int  DEBUG_LEVEL=0;               ///< Level of debugging.
std::string current_date_dox;     ///< @ d a t e  extracted from doxygen comments.
std::string current_author_dox;   ///< @ a u t h o r  extracted from doxygen comments.
std::string current_dox_block;    ///< Doxygen lines from beginning to "class definition" or to next  @ b r i e f.
std::string current_imports;      ///< All /*_imports: ... */ directives.

/// \brief  Recode mask of `ctype` into readable text.
/// \param  interest - mask of `ctype` information
/// \return textual representation as `std::string`.
std::string print_type(std::ctype<char>::mask interest)
{
    std::string out=std::to_string(interest);
    out+="\t";
    if((interest & std::ctype_base::space) !=0 ) out+="space;"; //white-space character
    if((interest & std::ctype_base::print) !=0 ) out+="print;"; //printable character
    if((interest & std::ctype_base::cntrl) !=0 ) out+="cntrl;"; //control character
    if((interest & std::ctype_base::upper) !=0 ) out+="upper;"; //uppercase letter
    if((interest & std::ctype_base::lower) !=0 ) out+="lower;"; //lowercase letter
    if((interest & std::ctype_base::alpha) !=0 ) out+="alpha;"; //alphabetic character
    if((interest & std::ctype_base::digit) !=0 ) out+="digit;"; //decimal digit
    if((interest & std::ctype_base::punct) !=0 ) out+="punct;"; //punctuation character
    if((interest & std::ctype_base::xdigit)!=0 ) out+="xdigit;";//hexadecimal digit
    if((interest & std::ctype_base::blank) !=0 ) out+="blank;"; //blank character
    if((interest & std::ctype_base::alnum) !=0 ) out+="alnum;"; //alpha|digit	alpha-numeric character
    if((interest & std::ctype_base::graph) !=0 ) out+="graph;"; //alnum|punct	character with graphic representation
    return out;
}

/// Extract all characters up to and including the given sequence.
int all_until(std::istream& inp,const std::string finish,std::string& block,char escape='\0')
{
    auto exp_len=finish.length();
    block="";

    while(true)
    {
        auto iC = inp.get();

        if(iC==EOF)
            return EOF;

        block+=std::string::value_type(iC); // Get rid of warning about automatic conversion from an integer to SOME char.

        if( escape!='\0' && block.length()>1 && escape==block[block.length()-2] ) //jeśli znak jest poprzedzony ESCAPE-m to nie sprawdzamy zakończenia
            continue;

        if( block.length() >= exp_len
        &&  finish.compare(block.substr(block.length() - exp_len, exp_len) ) == 0
                )
            return 1;
    }

    return 0;//Never used
}

/// Extract paired characters parentheses - block of even parentheses.
int parentheses_block(std::istream& inp,const char start,const char finish,std::string& block,int counter=0,char escape='\0')
{
    block="";// ??

    do {
        auto iC = inp.get();

        if(iC==EOF)
        { std::cerr << "An unexpected end of file inside parentheses "<<start<<finish<<" block "; return 0;}

        block+=char16_t(iC);

        if( escape!='\0' && block.length()>1 && escape==block[block.length()-2] ) //jeśli znak jest poprzedzony ESCAPE-m to nie sprawdzamy zakończenia
            continue;

        if(iC==start) counter++;
        if(iC==finish) counter--;

    }while(counter!=0);

    return 1;
}


/// TODO: Extract semantic parentheses - block of even parentheses. NOT IMPLEMENTED.
int parentheses_block(std::istream& /*inp*/,const std::string& /*start*/,const std::string& finish,std::string& block,int /*counter*/=0,char /*escape*/='\0')
{
    int exp_len=finish.length();
    block="";

    return 0;//Never used
}

/// Extract next block of code.
int next_block(std::istream& inp,std::string& block,std::ctype<char>::mask interest=
                        std::ctype_base::space | std::ctype_base::alpha | std::ctype_base::digit | std::ctype_base::punct
        )
{
    // Get a reference to the ctype<char> facet.
    static const std::locale loc ( "" );
    static const std::ctype<char>& ct = std::use_facet< std::ctype<char> >(loc);
    static const std::ctype<char>::mask* table=ct.table();

    block="";

    std::ctype<char>::mask typek1 = 0;
    std::ctype<char>::mask typek2 = 0;

    while(true)
    {
        auto iC = inp.get();

        if(iC==EOF)
        {
            if(!block.empty())
                return typek1;
            else
                return EOF;
        }

        typek2=table[iC] & interest;

        if(typek1==0) //Pierwszy znak ciągu
        {
            block+=iC;
            typek1=typek2;
            if(iC=='"' || iC=='\'') //Te znaki muszą być obrabiane samotnie
                return typek1;
        }
        else
            if( typek1 == typek2 && iC!='"' && iC!='\'') //Kolejny znak ciągu
            {
                block+=iC;
            }
            else //Niepasujący znak
            {
                inp.unget();
                return typek1;
            }
    }
    return 0;
}

/// Extract identifier
std::string take_identifier(const std::string& curr_block,size_t pos)
{
    std::string out; //EMPTY BY DEFAULT

    while(iswblank(curr_block[pos])) pos++;// EAT BLANKS!
    // WHEN COMMENTS INSIDE!!!
    if(curr_block[pos]=='/')
    {                                                                       //std::cerr << "'" << curr_block[pos] <<"' ";
        if(curr_block[++pos]!='*') return "?????";
                                                                            //std::cerr << "'" << curr_block[pos] <<"' ";
        std::string finish="*/";
        int exp_len=2;

        do { pos++;                                                         //std::cerr << "'" << curr_block[pos] <<"' ";
            if( finish.compare(curr_block.substr(pos, exp_len) ) == 0 ) {
                std::cerr<<"'"<<curr_block<<"'"<<std::endl;
                break;
            }
        }while(true);

        pos+=exp_len;

        while(iswblank(curr_block[pos])) pos++;// EAT BLANKS AFTER COMMENT
    }

    for(size_t i=pos;    curr_block[i]!=','  && curr_block[i]!='<' && curr_block[i]!=',' //IS IdentIFIER? todo!
                      && curr_block[i]!=' '  && curr_block[i]!='\t'
                      && curr_block[i]!='\n' && curr_block[i]!='\0' ; i++)
    {
        out+=curr_block[i];  //std::cerr << curr_block[i];
    }                        //std::cerr <<" ???"<<std::endl;
    return out;
}

/// Detect the name of super class from definition of a class.
std::string detect_super_class(const std::string& curr_block)
{
    std::string super_class="???";
    auto pos=curr_block.find("extends",0);
    if(pos!=std::string::npos)
    {
        pos+=strlen("extends")+1;
        super_class=take_identifier(curr_block,pos);
    }
    /*
    else //interfejsy? Ale one nie są superklasami w języku JAVA!
    {
        pos=curr_block.find("implements",0);
        if(pos!=std::string::npos)
        {
            pos+=strlen("implements")+1;
            super_class=take_identifier(curr_block,pos);
        }
    }
    */
    return super_class;
}

/// Detect the name of class from definition of a class.
std::string detect_class_name(const std::string& curr_block)
{
    std::string this_class="???";
    auto pos=curr_block.find("class",0);
    if(pos!=std::string::npos)
    {
        pos+=strlen("class")+1;
        this_class=take_identifier(curr_block, pos);
    }
    else
    {
        pos=curr_block.find("interface",0);
        if(pos!=std::string::npos)
        {
            pos+=strlen("interface")+1;
            this_class=take_identifier(curr_block, pos);
        }
    }

    return this_class;
}

std::string interfaces_imports(const std::string& curr_block,bool isInterface)
{
    std::string identifier, output="???";
    auto pos=curr_block.find("implements",0);
    if(pos!=std::string::npos)
    {
        pos+=strlen("implements")+1;
        identifier=take_identifier(curr_block,pos);         //std::cerr << identifier <<",";

        if(identifier.empty() || identifier.empty() || identifier[0]=='?')
            return output; //Coś poszło nie tak

        output="/*_import_class:"+identifier+" */\n";
        pos+=identifier.length();

        while(iswblank(curr_block[pos])) pos++;// EAT BLANKS!
        while(curr_block[pos]==',')
        {
            pos++;
            identifier=take_identifier(curr_block,pos);     //std::cerr << identifier <<",";
            // if(identifier.empty() || identifier.length()==0 || identifier[0]=='?')
            //            return output+"???"; //Coś poszło nie tak w tym miejscu
            output+="/*_import_class:"+identifier+" */\n";
            pos+=identifier.length();
            while(iswblank(curr_block[pos])) pos++; // EAT BLANKS!
        }                                                   //std::cerr << std::endl;
    }

    return output;
}

int  line_counter=1;
void count_lines(std::string& block)
{
    auto pos = block.find('\n');
    while(pos != std::string::npos)
    { line_counter++; pos = block.find('\n', pos + 1); }
}

void keep_doxygen_text(const std::string& curr_block,const std::string& rest_of_comment)
{
    std::string dox{curr_block};
    dox+=rest_of_comment;
    if( dox.find("@date")!=std::string::npos || dox.find("\\date")!=std::string::npos)
    {
        current_date_dox = dox;
        current_date_dox += "\n";
        return;
    }
    else
    if( dox.find("@author")!=std::string::npos || dox.find("\\author")!=std::string::npos)
    {
        current_date_dox = dox;
        current_date_dox += "\n";
        return;
    }
    else if(  dox.find("@brief")!=std::string::npos || dox.find("\\brief")!=std::string::npos)
    {
        current_dox_block= dox;
        current_dox_block+="\n";
        return;
    }
    else
    {
        current_dox_block+= dox;
        current_dox_block+="\n";
    }
}

int parseParams(int argc,const char** argv)
{
    std::cerr << "ARGC:" << argc << std::endl;
    for(int i=0;i<argc;i++)
    {
        std::cerr << "ARG"<<i<<"]\t"<< argv[i] <<"\t";
        if(i==0) {
            ;
        }
        else
        if(i==1) {
            OutDir = argv[1]; std::cerr<<"OK "<<"OutDir='"<<OutDir<<"'";
        }
        else
        if( strcasecmp(argv[i], "-ECLL") == 0) {
            EXTRACT_CLASSES = true; std::cerr<<"OK "<<"EXTRACT_CLASSES="<<(EXTRACT_CLASSES?"yes":"no");
        }
        else
        if( strcasecmp(argv[i], "-DEBUG") == 0 ) {
            DEBUG_LEVEL+=1;
        }
        else
        {
            std::cerr<<"unknown parametr"<<std::endl;
            std::cerr<<"USAGE:\n\t"<<argv[0]<<" "<<"<target dir> [-ECLL]"<<std::endl;
            return -1;
        }

        std::cerr << std::endl;
    }

    return 0;
}

/// Main function of class extraction tool.
int main(int argc,const char** argv)
{
    std::cerr << "Processing2C preprocessor compiled "<<__DATE__<< std::endl
              << "This is the beginning of error stream: "<< std::endl << std::flush;


    if(argc>1
    && parseParams(argc,argv)!=0 )
    {
        return -1; //Parsing parametrów się nie powiódł lub był jedynym, co należało zrobić.
    }

    std::string logName= OutDir + "/tools.log";
    mylog.open(logName, std::ios::app);

    if(!mylog.is_open())
    {
        std::cerr << "Cant open file \"" << logName << "\"\n";
        perror("System message:");
        std::cerr.flush();
        std::cerr << "Check if directory exists and proper rights are assigned to it."<<std::endl;
        return -1;
    }
    else
    {
        auto tim=time(nullptr);
        auto loc=localtime(&tim);
        std::cerr << "EXTENDED LOG FILE IN '"<<OutDir<<"/tools.log'"<<std::endl;
        mylog << std::endl << asctime(loc) << "#=============================================================" << std::endl;
        mylog.flush();
    }

    std::string curr_block="s";

    std::cerr<<"Waiting for input from `std::cin`...."<<std::endl;
    while(true) {
        bool isInterface=false;
        auto t = next_block(std::cin, curr_block);
        count_lines(curr_block);

        if(t==EOF) break;

        if( (t & std::ctype_base::punct) != 0
        && curr_block.length() > 1
        && curr_block[0] != '/' && curr_block[0] != '*'
        && curr_block.find('/',1) != std::string::npos
            )
        {
            std::cout << curr_block;

            std::cerr << std::endl << "Line " << line_counter << " Suspicious string of punctuation marks: " << "'" << curr_block << "'" << std::endl;
                mylog << std::endl << "Line " << line_counter << " Suspicious string of punctuation marks: " << "'" << curr_block << "'" << std::endl;
            std::cerr.flush();
        }
        else
        if((t & std::ctype_base::punct) != 0
        && curr_block.length() >= 2
        && curr_block[0] == '/'
        && curr_block[1] == '/'
            )
        {
            std::string rest_of_comment;
            getline(std::cin, rest_of_comment);
            line_counter++;//?
            std::cout << curr_block << rest_of_comment << std::endl;
                mylog << curr_block << rest_of_comment <<"\t\t\tCOMMENT"<< std::endl;
            if(curr_block[2] == '/' && curr_block[3] != '<' ) //DOXYGEN
            {
                if(DEBUG_LEVEL) std::cerr <<"'"<< curr_block << rest_of_comment <<"'"<< std::endl;
                keep_doxygen_text(curr_block,rest_of_comment);
            }
        }
        else
        if((t & std::ctype_base::punct) != 0
        && curr_block.length() >= 2
        && curr_block[0] == '/'
        && curr_block[1] == '*'
            ) {
            std::string rest_of_comment;
            all_until(std::cin, "*/", rest_of_comment);
            count_lines(rest_of_comment);
            std::string wholeComment=curr_block;
            wholeComment+=rest_of_comment;
            std::cout <<wholeComment;//<<"/*!?!?!*/";
            mylog << wholeComment << "\t\t\tCOMMENT" << std::endl;
            if (wholeComment[2] == '*') //DOXYGEN
            {
                if(DEBUG_LEVEL) std::cerr << "'" << curr_block << rest_of_comment << "'" << std::endl;
                keep_doxygen_text(curr_block,rest_of_comment);
            }
            else
                if(wholeComment[2] == '_' && wholeComment[3] == 'i' && wholeComment[4] == 'm'
                && ( strstr(wholeComment.c_str(),"_import")!=nullptr)
                ) //_import_class
                {
                    current_imports+=curr_block+rest_of_comment+'\n';
                }
        }
        else
        if(curr_block[0] == '"'
        || curr_block[0] == '\'')
        {
            std::string rest_of_string;
                                                                                                                        assert(curr_block.length()==1);
            all_until(std::cin, curr_block, rest_of_string,'\\');
            std::cout << curr_block << rest_of_string ;//<< "/*SP*/";
            mylog << curr_block << rest_of_string <<"\t\t\tSTRING or CHAR"<< std::endl;
        }
        else
        if( curr_block=="class"
        ||( isInterface=(curr_block=="interface") )
        || curr_block=="abstract"
        )
        {
            std::string rest_of_header;
            all_until(std::cin, "{", rest_of_header);
            count_lines(rest_of_header);

            curr_block+=rest_of_header;

            std::replace( curr_block.begin(), curr_block.end(),
                          '\n', ' '); // replace all '\n' to ' '
            //When Windows source code remain
            std::replace( curr_block.begin(), curr_block.end(),
                          '\r', ' '); // replace all '\r' to ' '

            mylog <<"\nCLASS HEAD:\n\t"<<curr_block<<std::endl;

            std::string super_class=detect_super_class(curr_block);
            std::string this_class=detect_class_name(curr_block);

            if(EXTRACT_CLASSES) // When user want to have separate files for all classes
            {
                std::string  header_src{OutDir };
                header_src+="/";
                header_src+=this_class;
                header_src+="_class.pde";

                mylog << "CREATE CLASS HEADER FILE:\t" << header_src << std::endl;

                std::ofstream new_header(header_src);
                new_header << "//_pragma once\n"
                         << (current_date_dox.empty()?"":current_date_dox.c_str())
                         <<"//_ifndef "<<"HEADER_"<<this_class<<"_INCLUDED\n"
                         <<"//_define "<<"HEADER_"<<this_class<<"_INCLUDED\n\n"
                         ;
                // Wszystkie dotychczasowe jawne importy z tego pliku
                if(!current_imports.empty()){
                    new_header<<current_imports<<std::endl;
                }
                // Ostatnie komentarze doxygen-a
                if(!current_dox_block.empty()){
                    new_header<< current_dox_block <<std::endl;
                    current_dox_block="";
                }
                // Importy wynikające z interfejsów
                auto imports=interfaces_imports(curr_block, isInterface);
                if(imports[0]!='?')
                {
                    new_header << imports << std::endl;

                    mylog << "DETECTED\n"
                          << "\tIMPORTS:\t" << imports << std::endl;
                }
                // Importowanie klasy bazowej
                if(super_class[0]!='?')
                {
                    new_header << "/*_import_class:" << super_class << " */\n"
                             <<"//_superclass:"<<super_class << "\n"<<std::endl;

                    mylog << "DETECTED\n"
                          << "\tSUPERCLASS:\t" << super_class<<std::endl;
                }

                std::string class_code; // Class definition code
                if( parentheses_block(std::cin,'{','}',class_code,1) !=0 )
                {
                    count_lines(class_code);

                    std::string  last_line;
                    getline(std::cin, last_line);
                    line_counter++;

                    class_code+=last_line;

                    mylog << "DETECTED\n\tCLASS DEFINITION:\n" << class_code << std::endl;
                }

                new_header << "/// @note Automatically extracted definition of `class`: " << this_class << "\n"
                         << curr_block << std::endl
                         << class_code << std::endl;

                if(super_class[0]!='?')
                {
                    new_header << "\n//_endOfSuperClass:" << super_class << std::endl;
                }

                new_header << "\n/// Generated by Processing2C++ extraction Tools\n"
                           << "//_endif //" << "HEADER_" << this_class << "_INCLUDED\n\n";
                new_header.close();

                std::cout<<"/*_import_class:"<<this_class<<" */\n";
            }
            else // ALL_IN_ONE_FILE - Into outputs now
            {
                if( !super_class.empty()
                    && super_class[0]!='?'
                )
                {
                    std::cout << "\n//_endOfSuperClass; // Now will change of superclass!";
                    std::cout << "\n//_superClass:" << super_class
                              << "\n//_derivedClass:"<<this_class<<"\n"<< std::endl;;
                }

                std::cout << curr_block;

                mylog << "CLASS derived from " << super_class ; //<< ":\t'" << curr_block << "'";
                mylog << std::endl;
            }
        }
        else
        {
            std::cout << curr_block;

            mylog << "'" << curr_block << "'";
            mylog <<"\t\t\t"<<print_type(t);
            mylog << std::endl;
        }
    }

    std::cerr<<"\nEnd of Processing refactor tools error stream!\n"<< std::endl;

    return 0;
}
/* ******************************************************************
 *               PROCESSING2C  version 2024                         *
 ********************************************************************
 *           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 *
 *            W O J C I E C H   B O R K O W S K I                   *
 *          Robert Zajonc Institute for Social Studies,             *
 *                     UNIVERSITY OF WARSAW                         *
 *   (Instytut Studiów Społecznych Uniwersytetu Warszawskiego)      *
 *    WWW: http://iss.uw.edu.pl/en/ ; https://en.uw.edu.pl/         *
 *    RG : https://www.researchgate.net/profile/Wojciech-Borkowski  *
 *    GITHUB: https://github.com/borkowsk                           *
 *                                                                  *
 *                               (Don't change or remove this note) *
 ********************************************************************/
