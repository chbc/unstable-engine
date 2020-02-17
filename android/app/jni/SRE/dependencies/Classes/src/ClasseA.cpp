#include "ClasseA.h"
#include "ClasseB.h"

const char* ClasseA::func()
{
	ClasseB b;
	return b.getId();
}
