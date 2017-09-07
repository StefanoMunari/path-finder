#include "../../core/ai.h"
#include "../../core/search/utils/searchable_type.h"
#include "../../core/utils/constants.h"
#include <list>
#include <stdlib.h>
#include <string>
#include <v8.h> // v8 Engine
#include <node.h> // Nodejs

using namespace v8;
using path_finder::AI;
using path_finder::SearchableType;
using std::list;
using std::map;
using std::pair;
using std::string;
using std::vector;

static AI * FS_ai_ = NULL;

static
char const * FS_root_path_ = getenv(PROJECT_ROOT);

static
const string
unwrap_string_(
  Isolate * isolate, const Handle<Object> object, const string& wrapper_name)
{
  Handle<Value> handle_value =
    object->Get(String::NewFromUtf8(isolate, wrapper_name.c_str()));

  v8::String::Utf8Value utf_value(handle_value);

  return std::string(*utf_value);
}

static
const uint32_t
unwrap_uint32_(
  Isolate * isolate, const Handle<Object> object, const string& wrapper_name)
{
  Handle<Value> handle_value =
              object->Get(String::NewFromUtf8(isolate, wrapper_name.c_str()));

  return (uint32_t)(handle_value->ToUint32()->Value());
}

static
const SearchableType
filter_algorithm_id_(const uint32_t algorithm)
{
  if(algorithm > 2)
    throw std::invalid_argument(
      "<NodeJS bindings>::AI_INTERFACE::find_path - invalid algorithm");
  return static_cast<SearchableType>(algorithm);
}

void
init(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  if(args.Length() == 1)
  {
    // get the current V8 instance
    Isolate * isolate = args.GetIsolate();

    // check env vars
    if(FS_root_path_ == NULL)
      throw std::invalid_argument(
        "<NodeJS bindings>::AI_INTERFACE::init - environment variable unset");

    // extract arguments
    const string data_path =
      unwrap_string_(isolate, args[0]->ToObject(), "data_path");
    const string f_name_prefix =
      unwrap_string_(isolate, args[0]->ToObject(), "filename_prefix");
    const string f_extension =
      unwrap_string_(isolate, args[0]->ToObject(), "filename_extension");

    // check arguments
    if(data_path.empty() || f_name_prefix.empty() || f_extension.empty())
      throw std::invalid_argument(
        "<NodeJS bindings>::AI_INTERFACE::init - arguments not specified");

    if(FS_ai_ != NULL)
      delete FS_ai_;

    // allocate a new AI instance on the heap
    FS_ai_ = new AI(data_path, f_name_prefix, f_extension);
  }
  else
    throw std::invalid_argument(
      "<NodeJS bindings>::AI_INTERFACE::init - invalid number of arguments");
}

void
find_path(const v8::FunctionCallbackInfo<v8::Value> & args)
{
  // get the current V8 instance
  Isolate * isolate = args.GetIsolate();

  if(args.Length() == 1)
  {
    // extract the needed parameters from args
    const string source =
      unwrap_string_(isolate, args[0]->ToObject(), "src");
    const string destination =
      unwrap_string_(isolate, args[0]->ToObject(), "dest");
    SearchableType algorithm =
      filter_algorithm_id_(
        unwrap_uint32_(isolate, args[0]->ToObject(), "algorithm"));

    // check arguments
    if(source.empty() || destination.empty())
      throw std::invalid_argument(
        "<NodeJS bindings>::AI_INTERFACE::find_path - arguments not specified");

    // find the path from source to destination using algorithm
    list<string> * path =
      FS_ai_->FindPath<string>(source, destination, algorithm);

    // copy the found path into the v8 JS path wrapper
    Local<Array> v8_path = v8::Array::New(isolate, path->size());
    {
      uint32_t v8_path_index = 0;
      for(const auto& element : *path)
      {
        v8_path->Set(v8_path_index,
          v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),element.c_str()));
        ++v8_path_index;
      }
    }

    // free resources
    delete path;

    // set the correct return value
    args.GetReturnValue().Set(v8_path);

  }
  else
    throw std::invalid_argument(
    "<NodeJS bindings>::AI_INTERFACE::find_path - invalid number of arguments");
}

// register the ai interface to make it callable from nodejs
void Init(Local<Object> exports)
{
  // register the ai method
  NODE_SET_METHOD(exports, "init", &init);
  // register the find_path method
  NODE_SET_METHOD(exports, "find_path", &find_path);
}

// associates the module name with the Init function
// which is called when the module if first loaded in a nodejs application
NODE_MODULE(ai_interface, Init);