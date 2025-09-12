
#include "debug.h"
#include "cub3D.h"
#include "parsing.h"

void print_struct_set(t_settings *set)
{
    printf("\n\nrp_no = %s\n",set->rp_no);
    printf("rp_so = %s\n",set->rp_so);
    printf("rp_we = %s\n",set->rp_we);
    printf("rp_ea = %s\n",set->rp_ea);
    printf("floor_r = %d\n",set->floor_r);
    printf("floor_g = %d\n",set->floor_g);
    printf("floor_b = %d\n",set->floor_b);
    printf("cell_r = %d\n",set->cell_r);
    printf("cell_g = %d\n",set->cell_g);
    printf("cell_b = %d\n",set->cell_b);
}

void print_map(t_settings *set)
{
    int i;

    i = 0;
    printf("map:\n\n");
    while (set->map[i])
    {
        printf("%s", set->map[i]);
        i++;
    }
}