#include <locale>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>

std::string   OutDir="./";     ///< Where byproducts (eg. class headers) have to put?
std::ofstream mylog;           ///< Mainly for error checking
bool EXTRACT_CLASSES=false;    ///< Make separate header file for all detected classes

std::string print_type(std::ctype<char>::mask interest)
{
    std::string out=std::to_string(interest);
    out+="\t";
    if((interest & std::ctype_base::space) !=0 ) out+="space;";//white-space character
    if((interest & std::ctype_base::print) !=0 ) out+="print;";//printable character
    if((interest & std::ctype_base::cntrl) !=0 ) out+="cntrl;";//control character
    if((interest & std::ctype_base::upper) !=0 ) out+="upper;";//uppercase letter
    if((interest & std::ctype_base::lower) !=0 ) out+="lower;";//lowercase letter
    if((interest & std::ctype_base::alpha) !=0 ) out+="alpha;";//alphabetic character
    if((interest & std::ctype_base::digit) !=0 ) out+="digit;";//decimal digit
    if((interest & std::ctype_base::punct) !=0 ) out+="punct;";//punctuation character
    if((interest & std::ctype_base::xdigit)!=0 ) out+="xdigit;";//hexadecimal digit
    if((interest & std::ctype_base::blank) !=0 ) out+="blank;";//blank character
    if((interest & std::ctype_base::alnum) !=0 ) out+="alnum;";//alpha|digit	alpha-numeric character
    if((interest & std::ctype_base::graph) !=0 ) out+="graph;";//alnum|punct	character with graphic representation
    return out;
}

/// All characters up to and including the given sequence
int all_until(std::istream& inp,const std::string finish,std::string& block,char escape='\0')
{
    int exp_len=finish.length();
    block="";

    while(true)
    {
        auto iC = inp.get();

        if(iC==EOF)
            return EOF;

        block+=iC;

        if( escape!='\0' && block.length()>1 && escape==block[block.length()-2] ) //jeśli znak jest poprzedzony ESCAPEm to nie sprawdzamy zakończenia
            continue;

        if(block.length() >= exp_len
           && finish.compare(block.substr(block.length() - exp_len, exp_len) ) == 0
                )
            return 1;
    }
    return 0;//Never used
}

/// Paired characters parentheses - block of even parentheses.
int parentheses_block(std::istream& inp,const char start,const char finish,std::string& block,int counter=0,char escape='\0')
{
    block="";// ??

    do {
        auto iC = inp.get();

        if(iC==EOF)
        { std::cerr << "Unexpected end of file inside parentheses "<<start<<finish<<" block "; return 0;}

        block+=iC;

        if( escape!='\0' && block.length()>1 && escape==block[block.length()-2] ) //jeśli znak jest poprzedzony ESCAPEm to nie sprawdzamy zakończenia
            continue;

        if(iC==start) counter++;
        if(iC==finish) counter--;

    }while(counter!=0);

    return 1;
}


/// Semantic parentheses - block of even parentheses. NOT IMPLEMENTED - todo?
int parentheses_block(std::istream& inp,const std::string start,const std::string finish,std::string& block,int counter=0,char escape='\0')
{
    int exp_len=finish.length();
    block="";

    return 0;//Never used
}

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
            if(block.length()>0)
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

