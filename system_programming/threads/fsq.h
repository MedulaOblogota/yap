typedef struct fsq_s fsq_t;

fsq_t *FSQCreate(size_t size);

void FSQDestroy(fsq_t *fsq);

int FSQEnqueue(fsq_t *fsq, int element);

int FSQDequeue(fsq_t *fsq);

int FSQIsEmpty(fsq_t *fsq);
