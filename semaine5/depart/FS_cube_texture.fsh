varying highp vec4 outColor;
varying highp vec2 outTexCoord;
uniform sampler2D texture0;

void main(void)
{
    vec4 col0 = outColor;
    vec4 col1 = texture2D(texture0, outTexCoord);
    gl_FragColor = col0*col1;
    gl_FragColor.a = col0.a;
}
