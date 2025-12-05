#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char *argv[]) {
    const char *path = argv[1];
    DIR *dir = opendir(path);
    if (!dir) {
        perror("not a dir");
        return -1;
    }

    struct dirent *entry;
    char *files[4096]; // change this anytime, its currently the max.overflows could happen tho
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        files[count] = strdup(entry->d_name);
        count++;
    }

    closedir(dir);

    FILE* m3u;
    m3u = fopen("new.m3u","w"); // create file

    fprintf(m3u,"#EXTM3U\n");

    goto loop;

    loop:
        for(int i=0;i<count;i++){
            if (strstr(files[i], ".mp3") || strstr(files[i],".flac") || strstr(files[i],".wav") || strstr(files[i],".aiff") || strstr(files[i],".ogg") || strstr(files[i],".opus") || strstr(files[i],".m4a") || strstr(files[i],".mp2") || strstr(files[i],".mp1") || strstr(files[i],".3gp") ||strstr(files[i],".alac")) {
                //this is extremely messy. this is also case sensitive.
                printf("File %d is a music file\n",i);
                fprintf(m3u,"%s\n",files[i]);
            }else{
                printf("File %d is not a music file\n",i);
            }
        }

    //free everything from  memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }

    return 0;
}

