#include <iostream>	//ostream operator
#include <list>			//std::list
#include <string>		//std::string
#include <algorithm>//std::find
#include <iterator>	//std::ostream_iterator

struct Word
{
	Word() { m_times = 1; }

	bool operator<(const std::string& str_);
	bool operator==(const std::string& str_);

	int m_times;
	std::string m_str;
};

bool Word::operator<(const std::string& str_)
{
	return (m_str.compare(str_) < 0 ? true : false);
}

bool Word::operator==(const std::string& str_)
{
	return (!m_str.compare(str_));
}

std::ostream& operator<<(std::ostream& os_, const Word& word_)
{
	return os_ << word_.m_str << " -> " << word_.m_times << std::endl;
}

void PrintWords(std::list<Word> words)
{
	std::ostream_iterator<Word> o(std::cout);
	std::copy(words.begin(), words.end(), o);
}

int main()
{
	typedef std::list<Word> Histo;
	Histo words;
	std::string input;
	Word wrd;

	std::cin >> input;

  while (input.compare(".") != 0)
  {
	  	Histo::iterator it = std::find(words.begin(), words.end(), input);

      if (it == words.end())
      {
				wrd.m_str = input;
				words.push_back(wrd);
      }
      else
      {
		  	++(it->m_times);
      }

      std::cin >> input;
    }

	PrintWords(words);
}
