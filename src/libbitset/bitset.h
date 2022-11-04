#ifndef LIBBITSET_BITSET_H
#define LIBBITSET_BITSET_H

#include <dystring/types.h>
#include <stdbool.h>

#ifndef LIBBITSET_VERSION

/********************
*                   *
* 1.2	0b00100001  *
* ^ ^	  ^^^^      *
* | |-----||||^^^^  *
* |-----------||||  *
*                   *
*********************/

#define LIBBITSET_VERSION 0b00000001

#endif /* LIBBITSET_VERSION */

typedef struct {
	dword_t part1;
	dword_t part2;
	dword_t _errno;
} bitset_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bitset_t *bitset_create(void);

bool bitset_is_enabled(bitset_t *, byte_t);
bitset_t *bitset_set_bit(bitset_t *, byte_t, bool);

qword_t bitset_pack(bitset_t *);
bitset_t *bitset_unpack(qword_t);
byte_t bitset_length(bitset_t *);
void bitset_destroy(bitset_t *);

dword_t libbitset_get_version(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBITSET_BITSET_H */
