// 
//  info.c
//  src/jbloader/helper/info.c
//  
//  Created 30/04/2023
//  jbloader (helper)
//

#include <jbloader.h>

int get_kflags() {
    struct kerninfo kinfo;
    int ret = get_kerninfo(&kinfo, RAMDISK);
    if (ret != 0) {
        fprintf(stderr, "%s %d\n", "Failed to read kerninfo:", ret);
        return ret;
    }
    char buf[16];
    snprintf(buf, 16, "%d\n", kinfo.flags);
    write(STDOUT_FILENO, &buf, strlen(buf) + 1);
    return 0;
}

int get_pflags() {
    struct paleinfo pinfo;
    int ret = get_paleinfo(&pinfo, RAMDISK);
    if (ret != 0) {
        fprintf(stderr, "%s %d\n", "Failed to read paleinfo:", ret);
        return ret;
    }
    char buf[16];
    snprintf(buf, 16, "%d\n", pinfo.flags);
    write(STDOUT_FILENO, &buf, strlen(buf) + 1);
    return 0;
}

int get_bmhash() {
    char hash[97];
    int ret = get_boot_manifest_hash(hash);
    if (ret != 0) {
        fprintf(stderr, "%s %d\n", "Failed to get boot manifest hash:", ret);
        return ret;
    }
 
    write(STDOUT_FILENO, &hash, strlen(hash) + 1);
    return 0;
}

int check_forcerevert() {
    struct kerninfo kinfo;
    int ret = get_kerninfo(&kinfo, RAMDISK);
    if (ret != 0) {
        fprintf(stderr, "%s %d\n", "Failed to read kerninfo:", ret);
        return ret;
    }

    return (kinfo.flags & checkrain_option_force_revert) != 0;
}

int check_rootful() {
    struct paleinfo pinfo;
    int ret = get_paleinfo(&pinfo, RAMDISK);
    if (ret != 0) {
        fprintf(stderr, "%s %d\n", "Failed to read paleinfo:", ret);
        return ret;
    }

    return (pinfo.flags & palerain_option_rootful) != 0;
}