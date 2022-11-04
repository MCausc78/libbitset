#include <dystring/writer.h>
#include <libbitset/writer.h>
#include <stdlib.h>

dystring_writer_t *dystring_writer_write_bitset(dystring_writer_t *obj, bitset_t *bs) {
	if(!obj)
		return obj;
	obj->_errno = 0;
	if(!bs) {
		obj->_errno = 3;
		return obj;
	}
	qword_t value = bitset_pack(bs);
	dystring_writer_write_qword(obj, value);
	return obj;
}
