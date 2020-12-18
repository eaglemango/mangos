#include "panic.h"

void panic_maker(const char* when, const char* where, const char* why, ...) {
    // Message header
    printf("\n\n================================= KERNEL PANIC =================================\n");

    printf("Sorry, but your mangOS is crushed! (o o )'\n\n");

    // Printf panic time and date
    printf("When: %s\n\n", when);

    // Print panic location
    printf("Where: %s\n\n", where);

    // Print panic reason =====================================================
    printf("Why: ");

    va_list arg_list;
	va_start(arg_list, why);
	vprintf(why, arg_list);
	va_end(arg_list);
    printf("\n\n");
    // ========================================================================

    // Print registers status
    // TODO: print registers status

    printf("Please, send this log to tg:@eaglemango and then reboot the system.\n");

    // Message footer
    printf("\n================================================================================");

    // Don't allow OS to perform further actions
    halt_but_dont_catch_fire();
}
