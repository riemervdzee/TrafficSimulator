#include "CValidator.hpp"
#include <regex>

// pattern for reconnizing valid ip address
const std::regex ipPattern("(\\d{1,3}).(\\d{1,3}).(\\d{1,3}).(\\d{1,3})");

// general
bool Validator::IsValidIPAddress(const std::string& ip)
{
	return std::regex_match(ip, ipPattern);
}

bool Validator::IsValidIPAddress(const char* ip)
{
	return std::regex_match(ip, ipPattern);
}
