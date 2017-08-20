/*
 *      Copyright (C) 2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "RarchTranslator.h"

#include <cstring>
#include <malloc.h>

SHADER_SCALE_TYPE CRarchTranslator::TranslateScaleType(enum gfx_scale_type type)
{
  switch (type)
  {
  case RARCH_SCALE_INPUT:
    return SHADER_SCALE_TYPE_INPUT;
  case RARCH_SCALE_ABSOLUTE:
    return SHADER_SCALE_TYPE_ABSOLUTE;
  case RARCH_SCALE_VIEWPORT:
    return SHADER_SCALE_TYPE_VIEWPORT;
  default:
    break;
  }

  return SHADER_SCALE_TYPE_INPUT;
}

enum gfx_scale_type CRarchTranslator::TranslateScaleType(SHADER_SCALE_TYPE type)
{
  switch (type)
  {
  case SHADER_SCALE_TYPE_INPUT:
    return RARCH_SCALE_INPUT;
  case SHADER_SCALE_TYPE_ABSOLUTE:
    return RARCH_SCALE_ABSOLUTE;
  case SHADER_SCALE_TYPE_VIEWPORT:
    return RARCH_SCALE_VIEWPORT;
  default:
    break;
  }

  return RARCH_SCALE_INPUT;
}

SHADER_FILTER_TYPE CRarchTranslator::TranslateFilterType(unsigned int type)
{
  switch (type)
  {
  case RARCH_FILTER_UNSPEC:
    return SHADER_FILTER_TYPE_UNSPEC;
  case RARCH_FILTER_LINEAR:
    return SHADER_FILTER_TYPE_LINEAR;
  case RARCH_FILTER_NEAREST:
    return SHADER_FILTER_TYPE_NEAREST;
  default:
    break;
  }

  return SHADER_FILTER_TYPE_UNSPEC;
}

unsigned int CRarchTranslator::TranslateFilterType(SHADER_FILTER_TYPE type)
{
  switch (type)
  {
  case SHADER_FILTER_TYPE_UNSPEC:
    return RARCH_FILTER_UNSPEC;
  case SHADER_FILTER_TYPE_LINEAR:
    return RARCH_FILTER_LINEAR;
  case SHADER_FILTER_TYPE_NEAREST:
    return RARCH_FILTER_NEAREST;
  default:
    break;
  }

  return RARCH_FILTER_UNSPEC;
}

SHADER_WRAP_TYPE CRarchTranslator::TranslateWrapType(enum gfx_wrap_type type)
{
  switch (type)
  {
  case RARCH_WRAP_BORDER:
    return SHADER_WRAP_TYPE_BORDER;
  case RARCH_WRAP_EDGE:
    return SHADER_WRAP_TYPE_EDGE;
  case RARCH_WRAP_REPEAT:
    return SHADER_WRAP_TYPE_REPEAT;
  case RARCH_WRAP_MIRRORED_REPEAT:
    return SHADER_WRAP_TYPE_MIRRORED_REPEAT;
  default:
    break;
  }

  return SHADER_WRAP_TYPE_BORDER;
}

enum gfx_wrap_type CRarchTranslator::TranslateWrapType(SHADER_WRAP_TYPE type)
{
  switch (type)
  {
  case SHADER_WRAP_TYPE_BORDER:
    return RARCH_WRAP_BORDER;
  case SHADER_WRAP_TYPE_EDGE:
    return RARCH_WRAP_EDGE;
  case SHADER_WRAP_TYPE_REPEAT:
    return RARCH_WRAP_REPEAT;
  case SHADER_WRAP_TYPE_MIRRORED_REPEAT:
    return RARCH_WRAP_MIRRORED_REPEAT;
  default:
    break;
  }

  return RARCH_WRAP_DEFAULT;
}

void CRarchTranslator::TranslateShaderPass(const rarch_video_shader_pass &rarch_pass, video_shader_pass &pass)
{
  pass.source_path = nullptr;
  if (rarch_pass.source.path != nullptr)
  {
    const unsigned int source_path_len = std::strlen(rarch_pass.source.path);
    if (source_path_len > 0)
    {
      pass.source_path = new char[source_path_len];
      std::strcpy(pass.source_path, rarch_pass.source.path);
    }
  }

  pass.vertex_source = nullptr;
  if (rarch_pass.source.string.vertex != nullptr)
  {
    const unsigned int vertex_source_len = std::strlen(rarch_pass.source.string.vertex);
    if (vertex_source_len > 0)
    {
      pass.vertex_source = new char[vertex_source_len];
      std::strcpy(pass.vertex_source, rarch_pass.source.string.vertex);
    }
  }

  pass.fragment_source = nullptr;
  if (rarch_pass.source.string.fragment != nullptr)
  {
    const unsigned int fragment_source_len = std::strlen(rarch_pass.source.string.fragment);
    if (fragment_source_len > 0)
    {
      pass.fragment_source = new char[fragment_source_len];
      std::strcpy(pass.fragment_source, rarch_pass.source.string.fragment);
    }
  }

  auto &fbo = pass.fbo;
  auto &rarch_fbo = rarch_pass.fbo;

  fbo.fp_fbo = rarch_fbo.fp_fbo;
  fbo.srgb_fbo = rarch_fbo.srgb_fbo;
  fbo.scale_x.type = TranslateScaleType(rarch_fbo.type_x);
  fbo.scale_y.type = TranslateScaleType(rarch_fbo.type_y);
  switch (fbo.scale_x.type)
  {
  case SHADER_SCALE_TYPE_ABSOLUTE:
    fbo.scale_x.abs = rarch_fbo.abs_x;
    break;
  default:
    fbo.scale_x.scale = rarch_fbo.scale_x;
    break;
  }
  switch (fbo.scale_y.type)
  {
  case SHADER_SCALE_TYPE_ABSOLUTE:
    fbo.scale_y.abs = rarch_fbo.abs_y;
    break;
  default:
    fbo.scale_y.scale = rarch_fbo.scale_y;
    break;
  }

  pass.filter = TranslateFilterType(rarch_pass.filter);
  pass.wrap = TranslateWrapType(rarch_pass.wrap);
  pass.frame_count_mod = rarch_pass.frame_count_mod;
  pass.mipmap = rarch_pass.mipmap;
}

void CRarchTranslator::TranslateShaderPass(const video_shader_pass &pass, rarch_video_shader_pass &rarch_pass)
{
  rarch_pass.source.path[0] = '\0';
  if (pass.source_path != nullptr)
    std::strcpy(rarch_pass.source.path, pass.source_path);

  rarch_pass.source.string.vertex = nullptr;
  if (pass.vertex_source != nullptr)
  {
    unsigned int vertex_len = std::strlen(pass.vertex_source);
    rarch_pass.source.string.vertex = static_cast<char*>(malloc(vertex_len));
    std::strcpy(rarch_pass.source.string.vertex, pass.vertex_source);
  }

  rarch_pass.source.string.fragment = nullptr;
  if (pass.fragment_source != nullptr)
  {
    unsigned int fragment_len = std::strlen(pass.fragment_source);
    rarch_pass.source.string.fragment = static_cast<char*>(malloc(fragment_len));
    std::strcpy(rarch_pass.source.string.fragment, pass.fragment_source);
  }

  rarch_pass.alias[0] = '\0';

  auto &rarch_fbo = rarch_pass.fbo;
  auto &fbo = pass.fbo;

  rarch_fbo.fp_fbo = fbo.fp_fbo;
  rarch_fbo.srgb_fbo = fbo.srgb_fbo;
  rarch_fbo.type_x = TranslateScaleType(fbo.scale_x.type);
  rarch_fbo.type_y = TranslateScaleType(fbo.scale_y.type);
  switch (rarch_fbo.type_x)
  {
  case RARCH_SCALE_ABSOLUTE:
    rarch_fbo.abs_x = fbo.scale_x.abs;
    break;
  default:
    rarch_fbo.scale_x = fbo.scale_x.scale;
    break;
  }
  switch (fbo.scale_y.type)
  {
  case RARCH_SCALE_ABSOLUTE:
    rarch_fbo.abs_y = fbo.scale_y.abs;
    break;
  default:
    rarch_fbo.scale_y = fbo.scale_y.scale;
    break;
  }

  rarch_pass.filter = TranslateFilterType(pass.filter);
  rarch_pass.wrap = TranslateWrapType(pass.wrap);
  rarch_pass.frame_count_mod = pass.frame_count_mod;
  rarch_pass.mipmap = pass.mipmap;
}

void CRarchTranslator::TranslateShaderLut(const rarch_video_shader_lut &rarch_lut, video_shader_lut &lut)
{
  lut.id = nullptr;
  unsigned int id_len = std::strlen(rarch_lut.id);
  if (id_len > 0)
  {
    lut.id = new char[id_len];
    std::strcpy(lut.id, rarch_lut.id);
  }

  lut.path = nullptr;
  unsigned int path_len = std::strlen(rarch_lut.path);
  if (path_len > 0)
  {
    lut.path = new char[path_len];
    std::strcpy(lut.path, rarch_lut.path);
  }

  lut.filter = TranslateFilterType(rarch_lut.filter);
  lut.wrap = TranslateWrapType(rarch_lut.wrap);
  lut.mipmap = rarch_lut.mipmap;
}

void CRarchTranslator::TranslateShaderLut(const video_shader_lut &lut, rarch_video_shader_lut &rarch_lut)
{
  rarch_lut.id[0] = '\0';
  if (lut.id != nullptr)
    std::strcpy(rarch_lut.id, lut.id);

  rarch_lut.path[0] = '\0';
  if (lut.path != nullptr)
    std::strcpy(rarch_lut.path, lut.path);

  rarch_lut.filter = TranslateFilterType(lut.filter);
  rarch_lut.wrap = TranslateWrapType(lut.wrap);
  rarch_lut.mipmap = lut.mipmap;
}

void CRarchTranslator::TranslateShaderParameter(const rarch_video_shader_parameter &rarch_param, video_shader_parameter &param)
{
  param.id = nullptr;
  unsigned int id_len = std::strlen(rarch_param.id);
  if (id_len > 0)
  {
    param.id = new char[id_len];
    std::strcpy(param.id, rarch_param.id);
  }

  param.desc = nullptr;
  unsigned int desc_len = std::strlen(rarch_param.desc);
  if (desc_len > 0)
  {
    param.desc = new char[desc_len];
    std::strcpy(param.desc, rarch_param.desc);
  }

  param.current = rarch_param.current;
  param.minimum = rarch_param.minimum;
  param.initial = rarch_param.initial;
  param.maximum = rarch_param.maximum;
  param.step = rarch_param.step;
}

void CRarchTranslator::TranslateShaderParameter(const video_shader_parameter &param, rarch_video_shader_parameter &rarch_param)
{
  rarch_param.id[0] = '\0';
  if (param.id != nullptr)
    std::strcpy(rarch_param.id, param.id);

  rarch_param.desc[0] = '\0';
  if (param.desc != nullptr)
    std::strcpy(rarch_param.desc, param.desc);

  rarch_param.current = param.current;
  rarch_param.minimum = param.minimum;
  rarch_param.initial = param.initial;
  rarch_param.maximum = param.maximum;
  rarch_param.step = param.step;
}

void CRarchTranslator::TranslateShader(const rarch_video_shader &rarch_shader, video_shader &shader)
{
  shader.pass_count = rarch_shader.passes;
  shader.passes = nullptr;
  if (shader.pass_count > 0)
  {
    shader.passes = new video_shader_pass[shader.pass_count];
    for (unsigned int i = 0; i < shader.pass_count; i++)
      TranslateShaderPass(rarch_shader.pass[i], shader.passes[i]);
  }

  shader.lut_count = rarch_shader.luts;
  shader.luts = nullptr;
  if (shader.lut_count > 0)
  {
    shader.luts = new video_shader_lut[shader.lut_count];
    for (unsigned int i = 0; i < shader.lut_count; i++)
      TranslateShaderLut(rarch_shader.lut[i], shader.luts[i]);
  }

  shader.parameter_count = rarch_shader.num_parameters;
  shader.parameters = nullptr;
  if (shader.parameter_count > 0)
  {
    shader.parameters = new video_shader_parameter[shader.parameter_count];
    for (unsigned int i = 0; i < shader.parameter_count; i++)
      TranslateShaderParameter(rarch_shader.parameters[i], shader.parameters[i]);
  }
}

void CRarchTranslator::TranslateShader(const video_shader &shader, rarch_video_shader &rarch_shader)
{
  rarch_shader.type = RARCH_SHADER_NONE; //! @todo

  rarch_shader.modern = false;
  rarch_shader.prefix[0] = '\0';

  rarch_shader.passes = shader.pass_count;
  for (unsigned int i = 0; i < rarch_shader.passes; i++)
    TranslateShaderPass(shader.passes[i], rarch_shader.pass[i]);

  rarch_shader.luts = shader.lut_count;
  for (unsigned int i = 0; i < rarch_shader.luts; i++)
    TranslateShaderLut(shader.luts[i], rarch_shader.lut[i]);

  rarch_shader.num_parameters = shader.parameter_count;
  for (unsigned int i = 0; i < rarch_shader.num_parameters; i++)
    TranslateShaderParameter(shader.parameters[i], rarch_shader.parameters[i]);

  rarch_shader.variables = 0;
  rarch_shader.script_path[0] = '\0';
  rarch_shader.script = nullptr;
  rarch_shader.script_class[0] = '\0';
  rarch_shader.feedback_pass = -1;
}

void CRarchTranslator::FreeShader(rarch_video_shader &rarch_shader)
{
  for (unsigned int i = 0; i < rarch_shader.passes; i++)
  {
    auto &rarch_pass = rarch_shader.pass[i];

    free(rarch_pass.source.string.vertex);
    if (rarch_pass.source.string.vertex != rarch_pass.source.string.fragment)
      free(rarch_pass.source.string.fragment);

    rarch_pass.source.string.vertex = nullptr;
    rarch_pass.source.string.fragment = nullptr;
  }
}
