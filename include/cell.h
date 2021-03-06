#ifndef __CELL_H__
#define __CELL_H__

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    ALIVE,
    NEWBORN,
    DYING
} status;
typedef struct Position {
    int x;
    int y;
} Pos;
typedef struct Cell {
    status cell_status;
    Pos cell_position;
    bool cell_ngbs[8];   
    struct Cell* next_cell;
} Cell_Node;
typedef struct Problem
{
    int grid_width;
    int grid_hight;
    int steps;
    Cell_Node* Head;
} Solution;

void next_generation(Solution* pSolution);
int get_ngbs_index(int x, int y);
Pos get_ngbs_position(Cell_Node* pNode, int index);
bool will_newborn(Cell_Node* pHead, Pos curPos, bool ngbs_status[]);
bool is_neighbor(Pos firstPos, Pos secondPos);
bool is_dying_cnt(int cnt);
bool is_alive_cnt(int cnt);
void update_link_ngbs(Cell_Node* pHead, Cell_Node* pNode);
Cell_Node* insert_node_in_link(Cell_Node* pHead, Cell_Node* pNode);

#endif
