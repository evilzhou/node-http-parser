#include <napi.h>
#include "http_parser.h"

using namespace Napi;

Value Parse(const CallbackInfo& args) {
    Env env = args.Env();
    if (args.Length() != 1) {
        TypeError::New(env, "args length != 1").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if (!args[0].IsObject()) {
        TypeError::New(env, "args[0] must be Object").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    auto argObj = args[0].ToObject();
    if (argObj.IsNull()) {
        TypeError::New(env, "args[0] must not be null").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    auto buffer = argObj.Get("buffer");
    if (!buffer.IsBuffer()) {
        TypeError::New(env, "args[0].buffer must be Buffer").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    http_parser parser;
    http_parser_init(&parser, HTTP_BOTH);
    parser.data = &argObj;
    http_parser_settings setting;
    http_parser_settings_init(&setting);
    setting.on_message_begin = [](http_parser* parser)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_message_begin = argObj.Get("on_message_begin");
        if (!on_message_begin.IsUndefined() && on_message_begin.IsFunction()) {
            on_message_begin.As<Function>().Call(argObj, {});
        }
        return 0;
    };
    setting.on_url = [](http_parser* parser, const char* at, size_t length)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_url = argObj.Get("on_url");
        if (!on_url.IsUndefined() && on_url.IsFunction()) {
            on_url.As<Function>().Call(argObj, { String::New(env, at, length) });
        }
        return 0;
    };
    setting.on_status = [](http_parser* parser, const char* at, size_t length)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_status = argObj.Get("on_status");
        if (!on_status.IsUndefined() && on_status.IsFunction()) {
            on_status.As<Function>().Call(argObj, { String::New(env, at, length) });
        }
        return 0;
    };
    setting.on_header_field = [](http_parser* parser, const char* at, size_t length)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_header_field = argObj.Get("on_header_field");
        if (!on_header_field.IsUndefined() && on_header_field.IsFunction()) {
            on_header_field.As<Function>().Call(argObj, { String::New(env, at, length) });
        }
        return 0;
    };
    setting.on_header_value = [](http_parser* parser, const char* at, size_t length)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_header_value = argObj.Get("on_header_value");
        if (!on_header_value.IsUndefined() && on_header_value.IsFunction()) {
            on_header_value.As<Function>().Call(argObj, { String::New(env, at, length) });
        }
        return 0;
    };
    setting.on_headers_complete = [](http_parser* parser)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_headers_complete = argObj.Get("on_headers_complete");
        if (!on_headers_complete.IsUndefined() && on_headers_complete.IsFunction()) {
            on_headers_complete.As<Function>().Call(argObj, {});
        }
        return 0;
    };
    setting.on_body = [](http_parser* parser, const char* at, size_t length)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_body = argObj.Get("on_body");
        if (!on_body.IsUndefined() && on_body.IsFunction()) {
            on_body.As<Function>().Call(argObj, { Buffer<char>::New(env, (char*)at, length) });
        }
        return 0;
    };
    setting.on_message_complete = [](http_parser* parser)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_message_complete = argObj.Get("on_message_complete");
        if (!on_message_complete.IsUndefined() && on_message_complete.IsFunction()) {
            on_message_complete.As<Function>().Call(argObj, {});
        }
        return 0;
    };
    setting.on_chunk_header = [](http_parser* parser)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_chunk_header = argObj.Get("on_chunk_header");
        if (!on_chunk_header.IsUndefined() && on_chunk_header.IsFunction()) {
            on_chunk_header.As<Function>().Call(argObj, {});
        }
        return 0;
    };
    setting.on_chunk_complete = [](http_parser* parser)->int {
        auto argObj = *(Object*)parser->data;
        auto env = argObj.Env();
        auto on_chunk_complete = argObj.Get("on_chunk_complete");
        if (!on_chunk_complete.IsUndefined() && on_chunk_complete.IsFunction()) {
            on_chunk_complete.As<Function>().Call(argObj, {});
        }
        return 0;
    };
    http_parser_execute(&parser, &setting, buffer.As<Buffer<const char>>().Data(), buffer.As<Buffer<const char>>().ByteLength());

    return Number::From(env, parser.http_errno);
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "parse"), Function::New(env, Parse));
    return exports;
}

NODE_API_MODULE(addon, Init)