std::string take_identifier(const std::string& curr_block,size_t pos)
{
    std::string out="";

    while(iswblank(curr_block[pos])) pos++;// EAT BLANKS!
    // WHEN COMMENTS INSIDE!!!
    if(curr_block[pos]=='/')
    {                                                                       //std::cerr << "'" << curr_block[pos] <<"' ";
        if(curr_block[++pos]!='*') return "?????";
                                                                            //std::cerr << "'" << curr_block[pos] <<"' ";
        std::string finish="*/";
        int exp_len=2;

        do { pos++;                                                         //std::cerr << "'" << curr_block[pos] <<"' ";
            if( finish.compare(curr_block.substr(pos, exp_len) ) == 0 )
                break;
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
    std::string identifier, output="";
    auto pos=curr_block.find("implements",0);
    if(pos!=std::string::npos)
    {
        pos+=strlen("implements")+1;
        identifier=take_identifier(curr_block,pos);         std::cerr << identifier <<",";
        output+="//_import:"+identifier+"\n";
        pos+=identifier.length();
        while(iswblank(curr_block[pos])) pos++;// EAT BLANKS!
        while(curr_block[pos]==',')
        {
            pos++;
            identifier=take_identifier(curr_block,pos);     std::cerr << identifier <<",";
            output+="//_import:"+identifier+"\n";
            pos+=identifier.length();
            while(iswblank(curr_block[pos])) pos++;// EAT BLANKS!
        }                                                   std::cerr << std::endl;
        return output;
    }
    return "";
}

int  line_counter=1;
void count_lines(std::string& block)
{
    auto pos = block.find('\n');
    while(pos != std::string::npos)
    { line_counter++; pos = block.find('\n', pos + 1); }
}

int main(int argc,const char** argv)
{
    std::cerr << "Processing refactor tools error stream:" << std::endl << std::flush;

    if(argc>0)
    {
        OutDir = argv[1];
        if(argc>1)
            EXTRACT_CLASSES = ( strcasecmp(argv[2],"-ECLL") == 0 );
    }

    mylog.open(OutDir+"/tools.log",std::ios::app);
    if(!mylog.is_open())
    {
        std::cerr << "Cant open file \"" <<  OutDir+"/tools.log" <<"\"\n";
        perror("System message:");
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

    while(true) {
        bool isInterface=false;
        auto t = next_block(std::cin, curr_block);
        count_lines(curr_block);

        if(t==EOF) break;

        if((t & std::ctype_base::punct) != 0
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
        if ((t & std::ctype_base::punct) != 0
            && curr_block.length() >= 2
            && curr_block[0] == '/'
            && curr_block[1] == '/'
                )
        {
            std::string rest_of_comment;
            getline(std::cin, rest_of_comment);
            line_counter++;//?
            std::cout << curr_block << rest_of_comment << std::endl;
                mylog << curr_block << rest_of_comment << std::endl;
        }
        else
        if ((t & std::ctype_base::punct) != 0
            && curr_block.length() >= 2
            && curr_block[0] == '/'
            && curr_block[1] == '*'
                )
        {
            std::string rest_of_comment;
            all_until(std::cin, "*/", rest_of_comment);
            count_lines(rest_of_comment);

            std::cout << curr_block << rest_of_comment ;//<<"/*!?!?!*/";
                mylog << curr_block << rest_of_comment << std::endl;
        }
        else if(curr_block[0] == '"'
        || curr_block[0] == '\'')
            {
                std::string rest_of_string;
                                                                            assert(curr_block.length()==1);
                all_until(std::cin, curr_block, rest_of_string,'\\');
                std::cout << curr_block << rest_of_string ;//<< "/*SP*/";
                mylog <<"STRING/CHAR: "<< curr_block << rest_of_string << std::endl;
            }
            else
        if(curr_block.compare("class")==0
        || (isInterface=(curr_block.compare("interface")==0))
        || curr_block.compare("abstract")==0
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

            std::string super_class=detect_super_class(curr_block);
            std::string this_class=detect_class_name(curr_block);

            if(EXTRACT_CLASSES) // When user want to have separate files for all classes
            {
                std::string  headersrc{ OutDir };
                headersrc+="/";
                headersrc+=this_class;
                headersrc+="_clss.pde";

                mylog << "CREATE HEADER "<< headersrc << std::endl;

                std::ofstream newheader(headersrc);
                newheader<<"//#pragma once\n"
                         <<"//#ifndef "<<"HEADER_"<<this_class<<"_INCLUDED\n"
                         <<"//#define "<<"HEADER_"<<this_class<<"_INCLUDED\n\n";

                if(super_class[0]!='?')
                {
                    newheader<<"//_import:" << super_class << "\n";
                    auto imports=interfaces_imports(curr_block, isInterface);
                    mylog << "DETECTED IMPORTS:" << imports << std::endl;
                    newheader << imports <<std::endl
                              <<"//_superclass:"<<super_class<<"\n";
                }

                std::string class_code;

                if( parentheses_block(std::cin,'{','}',class_code,1) !=0 )
                {
                    count_lines(class_code);

                    std::string  last_line;
                    getline(std::cin, last_line);
                    line_counter++;

                    class_code+=last_line;

                    mylog << "DETECTED CLASS DEFINITION:\n" << class_code << std::endl;
                }

                newheader<<"/// Automatic header for class "<<this_class<<"\n"
                         << curr_block << std::endl
                         << class_code << std::endl
                         <<"/// Generated by Processing2C++ extraction Tools\n"
                         <<"//#endif //"<<"HEADER_"<<this_class<<"_INCLUDED\n\n";
                newheader.close();

                std::cout<<"//_import:"<<this_class<<"\n";

                std::cerr<<"EXTRACT_CLASSES not implemented jet!"<<std::endl;
                //exit(-1);
            }
            else // ALL_IN_ONE_FILE - Into outputs now
            {
                if( super_class.length()>0
                    && super_class.compare("???")!=0
                )
                    std::cout << "\n//_superclass:"<<super_class<<"\n//_derivedclass:"<<this_class<<"\n";

                std::cout << curr_block;
                mylog << "CLASS derived from " << super_class << ":\t'" << curr_block << "'";
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
