#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message {
    char *text; /* Message 拥有该动态字符串。 */
};

static int message_init(struct Message *message, const char *text)
{
    size_t length = strlen(text);
    message->text = malloc(length + 1U);
    if (message->text == NULL) {
        return 0;
    }
    memcpy(message->text, text, length + 1U);
    return 1;
}

static void message_destroy(struct Message *message)
{
    free(message->text);
    message->text = NULL;
}

int main(void)
{
    struct Message message = {0};

    if (!message_init(&message, "device ready")) {
        return 1;
    }
    printf("%s\n", message.text);
    message_destroy(&message);

    /* TRY: 解释为什么直接复制 Message 会产生两个指向同一所有权资源的对象。 */
    return 0;
}
