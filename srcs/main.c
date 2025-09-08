#include <unistd.h> //write
#include "parsing.h"


//We init them at those value for further processing in the parsing
static void init_struct_value(t_settings *set)
{
    set->buff = NULL;
    set->rp_no = NULL;
    set->rp_so = NULL;
    set->rp_we = NULL;
    set->rp_ea = NULL;
    set->cell_r = NONE_ASSIGNED;
    set->cell_g = NONE_ASSIGNED;
    set->cell_b = NONE_ASSIGNED;
    set->floor_r = NONE_ASSIGNED;
    set->floor_g = NONE_ASSIGNED;
    set->floor_b = NONE_ASSIGNED;
    set->error_type = NONE_ASSIGNED;
}
static void free_all(t_settings *set)
{
    if(set->buff)
        free(set->buff);
    if(set->rp_no)
        free(set->rp_no);
    if(set->rp_so)
        free(set->rp_so);
    if(set->rp_we)
        free(set->rp_we);
    if(set->rp_ea)
        free(set->rp_ea);
    get_next_line(-1);
}

//TODO at the end of the project we still need to check if the info are still valid!
static int error_msg_handler(int error_type, t_settings *set)
{
    if(error_type == MALLOC_ERROR_SET)
        write(2, "Main:33 error during malloc of set\n", 35);
    if(error_type == PARSING_NBR_ARGC)
        write(2,"parsing:23 invalid argc value, cub3D require a single and only arg\n", 67);
    if(error_type == PARSING_FILE_EXTENSION)
        write(2,"parsing:28 invalid file's extension cub3d only support .cub files as arg\n",73);
    if(error_type == PARSING_CANT_OPEN_FILE)
        write(2,"parsing:33 parsing_file:53 Error while opening file be sure the file exist in scene_descriptions folder\n", 104);
    if(error_type == MALLOC_ERROR_BUFFER)
        write(2,"parsing_file:41 Malloc error during buff setup\n", 47);
    if(error_type == PARSING_ELEMENT_INVALID_CONTENT)
        write(2,"Invalid .cub format, make sure it follow the expected form\n", 59);
    if(error_type == PARSING_READ_FAILURE)
        write(2,"a read function failed, it may be because of incorrect format or reaching EOF during element collects\n", 102);
    if(set)
    {
        free_all(set);
        free(set);
        set = NULL;
    }
        
    return(error_type);
}

//TODO FREE CONTENT STRUCT?

int main(int argc, char *argv[])
{
    t_settings *set;

    set = malloc(sizeof(t_settings));
    if(!set)
        return(error_msg_handler(MALLOC_ERROR_SET, NULL));
    init_struct_value(set);
    if(parsing(argc, argv, set))
        return(error_msg_handler(set->error_type, set));
    print_struct_set(set); //DEBUG function to see content of struct set

    
    
    //-------------------------------------------------------
    //--------------PSEUDOCODE-------------------------------
    //-------------------------------------------------------
    //init structures/data
        //if fail return error with right msg + free close
    //init minilibx + I guess the controls? 
        //if fail return error with right msg + free/close
    //running part
    //-------------------------------------------------------
    //--------------PSEUDOCODE-------------------------------
    //-------------------------------------------------------
    free_all(set);
    free(set);
    write(1, "return Success\n", 15);
    return (EXIT_SUCCESS);
}