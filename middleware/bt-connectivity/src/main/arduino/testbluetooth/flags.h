#ifndef __FLAGS__
#define __FLAGS__

#define BIT(x) (1 << (x))

#define SET(flags, x) ((flags) |= BIT(x))

#define CLEAR(flags, x) ((flags) &= ~BIT(x))

#define TOGGLE(flags, x) ((flags) ^= BIT(x))

#define RAW_CHECK(flags1, flags2) (((flags1) & (flags2)) == (flags2))

#define CHECK(flags, x) RAW_CHECK(flags, BIT(x))

#endif /* __FLAGS__ */
