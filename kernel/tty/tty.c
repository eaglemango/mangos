#include "tty.h"

static size_t terminal_row;
static size_t terminal_column;
static uint16_t* terminal_buffer;

// Implementations will share static variables
#include "../tty/terminal_initialize.h"

#include "../tty/terminal_putentryat.h"

#include "../tty/terminal_scroll.h"

#include "../tty/terminal_putchar_color.h"

#include "../tty/terminal_write.h"

#include "../tty/terminal_writestring.h"

#include "../tty/terminal_writestring_color.h"
