#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <utility>
#include <stdexcept>


/* PunctStream */
/* ------------------------------------------------------------------------- */
class PunctStream
{
public:
    enum class Mode{ Replace, Erase };
    PunctStream( std::istream& is )
        : source_(is), sensitive_(true), mode_(Mode::Replace) { }

    template<typename T>
    void whitespace( T&& ws );
    void add_white( char ch )
        { ws_.insert(ch); }
    bool is_whitespace( char ch ) const noexcept;

    bool case_sensitive() const noexcept
        { return sensitive_; }
    void case_sensitive(bool b) noexcept
        { sensitive_ = b; }
    void set_mode( Mode mode ) noexcept
        { mode_ = mode; }
    
    PunctStream& operator>>( std::string& s );

    explicit operator bool() const noexcept;

private:
// --- member variables
    std::istream& source_;
    std::stringstream buffer_;
    std::set<char> ws_;
    bool sensitive_;
    Mode mode_;
};

template<typename T>
void PunctStream::whitespace( T&& ws )
{
    ws_.clear();
    ws_.insert( std::begin(std::forward<T>(ws)), std::end(std::forward<T>(ws)) );
}

bool PunctStream::is_whitespace( char ch ) const noexcept
{
    return ws_.find(ch) != ws_.end();
}

PunctStream::operator bool() const noexcept
{
    return !(source_.fail() || source_.bad()) && source_.good();
}

/* PunctStream& PunctStream::operator>>( std::string& s )
{
        while( !(buffer_ >> s) ){
        if( buffer_.bad() || !source_.good() )
            return *this;
        buffer_.clear();
        buffer_.seekp(0);

        for( char ch; source_.get(ch) && ch != '\n'; ){
            if( is_whitespace(ch) ){
                switch(mode_){
                case Mode::Replace: ch = ' '; break;
                case Mode::Erase: continue;
                default:
                    throw std::runtime_error( "< PunctStream::operator>> > Invalid input mode" );
                }
            }
            else if( !sensitive_ )
                ch = ::tolower(ch);
            
            buffer_ << ch;
        }
        buffer_.seekg(0);
    }
    return *this;
} */

PunctStream& PunctStream::operator>>( std::string& s )
{
    while( !(buffer_ >> s) ){
        if( buffer_.bad() || !source_.good() )
            return *this;
        buffer_.clear();

        std::string line;
        getline( source_, line );

        if( Mode::Replace == mode_ )
            std::replace_if(line.begin(), line.end(),
                            [&ws = ws_](char ch){
                                return ws.find(ch) != ws.end();
                            },
                            ' ');
        else{
            auto it = std::copy_if(line.begin(),line.end(),line.begin(),
                        [&ws = ws_](char ch){
                            return ws.find(ch) == ws.end();
                        });
            line.erase(it, line.end());
        }

        buffer_.str(line);
    }
    return *this;
}
/* ------------------------------------------------------------------------- */


int main()
{
    using namespace std;
    PunctStream ps(cin);
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~"); // note \" means " in string
    ps.case_sensitive(false);
    ps.set_mode(PunctStream::Mode::Erase);

    cout << "please enter words\n";
    vector<string> vs;
    string word;
    while (ps>>word)
        std::cout << word << "\n";
    // sort(vs.begin(),vs.end());              // sort in lexicographical order
    // for (int i=0; i<vs.size(); ++i)         // write dictionary
    //     if (i==0 || vs[i]!=vs[i-1]) cout << vs[i] << endl;
}
