#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define LINE_CAPACITY 8U

struct LineParser {
    char line[LINE_CAPACITY];
    size_t length;
    int discarding;
    unsigned int completed;
    unsigned int overflowed;
};

static void parser_feed(struct LineParser *parser, uint8_t byte)
{
    if (byte == (uint8_t)'\n') {
        if (parser->discarding) {
            parser->discarding = 0;
            parser->length = 0U;
            return;
        }
        parser->line[parser->length] = '\0';
        printf("line: %s\n", parser->line);
        parser->length = 0U;
        parser->completed += 1U;
        return;
    }

    if (parser->discarding) return;

    if (parser->length + 1U >= LINE_CAPACITY) {
        parser->length = 0U;
        parser->discarding = 1;
        parser->overflowed += 1U;
        return;
    }
    parser->line[parser->length++] = (char)byte;
}

int main(void)
{
    struct LineParser parser = {0};
    const uint8_t first[] = {'O', 'N'};
    const uint8_t second[] = {'\n', 'O', 'F', 'F', '\n'};

    for (size_t i = 0; i < sizeof first; ++i) parser_feed(&parser, first[i]);
    for (size_t i = 0; i < sizeof second; ++i) parser_feed(&parser, second[i]);

    printf("completed=%u overflowed=%u\n", parser.completed, parser.overflowed);
    /* TRY: 输入超长行后再输入 OK\n，确认只输出 OK 且能够恢复。 */
    return 0;
}
