// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// 2019_2020
//
attribute highp vec3 rv_Position;
attribute highp vec2 rv_TexCoord;
attribute highp vec3 rv_Normal;

uniform   highp mat4 u_ModelMatrix;
uniform   highp mat4 u_ViewMatrix;
uniform   highp mat4 u_ProjectionMatrix;
uniform   highp float u_opacity;
uniform   highp vec4 u_color;

varying   highp vec4 outColor;
varying   highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;

void main(void)
{
    outPos = vec3(u_ModelMatrix * vec4(rv_Position, 1.0));
    outNormal = vec3(u_ModelMatrix * vec4(rv_Normal, 0.0));
    outColor = vec4(u_color.rgb, u_opacity);
    outTexCoord = rv_TexCoord.st;

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(outPos, 1.0);
}
