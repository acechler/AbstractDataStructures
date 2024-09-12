#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <iostream>
#include "IPrompt.h"


class Prompt : public IPrompt
{
public:

	Prompt() : text("No Prompt set"){}

	Prompt (std::string textParam) : text(textParam)
	{
	}

	~Prompt ()
	{
	}


	void printQuery() const override {
		std::cout << text << std::endl;
	}

private:

	std::string text;

};



#endif //! PROMPT_HPP

