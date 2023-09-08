#include "FineGrainedQueue.h"
#include <iostream>
#include <thread>



int main()
{

		FineGrainedQueue queue{};

		auto pointer = [&queue](int value, int pos) { queue.insertIntoMiddle(value, pos); };

		std::thread t1(pointer, 2, 2);
		std::thread t2(pointer, 5, 6);
		std::thread t3(pointer, 7, 2);


		t1.join();
		t2.join();
		t3.join();

		std::thread t4(pointer, 20, 1);
		std::thread t5(pointer, 30, 1);
		std::thread t6(pointer, 40, 1);

		t4.join();
		t5.join();
		t6.join();
		

		std::cout << queue << std::endl;


	return 0;
}