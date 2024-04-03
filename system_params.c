#include "headers/allheaders.h"

#define MAX_LINE_LENGTH 100

int parse_part_selected = 0; //window, button_assigning, button_assigning
//menu counter, window counter, button counter
Menu_qualities menu;
window_qualities window_assigning;
button_qualities button_assigning;


void assigning_position(char *str){
    if(parse_part_selected == 1){
        sscanf(str, "%d %d", &window_assigning.position.coordinates_x, &window_assigning.position.coordinates_y);
    }
    else{
        sscanf(str, "%d %d", &button_assigning.position.coordinates_x, &button_assigning.position.coordinates_y);
    }
}

void assigning_name(char *str){
    sscanf(str, "%s", &button_assigning.name);
}

void assigning_size(char *str, int flag){
    if(flag == 1){
        if(parse_part_selected == 1){
            sscanf(str, "%d", &window_assigning.width);
        }
        else if(parse_part_selected == 2){
            sscanf(str, "%d", &button_assigning.width);
        }
    }
    else if(flag == 2){
        if(parse_part_selected == 1){
            sscanf(str, "%d", &window_assigning.height);
        }
        else if(parse_part_selected == 2){
            sscanf(str, "%d", &button_assigning.height);
        }
    }
    else if(flag == 3){
        sscanf(str, "%d", &button_assigning.size);
    }
}

void assigning_color(char *str, int flag){
    if(flag == 1){
        if(parse_part_selected == 1){
            sscanf(str, "%d %d %d", &window_assigning.color.r, &window_assigning.color.g, &window_assigning.color.b);
        }
        else if (parse_part_selected == 2){
            sscanf(str, "%d %d %d", &button_assigning.color.r, &button_assigning.color.g, &button_assigning.color.b);
        }
    }
    if(flag == 2){
        sscanf(str, "%d %d %d", &button_assigning.highlight_colour.r, &button_assigning.highlight_colour.g, &button_assigning.highlight_colour.b);
    }
}

TokenType get_token_type(char *token) {
    if(strcmp(token, "WindowBegin") == 0){
        return WindowBegin;
    }
    else if(strcmp(token, "WindowEnd") == 0){
        return WindowEnd;
    }
    else if(strcmp(token, "ButtonBegin") == 0){
        return ButtonBegin;
    }
    else if(strcmp(token, "ButtonEnd") == 0){
        return ButtonEnd;
    }
    else if(strcmp(token, "HighlightColor") == 0){
        return HiglightColor;
    }
    else if(strcmp(token, "Color") == 0){
        return Color;
    }
    else if(strcmp(token, "Width") == 0){
        return Width;
    }
    else if(strcmp(token, "Height") == 0){
        return Height;
    }
    else if(strcmp(token, "Name") == 0){
        return Name;
    }
    else if(strcmp(token, "Position") == 0){
        return Position;
    }
    else if(strcmp(token, "Size") == 0){
        return Size;
    }
}

void parse_line(char *line) {
    Token token;
    char *token_str = strtok(line, "=\n");
    while (token_str != NULL) {
        token.type = get_token_type(token_str);
        strcpy(token.value, "");

        token_str = strtok(NULL, "=\n");

        if (token_str != NULL) {
            strcpy(token.value, token_str);
        }
        switch (token.type) {
            case MenuBegin:
                break;
            case MenuEnd:
                break;
            case WindowBegin:
                menu.windows_counter++;
                parse_part_selected = 1;
                break;
            case WindowEnd:
                menu.windows = (window_qualities*)realloc(menu.windows, sizeof(window_qualities) * menu.windows_counter);
                menu.windows[menu.windows_counter - 1] = window_assigning;
                menu.windows[menu.windows_counter-1].window_number = menu.windows_counter-1; 
                parse_part_selected = 0;
                break;
            case ButtonBegin:
                menu.buttons_counter++;
                parse_part_selected = 2;
                break;
            case ButtonEnd:
                menu.buttons = (button_qualities*)realloc(menu.buttons, sizeof(button_qualities) * menu.buttons_counter);
                menu.buttons[menu.buttons_counter - 1] = button_assigning;
                menu.buttons[menu.buttons_counter - 1].button_number = menu.buttons_counter-1;
                parse_part_selected = 0;
                break;
            case Color:
                assigning_color(token.value, 1);
                break;
            case HiglightColor:
                assigning_color(token.value, 2);
                break;
            case Name:
                assigning_name(token.value);
                break;
            case Width:
                assigning_size(token.value, 1);
                break;
            case Height:
                assigning_size(token.value, 2);
                break;
            case Size:
                assigning_size(token.value, 3);
                break;
            case Position:
                assigning_position(token.value);
                break;
            
        }

        token_str = strtok(NULL, "=\n");
    }
}

void system_open() {
    menu.buttons = (button_qualities*)malloc(sizeof(button_qualities));
    menu.windows = (window_qualities*)malloc(sizeof(window_qualities));
    menu.buttons_counter = 0;
    menu.windows_counter = 0;
}

void system_close() {
    free(menu.buttons);
    free(menu.windows);
}

Menu_qualities system_init() {
    FILE *file = fopen("menu_description.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        parse_line(line);
    }
    
    fclose(file);
    return menu;

}
