/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <linux/types.h>

#define BOOT_MAGIC "ANDROID!"
#define BOOT_MAGIC_SIZE 8
#define BOOT_NAME_SIZE 16
#define BOOT_ARGS_SIZE 512
#define BOOT_EXTRA_ARGS_SIZE 1024

struct boot_img_hdr_v1 {
	// Must be BOOT_MAGIC.
	uint8_t magic[BOOT_MAGIC_SIZE];

	uint32_t kernel_size; /* size in bytes */
	uint32_t kernel_addr; /* physical load addr */

	uint32_t ramdisk_size; /* size in bytes */
	uint32_t ramdisk_addr; /* physical load addr */

	uint32_t second_size; /* size in bytes */
	uint32_t second_addr; /* physical load addr */

	uint32_t tags_addr; /* physical addr for kernel tags */
	uint32_t page_size; /* flash page size we assume */

	// Version of the boot image header.
	// Alternately this is used as dt_size on some hardware.
	union {
		uint32_t header_version;
		uint32_t dt_size; /* device tree in bytes */
	};

	// Operating system version and security patch level.
	// For version "A.B.C" and patch level "Y-M-D":
	//   (7 bits for each of A, B, C; 7 bits for (Y-2000), 4 bits for M)
	//   os_version = A[31:25] B[24:18] C[17:11] (Y-2000)[10:4] M[3:0]
	uint32_t os_version;

	uint8_t name[BOOT_NAME_SIZE]; /* asciiz product name */

	uint8_t cmdline[BOOT_ARGS_SIZE];

	uint32_t id[8]; /* timestamp / checksum / sha1 / etc */

	// Supplemental command line data; kept here to maintain
	// binary compatibility with older versions of mkbootimg.
	uint8_t extra_cmdline[BOOT_EXTRA_ARGS_SIZE];

	uint32_t recovery_dtbo_size;   /* size in bytes for recovery DTBO/ACPIO image */
	uint64_t recovery_dtbo_offset; /* offset to recovery dtbo/acpio in boot image */
	uint32_t header_size;
} __attribute__((packed));
