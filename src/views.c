#include "views.h"

#include "mongoose.h"

void main_view(struct mg_connection *c, struct mg_http_message *hm) {
    mg_http_reply(c, 200, "", "{\"result\": \"%.*s\"}\n", (int)hm->uri.len,
                  hm->uri.ptr);
}
