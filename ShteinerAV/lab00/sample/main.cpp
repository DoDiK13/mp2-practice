#include <iostream>
#include <stdexcept>

int main() {
	try {

	}catch(const std::exception& e) {
		std::cout << "Îøèáêà: " << e.what() << std::endl;
	}
	return 0;
}