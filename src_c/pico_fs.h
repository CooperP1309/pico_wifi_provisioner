#ifndef PICO_FS_H
#define PICO_FS_H

// Mount pico file system
//
// Initially assumes flash fs is pre-formatted.
// Recalls mount with formatting enabled if first call fails.
// returns 0 on success, -1 on mount fail
int picofs_init();

// Demount pico file system
//
// Demount call with layered value checking
int picofs_deinit();

// Read pico files
//
// Declares
// Returns bytes read.
int picofs_read_file(const char* file_name, char* buffer, int buff_len);

int picofs_write_file(const char* file_name, char* buffer, int buf_len);

#endif // PICO_FS_H