#include <locale>
#include <iostream>
#include <fstream>

std::ofstream mylog("tools.log");

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

int all_until(std::istream& inp,const std::string finish,std::string& line)
{
    int explen=finish.length();
    line="";

    while(true)
    {
        auto iC = inp.get();
        if(iC==EOF)
        {
            return EOF;
        }
        line+=iC;
        if(line.length()>=explen
        &&  finish.compare(line.substr(line.length()-explen,explen) ) == 0
                )
            return 1;
    }
    return 0;//Never used
}

int next_block(std::istream& inp,std::string& line,std::ctype<char>::mask interest=
std::ctype_base::space | std::ctype_base::alpha | std::ctype_base::digit | std::ctype_base::punct
        )
{
    // Get a reference to the ctype<char> facet.
    static const std::locale loc ( "" );
    static const std::ctype<char>& ct = std::use_facet< std::ctype<char> >(loc);
    static const std::ctype<char>::mask* table=ct.table();

    line="";

    std::ctype<char>::mask typek1 = 0;
    std::ctype<char>::mask typek2 = 0;

    while(true)
    {
        auto iC = inp.get();

        if(iC==EOF)
        {
            if(line.length()>0)
                return typek1;
            else
                return EOF;
        }

        typek2=table[iC] & interest;

        if(typek1==0) //Pierwszy znak ciągu
        {
            typek1=typek2;line+=iC;
        }
        else
            if( typek1 == typek2 ) //Kolejny znak ciągu
            {
                line+=iC;
            }
            else //Niepasujący znak
            {
                inp.unget();
                return typek1;
            }
    }
    return 0;
}

int  line_counter=1;
void calculate_lines(std::string& line)
{
    auto pos = line.find('\n');
    while(pos != std::string::npos)
    { line_counter++; pos = line.find('\n',pos+1); }
}

int main(int argc,const char** argv)
{
    std::cerr << "Processing refactor tools error stream:" << std::endl << std::flush;

    std::string line="s";

    while(true) {
        auto t = next_block(std::cin, line);
        calculate_lines(line);

        if(t==EOF) break;

        if((t & std::ctype_base::punct) != 0
           && line.length() > 1
           && line[0] != '/' && line[0] != '*'
           && line.find('/')!=std::string::npos
                )
        {
            std::cerr<<std::endl<<"Line "<<line_counter<<" Suspicious string of punctuation marks: "<<"'"<<line<<"'"<<std::endl;
                mylog<<std::endl<<"Line "<<line_counter<<" Suspicious string of punctuation marks: "<<"'"<<line<<"'"<<std::endl;
            std::cerr.flush();
        }
        else
        if ((t & std::ctype_base::punct) != 0
            && line.length() >= 2
            && line[0] == '/'
            && line[1] == '/'
                )
        {
            std::string restOfComment;
            getline(std::cin, restOfComment);
            line_counter++;//?
            std::cout << line << restOfComment << std::endl;
                mylog << line << restOfComment << std::endl;
        }
        else
        if ((t & std::ctype_base::punct) != 0
            && line.length() >= 2
            && line[0] == '/'
            && line[1] == '*'
                )
        {
            std::string restOfComment;
            all_until(std::cin,"*/",restOfComment);
            calculate_lines(restOfComment);
            std::cout << line << restOfComment << std::endl;
                mylog << line << restOfComment << std::endl;
        }
        else
        {
            std::cout << line;

            mylog << "'" << line << "'";
            mylog <<"\t\t\t"<<print_type(t);
            mylog << std::endl;
        }
    }

    return 0;
}
