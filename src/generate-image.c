#include "generate-image.h"

bool write_image(const char* filename, Solution* pSolution)
{
    FILE *p_file = NULL;
    p_file = fopen(filename, "w");

    if (p_file == NULL)
    {
        return false;
    }
    
    fprintf(p_file, "P3\n%d %d\n255\n", pSolution->grid_width, pSolution->grid_hight);
    
    Cell_Node* pNode = pSolution->Head;

    int line = 0, column = 0;
    for(line = 0; line < pSolution->grid_hight; line++)
    {
        for(column = 0; column < pSolution->grid_width; column++)
        {
            if (pNode == NULL)
            {
                fprintf(p_file, "  0 0 0");
                continue;
            }
            if (line == pNode->cell_position.y &&
                    column == pNode->cell_position.x)
            {
                if (pNode->cell_status == DYING)
                {
                    fprintf(p_file, "  0 0 0");
                }
                else
                {
                    fprintf(p_file, "  0 0 230");
                }
                pNode = pNode->next_cell;
            }
            else
            {
                fprintf(p_file, "  0 0 0");
            }
        }
        fprintf(p_file, "\n");
    }

    fclose(p_file);
    return true;
}

