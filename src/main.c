#include <jansson.h>

#include "mongoose.h"
#include "router.h"
#include "setting.h"
#include "util.h"
#include "views.h"

static const char *s_http_addr = HTTP_SERVICE_URL;  // HTTP port
// static const char *s_https_addr = "https://0.0.0.0:8443";  // HTTPS port
static const char *s_root_dir = ".";

static Router *router;

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        if (mg_http_match_uri(hm, "/api/user")) {
            char msg[256] = "";
            char method[8] = "";
            strncpy(method, hm->method.ptr, hm->method.len);
            sprintf(msg, "{\"METHOD\": \"%s\", \"METHODLEN\": \"%ld\"}\n",
                    method, hm->method.len);
            mg_http_reply(c, 200, "", msg);
        }

        for (size_t i = 0; i < router->length; i++) {
            if (mg_http_match_uri(hm, get_uri(router, i))) {
                get_route(router, i)(c, hm);
            }
        }
    }
    (void)fn_data;
}

int main(void) {
    struct mg_mgr mgr;  // Event manager

    router = initialize_router();
    push_new_route(router, "/api/hoge", main_view);

    // Set log level
    mg_log_set(VERBOSE ? MG_LL_VERBOSE : (DEBUG ? MG_LL_DEBUG : MG_LL_INFO));

    mg_mgr_init(&mgr);                            // Initialise event manager
    mg_http_listen(&mgr, s_http_addr, fn, NULL);  // Create HTTP listener
    // mg_http_listen(&mgr, s_https_addr, fn, (void *)1);  // HTTPS listener

    for (;;) mg_mgr_poll(&mgr, 1000);  // Infinite event loop

    mg_mgr_free(&mgr);

    finalize_router(router);

    return 0;
}
