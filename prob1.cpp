#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
    		stringstream buffer;
		buffer << line;
		int num = 0;
		buffer >> num;
	
			
		if(num != 42)
		{
			std::cout << num << std::endl;
		}
		else
		{
			while (std::getline(std::cin, line));
		}
	}
	
	return 0;
}
