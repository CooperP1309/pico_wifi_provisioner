#ifndef PICO_FS_H
#define PICO_FS_H

class Pico_FS {
    public:
        int init();     // init > constructor: error checking and logic control
        int deinit();   // ^ ditto ^
};

int Pico_FS::init() {

    // attempt initial mount w/o formatting
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

int Pico_FS::deinit() {

    if (pico_unmount() < 0) {
        printf("PicoFiles: unmounting failed\n");
        return -1;
    }

    printf("PicoFiles: unmounted successfully\n");

    return 0;
}

#endif // PICO_FS_H