#include <iostream>
#include "Console.h"

int main()
{
	Console console{ "MyConsole" };

	WindowConsole wc{ &console, 2, 2, 10, 40 };
	wc.Show();
	std::cin.get();
	wc.Hide();
}