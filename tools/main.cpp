#include <locale>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

std::string   OutDir="./";     ///< Where byproducts (eg. class headers) have to put?
std::ofstream mylog;           ///< Mainly for error checking

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

int all_until(std::istream& inp,const std::string finish,std::string& block)
{
    int exp_len=finish.length();
    block="";

    while(true)
    {
        auto iC = inp.get();
        if(iC==EOF)
        {
            return EOF;
        }
        block+=iC;
        if(block.length() >= exp_len
           && finish.compare(block.substr(block.length() - exp_len, exp_len) ) == 0
                )
            return 1;
    }
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
            typek1=typek2;block+=iC;
        }
        else
            if( typek1 == typek2 ) //Kolejny znak ciągu
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
        OutDir=argv[1];

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
        mylog << std::endl << asctime(loc) << "#=============================================================" << std::endl;
    }

    std::string curr_block="s";

    while(true) {
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
            std::cout << curr_block << rest_of_comment;
                mylog << curr_block << rest_of_comment << std::endl;
        }
        else
        if(curr_block.compare("class")==0
        || curr_block.compare("interface")==0
        )
        {
            std::string rest_of_header;
            all_until(std::cin, "{", rest_of_header);
            curr_block+=rest_of_header;
            std::replace( curr_block.begin(), curr_block.end(),
                          '\n', ' '); // replace all '\n' to ' '
            //When Windows source code remain
            std::replace( curr_block.begin(), curr_block.end(),
                          '\r', ' '); // replace all '\r' to ' '
            //Into outputs now
            std::cout << curr_block;

            mylog << "CLASS:\t'" << curr_block << "'";
            mylog << std::endl;
        }
        else
        {
            std::cout << curr_block;

            mylog << "'" << curr_block << "'";
            mylog <<"\t\t\t"<<print_type(t);
            mylog << std::endl;
        }
    }

    return 0;
}
