#ifndef FILTER_H
#define FILTER_H

int find_max(const int *pb, const int *pe, const int **max_i);
int find_min(const int *pb, const int *pe, const int **min_i);
int copy_arr(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif // FILTER_H
