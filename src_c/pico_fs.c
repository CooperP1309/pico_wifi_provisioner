#include "pico_fs.h"
#include "pico_hal.h"            // pico file system lib

int picofs_init() {

    // attempt initial mount w/o formatting - expect mount fail on first startup (format req.)
    if (pico_mount(false) < 0) {
        printf("PicoFiles: failed to mount file system - commencing formatting...\n");
        
        // reattempt with formatting on first fail
        if (pico_mount(true) < 0) {
            printf("PicoFiles: formatted mount failed - aborting...\n");
            return -1;
        }
    }

    printf("PicoFiles: file system mounted successfully\n");

    return 0;
}

int picofs_deinit() {

    if (pico_unmount() < 0) {
        printf("PicoFiles: unmounting failed\n");
        return -1;
    }

    printf("PicoFiles: unmounted successfully\n");

    return 0;
}

int picofs_read_file(const char* file_name, char* buffer, int buff_len) {

    // to handle first time startups, set flag create if not exists
    int fp = pico_open(file_name, LFS_O_RDWR | LFS_O_CREAT);
    
    if (fp < 0) {
        printf("PicoFiles: error opening file\n");
        return -1;
    }

    printf("PicoFiles: file opened successfully\n");
    
    // read to buffer (-1 buff len to preserve terminating null)
    int bytes_read = pico_read(fp, buffer, buff_len-1);

    if (bytes_read < 0) {
        printf("PicoFiles: error reading file\n");
        return -1;
    }

    buffer[bytes_read] = '\0';

    printf("PicoFiles: read %d bytes from file\n", bytes_read);

    if (pico_close(fp) < 0) {
        printf("PicoFiles: error closing file\n");
        return -1;
    }

    printf("PicoFiles: file closed\n");

    return 0;
}

int picofs_write_file(const char* file_name, char* buffer, int buf_len) {

    // truncate file data
    int fp = pico_open(file_name, LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
    
    if (fp < 0) {
        printf("PicoFiles: error opening file\n");
        return -1;
    }

    printf("PicoFiles: file opened successfully\n");
    
    // write from buffer
    int bytes_written = pico_write(fp, buffer, strnlen(buffer, buf_len));

    if (bytes_written < 0) {
        printf("PicoFiles: error writting to cache\n");
        return -1;
    }

    printf("PicoFiles: %d bytes written to file\n", bytes_written);

    if (pico_close(fp) < 0) {
        printf("PicoFiles: error closing file\n");
        return -1;
    }

    printf("PicoFiles: file closed\n");

    return 0;
}