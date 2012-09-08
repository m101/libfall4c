#ifndef DATA_MATRIX_H

#define DATA_MATRIX_H

long reedSolomonError (long data[], size_t i, long dataSum, long dataSumPonderated, long *i_error);
void RS_correctError (long data[], size_t i, long error, size_t i_error);

#endif
