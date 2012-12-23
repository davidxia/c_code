#include <stdlib.h>
/* #include "frames.h" */
#include "list.h"


int alloc_frame(List *frames) {
    int frame_number, *data;

    /* No frames available */
    if (list_size(frames) == 0)
        return -1;

    /* Free frame couldn't be retrieved */
    if (list_rem_next(frames, NULL, (void **)&data) != 0)
        return -1;

    /* Store number of available frames */
    frame_number = *data;
    free(data);
    return frame_number;
}


int free_frame(List *frames, int frame_number) {
    int *data;

    /* Allocate storage for the frame number */
    if ((data = (int *) malloc(sizeof(int))) == NULL)
        return -1;

    /* Put frame back in list of available frames */
    *data = frame_number;

    if (list_ins_next(frames, NULL, data) != 0)
        return -1;
    return 0;
}

