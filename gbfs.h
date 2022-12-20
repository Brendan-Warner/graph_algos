#pragma once

bool sort_grid_gbfs(const grid* node1, const grid* node2);

void shortest_path_GBFS(grid* gird_node, bool ouutput_file);

void GBFS_alg(int starth, int startc, int finishh, int finishc, int height, int width, int output, char walls, char waited, bool outputFile);

