#include <dystring/reader.h>
#include <dystring/types.h>
#inlcude <libbitset/bitset.h>
#include <stdlib.h>

bitset_t *dystring_reader_read_bitset(dystring_reader_t *obj) {
	if(!obj)
		return NULL;
	obj->_errno = 0;
	qword_t value;
	value = dystring_reader_read_qword(obj);
	if(obj->_errno != 0)
		return NULL;
	bitset_t *bs;
	bs = bitset_unpack(value);
	if(!bs)
		obj->_errno = 3;
	return bs;
}