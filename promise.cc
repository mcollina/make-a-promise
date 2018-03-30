#include "napi.h"

class PromiseWrap : public Napi::ObjectWrap<PromiseWrap> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    PromiseWrap(const Napi::CallbackInfo& info);
    ~PromiseWrap();
    Napi::Promise::Deferred* deferred;

  private:
    static Napi::FunctionReference constructor;
    Napi::Value Resolve(const Napi::CallbackInfo& info);
    Napi::Value Reject(const Napi::CallbackInfo& info);
};

Napi::FunctionReference PromiseWrap::constructor;

Napi::Object PromiseWrap::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "PromiseWrap", {
    InstanceMethod("resolve", &PromiseWrap::Resolve),
    InstanceMethod("reject", &PromiseWrap::Reject),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("PromiseWrap", func);
  return exports;
}

PromiseWrap::PromiseWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<PromiseWrap>(info)  {
  const Napi::Env env = info.Env();

  this->deferred = new Napi::Promise::Deferred(env);

  Napi::Object obj = info.This().As<Napi::Object>();
  obj.Set("promise", deferred->Promise());
}

PromiseWrap::~PromiseWrap() {
  delete this->deferred;
}

Napi::Value PromiseWrap::Resolve(const Napi::CallbackInfo& info) {
  const Napi::Env env = info.Env();

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  deferred->Resolve(info[0]);

  return info.This();
}

Napi::Value PromiseWrap::Reject(const Napi::CallbackInfo& info) {
  const Napi::Env env = info.Env();

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  deferred->Reject(info[0]);

  return info.This();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return PromiseWrap::Init(env, exports);
}

NODE_API_MODULE(make_promise, Init)
