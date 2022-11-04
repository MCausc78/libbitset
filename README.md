# libbitset

A library for bitsets

## Building

To build, run:

```bash
# If you want install to something another directory, set PREFIX variable
# PREFIX="$HOME/opt/mybuilds"

# Build
./builder build
```

To install:
```bash
# Install
# Note: You can remove 'sudo' if installing to home directory
sudo ./builder install
```

## Programs

Example
```c
#include <libbitset/bitset.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	bitset_t *bs;
	bs = bitset_create();
	srand(time(0));
	byte_t i;
	for(i = 0; i < 8; i++) {
		bitset_set_bit(bs, (rand() % 64), true)
	}
	for(i = 0; i < 64; i++) {
		printf("%d: %s", i, bitset_is_enabled(bs, i) ? "true" : "false");
	}
	bitset_destroy(bs);
	return 0;
}
```
