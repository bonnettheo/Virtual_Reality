attribute highp vec3 rv_Position;
attribute highp vec3 rv_Color;
uniform   highp mat4 u_ModelViewProjectionMatrix;
varying   highp vec4 outColor;
uniform   highp float u_opacity;
uniform   highp vec3 u_Color;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position,1);
    outColor = vec4(rv_Color * u_Color, u_opacity);
}
