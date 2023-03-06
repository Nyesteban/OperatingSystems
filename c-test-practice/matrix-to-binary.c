#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int** m;
    FILE* f;
    int i, j, rows, cols, fd;

    f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Could not open file");
        return 1;
    }
    fscanf(f, "%d %d", &rows, &cols);

    m = malloc(rows*sizeof(int*)+4);
    for(i=0; i<rows; i++) {
        m[i] = malloc(sizeof(int*)+4);
        for(j=0; j<cols; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }
    fclose(f);

    fd = open(argv[2], O_CREAT | O_WRONLY, 00600);
    if(fd == -1) {
        perror("Could not open destination file");
        return 1;
    }
    write(fd, &rows, sizeof(rows));
    write(fd, &cols, sizeof(cols));
    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            write(fd, &m[i][j], sizeof(m[i][j]));
        }
    }
    close(fd);
    for(i=0; i<rows; i++) {
	   free(m[i]);
    }	    
    free(m);
    return 0;
}
