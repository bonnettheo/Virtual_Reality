varying highp vec4 outColor;
varying highp vec2 outTexCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform highp float u_daytime;


void main(void)
{
    highp float x = outTexCoord.s;

    highp float t_light = mod(u_daytime, 24.0)/24.0;
    highp float t_night = mod(u_daytime + 12.0, 24.0)/24.0;
    highp float deltaT = 0.2;
    highp float a = smoothstep(t_light - deltaT, t_light , x);
    highp float a2 = smoothstep(t_light - deltaT + 1.0, t_light + 1.0 , x);
    highp float b = smoothstep(t_night - deltaT, t_night  , x);
    highp float b2 = smoothstep(t_night - deltaT + 1.0, t_night  + 1.0, x);
    highp float c = (t_night  < t_light  ) ? 1.0 : 0.0;
    //float c = pow(sin(u_daytime/10.0), 2.0);
    //float c = smoothstep(0.4, 0.5, x);
    highp vec4 col0 = texture2D(texture0, outTexCoord);
    highp vec4 col1 = texture2D(texture1, outTexCoord);
    //gl_FragColor = mix(col0, col1, c) ;
    gl_FragColor = mix(col0, col1, c + a + a2 - b - b2) ;
}
