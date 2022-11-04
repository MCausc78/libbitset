#include <errno.h>
#include <libbitset/bitset.h>
#include <stdbool.h>
#include <stdlib.h>

bitset_t *bitset_create(void) {
	bitset_t *obj;
	obj = malloc(sizeof obj);
	if(!obj)
		return obj;
	obj->_errno = 0;
	obj->part1 = 0;
	obj->part2 = 0;
}

bool bitset_is_enabled(bitset_t *obj, byte_t bit) {
	dword_t *part;
	obj->_errno = 0;
	if(bit < 64) {
		part = (bit > 32 ? &(obj->part2) : &(obj->part1));
		return ((*part) & (1 << (bit % 32))) != 0;
	} else {
		obj->_errno = 1;
	}
	return false;
}

bitset_t *bitset_set_bit(bitset_t *obj, byte_t bit, bool value) {
	if(!obj)
		return obj;
	obj->_errno = 0;
	dword_t *part;
	if(bit < 64) {
		part = ((bit > 32) ? &(obj->part2) : &(obj->part1));
		dword_t rs = (1 << (bit % 32));
		if(value)
			*part |= rs;
		else if(bitset_is_enabled(obj, bit))
			*part &= ~rs;
	} else {
		obj->_errno = 1;
	}
	return obj;
}

qword_t bitset_pack(bitset_t *obj) {
	errno = 0;
	if(!obj) {
			errno = EADDRNOTAVAIL;
			return 0;
	}
	qword_t result = 0;
	result |= (qword_t)obj->part1;
	result |= (((qword_t)obj->part2) << 32);
	return result;
}

bitset_t *bitset_unpack(qword_t value) {
	bitset_t *obj = bitset_create();
	if(!obj || obj->_errno != 0)
		return obj;
	obj->part1 = (value & 0x0000FFFF);
	obj->part1 = (value & 0xFFFF0000);
	return obj;
}

byte_t bitset_length(bitset_t *obj) {
	if(!obj)
		return 0;
	byte_t len;
	qword_t part = bitset_pack(obj);
	for(len = 0; part != 0; part >>= 1)
		len += (part & 1);
	return len;
}

void bitset_destroy(bitset_t *obj) {
	free(obj);
}

dword_t libbitset_get_version(void) {
	return LIBBITSET_VERSION;
}

