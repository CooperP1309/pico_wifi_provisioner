#ifndef PICOFILES_H
#define PICOFILES_H

class PicoFiles {
    public:
        int init();

    private:

};

int PicoFiles::init() {

    // attempt initial mount w/o formatting
    if (pico_mount(false) < 0) {
        printf("PicoFiles: failed to mount file system - commencing formatting...\n");
        
        if (pico_mount(true) < 0) {
            printf("PicoFiles: formatted mount failed - aborting...\n");
            return -1;
        }
    }

    printf("PicoFiles: file system mounted successfully\n");

    if (pico_unmount() < 0) {
        printf("PicoFiles: unmounting failed\n");
    }

    printf("PicoFiles: unmounted successfully\n");
    
    return 0;
}



#endif // PICOFILES_H