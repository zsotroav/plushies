#ifdef DEBUG_EXTRA

#warning DEBUG_EXTRA_COMPILED

#endif

//////////////////////////////////////////

#ifdef CPORTA

#include "test.h"

int main() { dotest(); return 0; }

#else

#include "game.h"

int main() { gameInit(); return 0; }

#endif
