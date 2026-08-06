#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define HEADER UINT8_C(0xaa)
#define PAYLOAD_MAX 4U

enum ParseState { WAIT_HEADER, READ_LENGTH, READ_BODY, READ_CHECKSUM };

struct Parser {
    enum ParseState state;
    uint8_t length;
    uint8_t body[PAYLOAD_MAX + 1U]; /* command + payload */
    size_t body_length;
    uint8_t sum;
    unsigned int frames;
    unsigned int errors;
};

static void parser_reset(struct Parser *parser)
{
    parser->state = WAIT_HEADER;
    parser->body_length = 0U;
    parser->sum = 0U;
}

static void parser_feed(struct Parser *parser, uint8_t byte)
{
    switch (parser->state) {
    case WAIT_HEADER:
        if (byte == HEADER) parser->state = READ_LENGTH;
        break;
    case READ_LENGTH:
        if (byte > PAYLOAD_MAX) {
            parser->errors += 1U;
            parser_reset(parser);
        } else {
            parser->length = byte;
            parser->sum = byte;
            parser->body_length = 0U;
            parser->state = READ_BODY;
        }
        break;
    case READ_BODY:
        parser->body[parser->body_length++] = byte;
        parser->sum = (uint8_t)(parser->sum + byte);
        if (parser->body_length == (size_t)parser->length + 1U)
            parser->state = READ_CHECKSUM;
        break;
    case READ_CHECKSUM:
        if (byte == parser->sum) parser->frames += 1U;
        else parser->errors += 1U;
        parser_reset(parser);
        if (byte == HEADER) parser->state = READ_LENGTH;
        break;
    }
}

int main(void)
{
    struct Parser parser = {0};
    const uint8_t stream[] = {
        0x00U, 0x55U,
        HEADER, 1U, 0x10U, 0x7fU, 0x90U,
        HEADER, 0U, 0x20U, 0x20U
    };

    for (size_t i = 0; i < sizeof stream; ++i) parser_feed(&parser, stream[i]);
    printf("frames=%u errors=%u\n", parser.frames, parser.errors);

    /* TRY: 构造错误长度和错误校验后紧跟正确帧的输入。 */
    return 0;
}
