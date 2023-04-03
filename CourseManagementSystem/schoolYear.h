#include <string>
class SchoolYear
{
public:
	SchoolYear(std::string time, SchoolYear* pointer);
	SchoolYear();
	std::string getYear();
	void createSchoolYear();
	SchoolYear* pNext;
private:
	std::string year;
};
