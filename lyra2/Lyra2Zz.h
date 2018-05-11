#ifndef LYRA2ZZ_H_
#define LYRA2ZZ_H_

#include <stdint.h>

#define LYRA2ZZ_BLOCK_HEADER_LEN_BYTES 112
#define LYRA2ZZ_BLOCK_HEADER_NONCE_OFFSET 19 /* 19 * 4 bytes */

#define LYRA2ZZ_BLOCK_HEADER_DATA_LEN 32
#define LYRA2ZZ_BLOCK_HEADER_ACCUM_CHECKPOINT_BYTES 32

#define LYRA2ZZ_LOG_HEADER __func__ " lyra2zz - "

typedef uint32_t uint256_32_t[8];

/* Assumes that accum_e */
typedef struct lyra2zz_block_header {
	uint256_32_t block_hash;
	uint32_t min_nonce;
	uint32_t max_nonce;
	uint32_t data[LYRA2ZZ_BLOCK_HEADER_DATA_LEN];
} lyra2zz_block_header_t;

class uint256;
struct json_t;

/* this only returns a bool, but because uint256 is required there's too much macro redefinition 
   conflict issues that occur if stdbool is included here, as well as if bool is declared: its type in the 
   source file gets overriden by the macro definition. */
int lyra2zz_read_getblocktemplate(const json_t* blocktemplate, lyra2zz_block_header_t *out_header);

lyra2zz_block_header_t lyra2zz_make_header(
		int32_t version,
		const uint256& prev_block,
		const uint256& merkle_root,
		uint32_t time,
		uint32_t bits,
		uint64_t noncerange,	// low bits = min, 
		const uint256& accum_checkpoint);

int lyra2z_test_blake_80(void);

#endif // LYRA2ZZ_H_