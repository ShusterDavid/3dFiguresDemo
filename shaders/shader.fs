#version 330 core

in vec3 Normal;

out vec4 FragColor;

void main()
{
  vec3 normal = normalize(Normal);
  vec3 dir = vec3(-2.0, -3.0, 1.0);
  vec3 lightDir = normalize(dir);

  // ambient
  vec3 ambient = vec3(0.2);

  // diffuse
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = vec3(0.5) * diff;

  FragColor = vec4(ambient + diffuse, 1.0);
}