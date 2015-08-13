//
//  flShaders.cpp
//  JINS MEME GL Dev
//
//  Created by YoshitoONISHI on 5/15/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include "flShaders.h"

FL_NAMESPACE_BEGIN

const char* kShaderSingleColorVert = STRINGIFY
(
 attribute vec4 position;
 
 varying lowp vec4 colorVarying;
 
 uniform vec4 color;
 uniform mat4 modelViewProjectionMatrix;
 uniform float pointSize;
 
 void main()
{
    colorVarying = color;
    gl_Position = modelViewProjectionMatrix * position;
    gl_PointSize = pointSize;
}
 );

const char* kShaderSingleColorFrag = STRINGIFY
(
 varying lowp vec4 colorVarying;
 
 void main()
{
    gl_FragColor = colorVarying;
}
 );
 
const char* kShaderTextureSingleColorVert = STRINGIFY
(
 attribute vec4 position;
 attribute vec2 texCoord;
 
 varying lowp vec4 colorVarying;
 varying lowp vec2 texCoordVarying;
 
 uniform vec4 color;
 uniform mat4 modelViewProjectionMatrix;
 
 void main()
{
    colorVarying = color;
    texCoordVarying = texCoord;
    gl_Position = modelViewProjectionMatrix * position;
}
 );

const char* kShaderTextureSingleColorFrag = STRINGIFY
(
 varying lowp vec4 colorVarying;
 varying lowp vec2 texCoordVarying;
 
 uniform sampler2D texture;
 
 void main()
{
    lowp vec4 texColor = texture2D(texture, texCoordVarying);
    gl_FragColor = colorVarying * texColor;
}
 );

 FL_NAMESPACE_END