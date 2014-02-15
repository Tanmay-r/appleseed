
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2014 Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_MODELING_SHADERGROUP_SHADERPARAMPARSER_H
#define APPLESEED_RENDERER_MODELING_SHADERGROUP_SHADERPARAMPARSER_H

// appleseed.renderer headers.
#include "renderer/modeling/shadergroup/shaderparam.h"

// appleseed.foundation headers.
#include "foundation/core/exceptions/exception.h"
#include "foundation/utility/string.h"

// Standard headers.
#include <cstddef>
#include <string>
#include <vector>

namespace renderer
{

//
// An utility class to parse OSL shader parameter value strings.
//

struct ExceptionOSLParamParseError
  : public foundation::Exception
{
};

//
// An utility class to parse OSL shader parameter value strings.
//

class ShaderParamParser
{
  public:
    explicit ShaderParamParser(const std::string& string);

    OSLParamType param_type() const;

    float float_value();
    int int_value();
    
    void color_value(float& r, float& g, float& b);
    
  private:
    std::vector<std::string>                    m_tokens;
    OSLParamType                                m_param_type;
    std::vector<std::string>::const_iterator    m_tok_it;
    std::vector<std::string>::const_iterator    m_tok_end;

    template<class T>
    T convert_from_string(const std::string& s) const;
    
    template<class T>
    T parse_one_value(bool expect_end = false);
    
    template<class T>
    void parse_three_values(
        T& a, 
        T& b,
        T& c,
        bool parse_as_color = false);
};

//
// ShaderParamParser implementation.
//

inline OSLParamType ShaderParamParser::param_type() const
{
    return m_param_type;
}

template<class T>
T ShaderParamParser::convert_from_string(const std::string& s) const
{
    try
    {
        return foundation::from_string<T>(s);
    }
    catch(const foundation::ExceptionStringConversionError&)
    {
        throw ExceptionOSLParamParseError();
    }
}

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_SHADERGROUP_SHADERPARAM_H
