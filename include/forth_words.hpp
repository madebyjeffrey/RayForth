
#ifndef FORTH_WORDS
#define FORTH_WORDS

#include "forth.hpp"


namespace Forth
{
	Status add(Stack &stack);
	Status minus(Stack &stack);
	Status product(Stack &stack);
	Status divide(Stack &stack);
	Status mod(Stack &stack);
	Status print(Stack &stack);
	Status cr(Stack const &stack);
	Status swap(Stack &stack);
	Status drop(Stack &stack);
	Status bye(Stack &stack);
	Status print_stack(Stack &stack);
	
	Status makeSphere(Stack &stack);
	Status vec3(Stack &stack);
	Status makeTriangle(Stack &stack);
	Status renderScene(Stack &stack);
}

#endif