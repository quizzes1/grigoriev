typedef enum TokenType {
    MenuBegin,
    MenuEnd,
    WindowBegin,
    WindowEnd,
    Button1Begin,
    Button1End,
    Button2Begin,
    Button2End,
    HiglightColor,
    Width,
    Height,
    Color,
    Name
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
    char name[100];
    rgb_colour color;
    rgb_colour highlight_colour;

} button_qualities;

typedef struct window_qualities{
    int height;
    int width;
    rgb_colour color;

} window_qualities;

typedef struct menu{
    window_qualities window;
    button_qualities button1;
    button_qualities button2;
} Menu_qualities;

void assigning_name(char *str);
void assigning_size(char *str, int flag);
void assigning_color(char *str, int flag);
TokenType get_token_type(char *token);
void parse_line(char *line);
Menu_qualities system_init();