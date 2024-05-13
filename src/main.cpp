#ifdef COMPILE_DEBUG_ENABLED

#warning DEBUG_COMPILE_ENABLED

#endif

//////////////////////////////////////////

#ifdef CPORTA

#include "test.h"

int main() { dotest(); return 0; }

#else

#include "game.h"

int main() { gameInit(); return 0; }

#endif
