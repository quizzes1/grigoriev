typedef enum TokenType {
    MenuBegin,
    MenuEnd,
    WindowBegin,
    WindowEnd,
    ButtonBegin,
    ButtonEnd,
    HiglightColor,
    Width,
    Height,
    Color,
    Name,
    Position,
    Size
} TokenType;

typedef struct Token {
    TokenType type;
    char value[100];
} Token;

typedef struct rgb_colour{
    int r;
    int g;
    int b;
} rgb_colour;

typedef struct button_qualities{
    int height;
    int width;
    int size;
    char name[100];
    point position;
    rgb_colour color;
    rgb_colour highlight_colour;

} button_qualities;

typedef struct window_qualities{
    int height;
    int width;
    point position;
    rgb_colour color;

} window_qualities;

typedef struct Menu_qualities{
    int windows_counter;
    int buttons_counter;
    window_qualities* windows;
    button_qualities* buttons;
} Menu_qualities;

void assigning_name(char *str);
void assigning_position(char *str);
void assigning_size(char *str, int flag);
void assigning_color(char *str, int flag);
TokenType get_token_type(char *token);
void parse_line(char *line);
Menu_qualities system_init();
void system_open();
void system_close();