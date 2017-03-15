#include "load.h"
#include "cell.h"
#include "generate-image.h"
#include <stdio.h>

int main(int argc, char*argv[])
{
    if (argc < 2)
    {
        return 0;
    }
    Solution* pSolution = load_grid(argv[1]);
    if (pSolution == NULL)
    {
        return 0;
    }
    
    int step_index = 0;
    char filename[64] = {0};
    for (step_index = 0; step_index < pSolution->steps; step_index++)
    {
        sprintf(filename, "./out/%d.ppm", step_index);
        write_image(filename, pSolution);
        next_generation(pSolution);
    }
    return 1;
}
