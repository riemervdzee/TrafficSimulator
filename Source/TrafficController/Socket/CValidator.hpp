#include <string>

// static validator class
class Validator
{
public:
	static bool IsValidIPAddress(const std::string& ip);
	static bool IsValidIPAddress(const char* ip);

private: 
	Validator() {}
};