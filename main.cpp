#include <iostream>
#include <thread>
#include <mutex>




//================================_Task_1_================================

static std::mutex mtx_cout;

class pcout {
private:
	std::unique_lock<std::mutex> ulk;

public:
	pcout() : ulk(std::unique_lock<std::mutex>(mtx_cout)) {}

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

void someOperation(int number)
{
	pcout() << "Start thread " << number << std::endl;
	pcout() << "Stop thread " << number << std::endl;
}


int main()
{
	pcout() << "===================================================_Task_1_===========================================" << std::endl;
	std::thread th1(someOperation, 1);
	std::thread th2(someOperation, 2);
	std::thread th3(someOperation, 3);
	std::thread th4(someOperation, 4);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	return 0;
}