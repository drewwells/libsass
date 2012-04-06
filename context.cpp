#include "context.hpp"
#include <iostream>
using std::cerr; using std::endl;

namespace Sass {
  using std::pair;
  
  Context::Context()
  : global_env(Environment()),
    function_env(map<pair<string, size_t>, Function>()),
    source_refs(vector<char*>()),
    ref_count(0)
  {
    register_functions();
  }
  
  Context::~Context()
  {
    for (int i = 0; i < source_refs.size(); ++i) {
      delete[] source_refs[i];
    }
  }
  
  inline void Context::register_function(Function_Descriptor d, Implementation ip)
  {
    Function f(d, ip);
    function_env[pair<string, size_t>(f.name, f.parameters.size())] = f;
  }
  
  void Context::register_functions()
  {
    using namespace Functions;
    // RGB Functions
    register_function(rgb_descriptor,  rgb);
    register_function(rgba_4_descriptor, rgba_4);
    register_function(rgba_2_descriptor, rgba_2);
    register_function(red_descriptor, red);
    register_function(green_descriptor, green);
    register_function(blue_descriptor, blue);
    register_function(mix_2_descriptor, mix_2);
    register_function(mix_3_descriptor, mix_3);
    // HSL Functions
    register_function(invert_descriptor, invert);
    // Opacity Functions
    register_function(alpha_descriptor, alpha);
    register_function(opacity_descriptor, alpha);
    register_function(opacify_descriptor, opacify);
    register_function(fade_in_descriptor, opacify);
    register_function(transparentize_descriptor, transparentize);
    register_function(fade_out_descriptor, transparentize);
    // String Functions
    register_function(unquote_descriptor, unquote);
    register_function(quote_descriptor, quote);
    // Number Functions
    register_function(percentage_descriptor, percentage);
    register_function(round_descriptor, round);
    register_function(ceil_descriptor, ceil);
    register_function(floor_descriptor, floor);
    register_function(abs_descriptor, abs);
  }
  
}