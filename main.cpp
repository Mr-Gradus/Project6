#include <iostream>
#include <thread>
#include <mutex>


//================================_Task_1_================================

static std::mutex mtx_cout;

class pcout {
private:
	std::unique_lock<std::mutex> ulk;

public:
	pcout() : ulk(std::unique_lock<std::mutex>(mtx_cout)){}

	template<typename T>
	
	pcout& operator<<(const T& data)
	{
		std::cout << data;
		return *this;
	}

	pcout& operator<<(std::ostream& (*fp)(std::ostream&))
	{
		std::cout << fp;
		return *this;
	}
};
