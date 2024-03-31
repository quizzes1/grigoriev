#include "headers/allheaders.h"

#define MAX_LINE_LENGTH 100

int parse_part_selected = 0; //window, button1, button2

window_qualities window;
button_qualities button1;
button_qualities button2;

void assigning_position(char *str){
    if(parse_part_selected == 2){
        sscanf(str, "%d %d", &button1.position.coordinates_x, &button1.position.coordinates_y);
    }
    else{
        sscanf(str, "%d %d", &button2.position.coordinates_x, &button2.position.coordinates_y);
    }
}

void assigning_name(char *str){
    
    if(parse_part_selected == 2){
        sscanf(str, "%s", &button1.name);
    }
    else{
        sscanf(str, "%s", &button2.name);
    }
}

void assigning_size(char *str, int flag){
    if(flag == 1){
        if(parse_part_selected == 1){
            sscanf(str, "%d", &window.width);
        }
        else if(parse_part_selected == 2){
            sscanf(str, "%d", &button1.width);
        }
        else if(parse_part_selected == 3){
            sscanf(str, "%d", &button2.width);
        }
    }
    else if(flag == 2){
        if(parse_part_selected == 1){
            sscanf(str, "%d", &window.height);
        }
        else if(parse_part_selected == 2){
            sscanf(str, "%d", &button1.height);
        }
        else if(parse_part_selected == 3){
            sscanf(str, "%d", &button2.height);
        }
    }
}

void assigning_color(char *str, int flag){
    if(flag == 1){
        if(parse_part_selected == 1){
            sscanf(str, "%d %d %d", &window.color.r, &window.color.g, &window.color.b);
        }
        else if (parse_part_selected == 2){
            sscanf(str, "%d %d %d", &button1.color.r, &button1.color.g, &button1.color.b);
        }
        else if (parse_part_selected == 3){
            sscanf(str, "%d %d %d", &button2.color.r, &button2.color.g, &button2.color.b);
        }
    }
    if(flag == 2){
        if (parse_part_selected == 2){
            sscanf(str, "%d %d %d", &button1.highlight_colour.r, &button1.highlight_colour.g, &button1.highlight_colour.b);
        }
        else if (parse_part_selected == 3){
            sscanf(str, "%d %d %d", &button2.highlight_colour.r, &button2.highlight_colour.g, &button2.highlight_colour.b);
        }
    }
}

TokenType get_token_type(char *token) {
    if(strcmp(token, "WindowBegin") == 0){
        return WindowBegin;
    }
    else if(strcmp(token, "WindowEnd") == 0){
        return WindowEnd;
    }
    else if(strcmp(token, "Button1Begin") == 0){
        return Button1Begin;
    }
    else if(strcmp(token, "Button1End") == 0){
        return Button1End;
    }
    else if(strcmp(token, "Button2Begin") == 0){
        return Button2Begin;
    }
    else if(strcmp(token, "Button2End") == 0){
        return Button2End;
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
}

void parse_line(char *line) {
    Token token;
    char *token_str = strtok(line, "=\n");
    while (token_str != NULL) {
        token.type = get_token_type(token_str);
        strcpy(token.value, "");

        token_str = strtok(NULL, "=");

        if (token_str != NULL) {
            strcpy(token.value, token_str);
        }
        switch (token.type) {
            case MenuBegin:
                break;
            case MenuEnd:
                break;
            case WindowBegin:
                parse_part_selected = 1;
                break;
            case WindowEnd:
                parse_part_selected = 0;
                break;
            case Button1Begin:
                parse_part_selected = 2;
                break;
            case Button1End:
                parse_part_selected = 0;
                break;
            case Button2Begin:
                parse_part_selected = 3;
                break;
            case Button2End:
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
            case Position:
                assigning_position(token.value);
                break;
        }

        token_str = strtok(NULL, "=");
    }
}

Menu_qualities system_init() {
    FILE *file = fopen("menu_description.txt", "r");
    Menu_qualities menu;
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        parse_line(line);
    }
    menu.button1 = button1;
    menu.window = window;
    menu.button2 = button2;
    fclose(file);
    return menu;
}
