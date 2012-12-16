#include <stdlib.h>
#include <string.h>

#include "event.h"
#include "events.h"
#include "queue.h"


int receive_event(Queue *events, const Event *event) {
    Event *new_event;

    if ((new_event = (Event *) malloc(sizeof(Event))) == NULL)
        return -1;

    /* Make copy of the event and enqueue it */
    memcpy(new_event, event, sizeof(Event));

    if (queue_enqueue(events, new_event) != 0)
        return -1;

    return 0;
}


int process_event(Queue *events, int (*dispatch)(Event *event)) {
    Event *event;

    /* No events to dispatch */
    if (queue_size(queue) == 0)
        return -1;
    else {
        /* Event couldn't be retrieved */
        if (queue_dequeue(events, (void **) &event) != 0)
            return -1;
        else {
            /* Call user-defined function to dispatch event */
            dispatch(event);
            free(event);
        }
    }

    return 0;
}

