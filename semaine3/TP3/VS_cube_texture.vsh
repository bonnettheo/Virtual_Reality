attribute highp vec3 rv_Position;
attribute highp vec3 rv_Color;
attribute highp vec3 rv_TexCoord;
uniform   highp mat4 u_ModelViewProjectionMatrix;
uniform   highp float u_opacity;
uniform   highp vec4 u_color;
varying   highp vec4 outColor;
varying   highp vec2 outTexCoord;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position,1);
    outTexCoord = vec2(rv_TexCoord[0], rv_TexCoord[1]);
    outColor = vec4(rv_Color * u_color.rgb, u_opacity);
}
