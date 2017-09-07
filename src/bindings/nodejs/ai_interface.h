#ifndef AI_INTERFACE_H
#define AI_INTERFACE_H

#include <v8.h>
#include <node.h>

void init(const v8::FunctionCallbackInfo<v8::Value> &);
void find_path(const v8::FunctionCallbackInfo<v8::Value> &);

#endif /*AI_INTERFACE_H*/