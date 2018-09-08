#version 150

uniform float time;
uniform vec2 resolution;
uniform sampler2DRect tex;

out vec4 outputColor;

void main() {

  vec4 t = texture(tex, vec2(gl_FragCoord.x - 25, (resolution.y - gl_FragCoord.y) - 25));
  float gray = dot(t.rgb, vec3(0.299, 0.587, 0.114));
  outputColor = vec4(vec3(gray), t.a * 0.2);
}
