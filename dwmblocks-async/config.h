#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(cmd, interval, signal).
#define BLOCKS(X)         \
    X("dwm_memory", 1, 1)  \
    X("dwm_cpu", 1, 2)   \
    X("dwm_disk", 1, 3) \
    X("dwm_network", 500, 4) \
    X("dwm_volume", 1, 5) \
    X("dwm_battery", 1, 6)     \
    X("dwm_lunar", 1, 7)  \
    X("dwm_date", 1, 8)

#endif  // CONFIG_H
