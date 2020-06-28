#pragma once
#include <iostream>

class exceptions
{
	std::string error_message;
public:
	exceptions() : error_message("Unknown error") {}
	exceptions(const std::string& error_message) : error_message(error_message) {}

	std::string get_string() const
	{
		return error_message;
	}

	friend std::ostream& operator << (std::ostream& os, const exceptions& exc);
};

std::ostream& operator << (std::ostream& os, const ::exceptions& exc)
{
	os << exc.get_string();
	return os;

}