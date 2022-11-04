#ifndef LIBBITSET_WRITER_H
#define LIBBITSET_WRITER_H

#include <dystring/writer.h>
#include <libbitset/bitset.h>

dystring_writer_t *dystring_writer_write_bitset(dystring_writer_t *, bitset_t *);

#endif /* LIBBITSET_WRITER_H */
