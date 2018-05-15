#include <iostream>
#include <string>
#include <new>

const short BUFFER = 512;

class JustTesting
{
private: 
	std::string words;
	int number;
public:
	JustTesting(const std::string & s = "Just Testing", int n = 0)
	{
		words = s;
		number = n;
		std::cout << words << " constructed." << std::endl;
	}
	~JustTesting() { std::cout << words << " destroyed." << std::endl; }
	void Show() { std::cout << words << ", " << number << std::endl; }
};

int main()
{
	char * buffer = new char[BUFFER];

	JustTesting *pc1, *pc2;

	pc1 = new (buffer) JustTesting;
	pc2 = new JustTesting("Heap1", 20);

	std::cout << "\nMemory block addresses:" << std::endl;
	std::cout << "buffer: " << static_cast<void*>(buffer) << "    heap: " << pc2 << std::endl; // cast to <void*>, else buffer would display the first character in the array 
	 
	std::cout << "\nMemory contents:" << std::endl;
	std::cout << pc1 << ": ";
	pc1->Show();
	std::cout << pc2 << ": ";
	pc2->Show();

	std::cout << "\n";

	JustTesting *pc3, *pc4;
	pc3 = new (buffer) JustTesting("Bad Idea", 6); // object pointed to by pc1 is overwritten, its destructor never called
	pc4 = new JustTesting("Heap2", 10);

	std::cout << "\nMemory contents:" << std::endl;
	std::cout << pc3 << ": ";
	pc3->Show();
	std::cout << pc4 << ": ";
	pc4->Show();

	// see page 673
	JustTesting *pc5 = new (buffer + sizeof(JustTesting)) JustTesting("Better Idea", 7);
	std::cout << "\nMemory contents of pc5:" << std::endl;
	std::cout << pc5 << ": ";
	pc5->Show();

	std::cout << "\n";

	delete pc2;			// free Heap1
	delete pc4;			// free Heap2
	delete[] buffer;	// free buffer, but does not invoke the destructor of the object stored in buffer

	std::cout << "Done." << std::endl;

	std::cin.get();

	return 0;
}