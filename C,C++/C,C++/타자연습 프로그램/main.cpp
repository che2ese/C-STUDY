#include "Header.h"
#include "TypingSystem.h"

int main() {
	srand(time(0));
	TypingSystem* s = new TypingSystem;
	s->start();

	return 0;
}