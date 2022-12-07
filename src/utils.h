//
//  utils.h
//  silmarils-unpacker
//

#pragma once

#include "config.h"

/// @brief Reads an u16 from file
/// @param fp file pointer
/// @param is_le zero if file is big-endian encoded, else little-endian
/// @return 16-bit value
u16         fread16(FILE * fp, u8 is_le);

/// @brief Reads an u32 from file
/// @param fp file pointer
/// @param is_le zero if file is big-endian encoded, else little-endian
/// @return 32-bit value
u32         fread32(FILE * fp, u8 is_le);

/// @brief Swaps a 16-bit value if its endianness is different than the host's
/// endianness
/// @param value 16-bit value to swap if needed
/// @param is_le zero if the input was read from a big-endian encoded file
/// @return The possibly swapped value
u16         swap16(u16 num, u8 is_le);

/// @brief Swaps a 32-bit value if its endianness is different than the host's
/// endianness
/// @param value 32-bit value to swap if needed
/// @param is_le zero if the input was read from a big-endian encoded file
/// @return The possibly swapped value
u32         swap32(u32 num, u8 is_le);

/// @brief Tells if host is little-endian
/// @return zero if host is big-endian
int         is_host_le(void);