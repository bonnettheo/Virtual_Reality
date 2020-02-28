varying highp vec4 outColor;

void main(void)
{
    vec4 c;
    c.x = outColor.x * (1.0 - gl_FragCoord.z / 2.0);
    c.y = outColor.y * (1.0 - gl_FragCoord.z / 2.0);
    c.z = outColor.z * (1.0 - gl_FragCoord.z / 2.0);
    c.w = outColor.w;
    gl_FragColor = c;
}
