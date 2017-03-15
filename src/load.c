#include "load.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Solution* load_grid(char* filename)
{
    FILE *p_file = NULL;
    p_file = fopen(filename, "r");

    if (p_file == NULL)
    {
        error(1, 0, "Cannot read file %s!\n", filename);
        return NULL;
    }

    int width = 0, height = 0, step = 0;
    int fscanf_result = fscanf(p_file, "%d %d", &width, &height);
    if (fscanf_result != 2)
    {
        fclose(p_file);
        return NULL;
    }

    fscanf_result = fscanf(p_file, "%d\n", &step);
    if (fscanf_result != 1)
    {
        fclose(p_file);
        return NULL;
    }

    Solution* pSolution = (Solution*)malloc(sizeof(Solution));
    pSolution->grid_width = width;
    pSolution->grid_hight = height;
    pSolution->steps = step;
    pSolution->Head = NULL;
    Cell_Node* pTail = NULL;

    int line_index = 0, column_index = 0;
    char c_result;
    for (line_index = 0; line_index < height; line_index++)
    {
        for (column_index = 0; column_index < width; column_index++)
        {
            fscanf_result = fscanf(p_file, "%c", &c_result);
            if (fscanf_result == EOF)
            {
                fclose(p_file);
                free(pSolution);
                return NULL;
            }
            if (c_result == 'o')
            {
                Cell_Node* pNode = (Cell_Node*)malloc(sizeof(Cell_Node));
                pNode->cell_status = NEWBORN;
                pNode->cell_position.x = column_index;
                pNode->cell_position.y = line_index;
                memset(pNode->cell_ngbs, 0, 8);
                pNode->next_cell = NULL;
                if (pTail != NULL)
                {
                    pTail->next_cell = pNode;
                }
                else
                {
                    pSolution->Head = pNode;
                }
                pTail = pNode;
            }
        }
        fscanf_result = fscanf(p_file, "%c", &c_result);
    }
    fclose(p_file);
    
    Cell_Node* ptmpNode = pSolution->Head;
    while (ptmpNode != NULL)
    {
        update_link_ngbs(pSolution->Head, ptmpNode);
        ptmpNode->cell_status = ALIVE;
        ptmpNode = ptmpNode->next_cell;
    }
    return pSolution;
}
