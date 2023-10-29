https://www.boost.org/doc/libs/1_75_0/libs/tokenizer/doc/index.html

```c++
// char_sep_example_1.cpp
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

void example_1()
{
  std::string str = ";;Hello|world||-foo--bar;yow;baz|";
  typedef boost::tokenizer<boost::char_separator<char> > 
    tokenizer;
  boost::char_separator<char> sep("-;|");
  tokenizer tokens(str, sep);
  for (tokenizer::iterator tok_iter = tokens.begin();
       tok_iter != tokens.end(); ++tok_iter)
    std::cout << "<" << *tok_iter << "> ";
  std::cout << "\n";
  return;
}

void example_2()
{
    std::string str = ";;Hello|world||-foo--bar;yow;baz|";
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep("-;", "|", boost::keep_empty_tokens);
    tokenizer tokens(str, sep);
    for (tokenizer::iterator tok_iter = tokens.begin();
         tok_iter != tokens.end(); ++tok_iter)
      std::cout << "<" << *tok_iter << "> ";
    std::cout << "\n";
    return;
}

void example_3() {
	std::string str = "This is,  a test";
   typedef boost::tokenizer<boost::char_separator<char> > Tok;
   boost::char_separator<char> sep; // default constructed
   Tok tok(str, sep);
   for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
     std::cout << "<" << *tok_iter << "> ";
   std::cout << "\n";
   return;
}
```