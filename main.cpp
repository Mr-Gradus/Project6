#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <Windows.h>


//================================_Task_1_================================

static std::mutex mtx_cout;
std::mutex m_a;
std::mutex m_b;
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


//================================_Task_2_================================


void progress()
{
	std::lock_guard<std::mutex> m{ m_a };
	
	pcout() << "Loading Please Wait";

	Sleep(100);
	pcout() << "." << std::flush;
	Sleep(100);
	pcout() << "." << std::flush;
	Sleep(100);
	pcout() << "." << std::flush;
	Sleep(100);
	pcout() << "." << std::flush;
	Sleep(100);
	pcout() << "." << std::flush;
	Sleep(100);
	pcout() << std::endl;
}

void primeNum(int n)
 {
	
	
	


	std::lock_guard<std::mutex> m{m_b};
	int size = n; // ����� ��������� ��� ������� ����� ��� �����������
	 int* primes = new int[n]; // ������ ������� �����
	 int* numbers = new int[size]; // ������ ��� �����
	 

	 for (int i = 0; i < size; i++)
		 numbers[i] = i; // ��������� ������ (����� ����� ������� ��������)

	 primes[0] = 2; // ������ ������� ����� - 2
	 int i = 0; // ������ �������� �������� �����

	 while (i < n) {
		 int p = primes[i++]; // ���������� ������� ������� �����

		 for (int j = p * 2; j < size; j += p)
			 numbers[j] = 0; // �������� ��� ������� ��� ����� � �������

		 while (numbers[p + 1] == 0)
			 p++; // ���� ��������� ��������� �����

		 if (p + 1 >= size) { // ���� ������ �� �������, ��������� ������
			 int* tmp = new int[size * 2];

			 for (int k = 0; k < size; k++)
				 tmp[k] = numbers[k];

			delete[] numbers;

			 size *= 2;
			 numbers = tmp;

			 for (int j = size / 2; j < size; j++)
				 numbers[j] = j; // ��������� ����� ����� ������� �������

			 i = 0; // ������������ � ��������� ������ �����������
		 }
		 else
			 primes[i] = p + 1; // ���������� ����� ������� �����
	 }

	 pcout() << n << " prime number is " << primes[n - 1] << std::endl;

	 delete[] new int[n];
	 delete[] new int[size];
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
	
	pcout() << "\n===================================================_Task_2_===========================================" << std::endl;
	
	int n;
	pcout() << "Enter number of prime number: ";
	std::cin >> n; // ��������� ����� �������� �����, ������� ����� �����
	
	std::thread th6{ progress};
	th6.join();
	std::thread th5{ primeNum, n };
	th5.join();
	
	return 0;
}