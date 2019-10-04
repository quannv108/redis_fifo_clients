#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <signal.h>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "hiredis/hiredis.h"

std::string timePointAsString(const std::chrono::system_clock::time_point &tp)
{
    auto ttime_t = std::chrono::system_clock::to_time_t(tp);
    auto tp_sec = std::chrono::system_clock::from_time_t(ttime_t);
    std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(tp - tp_sec);

    std::tm ttm;
    gmtime_r(&ttime_t, &ttm);

    char time_str[] = "yyyy.mm.dd.HH MM.SS.ffffff";
    char date_time_format[] = "%Y-%m-%d %H:%M:%S";

    strftime(time_str, strlen(time_str), date_time_format, &ttm);

    std::string result(time_str);
    result.append(".");
    if(ms.count() == 0) {
        result.append("000000");
    }
    else {
        char milli_buf[6];
        if(ms.count() > 999999) {
            result.append("999999");
        } else {
            sprintf(milli_buf, "%06ld", std::abs(ms.count()));
            result.append(std::string(milli_buf));
        }
    }

    return result;
}

void onMessage(redisContext *c, redisReply *r) {
    if(r == NULL) {
        printf("redis command error\n");
        throw std::runtime_error("reply null");
    }

    if (r->type == REDIS_REPLY_ARRAY) {
        // printf("received array len = %ld\n", r->elements);
        // for (int j = 0; j < r->elements; j++) {
            // printf("%u) %s\n", j, r->element[j]->str);
        // }
    } else if (r->type == REDIS_REPLY_INTEGER) {
        // printf("received int = %lld\n", r->integer);
    } else if (r->type == REDIS_REPLY_DOUBLE) {
        // printf("received double = %f\n", r->dval);
    } else if (r->type == REDIS_REPLY_STRING) {
        // printf("received str = %s\n", r->str);
    } else if(r->type == REDIS_REPLY_NIL) {
        // printf("received nil\n");
    } else {
        // printf("received type %d\n", r->type);
    }
}

int main()
{
    std::cout << "cpush starting...\n";
    const char *redis_host = std::getenv("HOST");
    int redis_port = 6379;

    redisContext *ctx = redisConnect(redis_host, redis_port);
    if (ctx == NULL || ctx->err) {
        if (ctx) {
            printf("Error: %s\n", ctx->errstr);
            // handle error
            return ctx->err;
        } else {
            printf("Can't allocate redis context\n");
            return -1;
        }
    }

    // redisReply *reply = (redisReply *) redisCommand(ctx, "keys %s", "*");
    // onMessage(ctx, reply);
    // freeReplyObject(reply);

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto now = std::chrono::system_clock::now();
        auto now_str = timePointAsString(now);
        printf("will push value %s\n", now_str.c_str());
        redisReply *reply = (redisReply *) redisCommand(ctx, "LPUSH abc %s", now_str.c_str());
        onMessage(ctx, reply);
        freeReplyObject(reply);
        std::cout.flush();
    }

    redisFree(ctx);
    ctx = NULL;
    return 0;
}