#include "Scene.h"

Transformation::Transformation() : rot_psi(16), rot_tetta(16), rot_gamma(16), scale(16), trans(16) {}

float* Transformation::getRotPsi()
{
	rot_psi[0] = cos(psi);	rot_psi[1] = 0.0;	rot_psi[2] = -sin(psi);		rot_psi[3] = 0.0;
	rot_psi[4] = 0.0;		rot_psi[5] = 1.0;	rot_psi[6] = 0.0;			rot_psi[7] = 0.0;
	rot_psi[8] = sin(psi);	rot_psi[9] = 0.0;	rot_psi[10] = cos(psi);		rot_psi[11] = 0.0;
	rot_psi[12] = 0.0;		rot_psi[13] = 0.0;	rot_psi[14] = 0.0;			rot_psi[15] = 1.0;

	return rot_psi.data();
}

float* Transformation::getRotTetta()
{
	rot_tetta[0] = 1.0;		rot_tetta[1] = 0.0;			rot_tetta[2] = 0.0;				rot_tetta[3] = 0.0;
	rot_tetta[4] = 0.0;		rot_tetta[5] = cos(tetta);	rot_tetta[6] = -sin(tetta);		rot_tetta[7] = 0.0;
	rot_tetta[8] = 0.0;		rot_tetta[9] = sin(tetta);	rot_tetta[10] = cos(tetta);		rot_tetta[11] = 0.0;
	rot_tetta[12] = 0.0;	rot_tetta[13] = 0.0;		rot_tetta[14] = 0.0;			rot_tetta[15] = 1.0;

	return rot_tetta.data();
}

float* Transformation::getRotGamma()
{
	rot_gamma[0] = cos(gamma);	rot_gamma[1] = -sin(gamma);	rot_gamma[2] = 0.0;			rot_gamma[3] = 0.0;
	rot_gamma[4] = sin(gamma);	rot_gamma[5] = cos(gamma);	rot_gamma[6] = 0.0;			rot_gamma[7] = 0.0;
	rot_gamma[8] = 0.0;			rot_gamma[9] = 0.0;			rot_gamma[10] = 1.0;		rot_gamma[11] = 0.0;
	rot_gamma[12] = 0.0;		rot_gamma[13] = 0.0;		rot_gamma[14] = 0.0;		rot_gamma[15] = 1.0;

	return rot_gamma.data();
}

float* Transformation::getScale()
{
	scale[0] = k;		scale[1] = 0.0;		scale[2] = 0.0;		scale[3] = 0.0;
	scale[4] = 0.0;		scale[5] = k;		scale[6] = 0.0;		scale[7] = 0.0;
	scale[8] = 0.0;		scale[9] = 0.0;		scale[10] = k;		scale[11] = 0.0;
	scale[12] = 0.0;	scale[13] = 0.0;	scale[14] = 0.0;	scale[15] = 1.0;

	return scale.data();
}

float* Transformation::getTrans()
{
	trans[0] = 1.0;		trans[1] = 0.0;		trans[2] = 0.0;		trans[3] = x;
	trans[4] = 0.0;		trans[5] = 1.0;		trans[6] = 0.0;		trans[7] = y;
	trans[8] = 0.0;		trans[9] = 0.0;		trans[10] = 1.0;	trans[11] = z;
	trans[12] = 0.0;	trans[13] = 0.0;	trans[14] = 0.0;	trans[15] = 1.0;

	return trans.data();
}

Camera::Camera(sf::Vector2u resolution)
{
	float n = 0.1;
	float f = 1000.0;
	float fov = 120.0 / 180.0 * 3.14;
	float aspect = resolution.x / resolution.y;

	projection = {
		1.0f / tan(fov / 2.0f) * aspect,	0.0f,	0.0f,	0.0f,
		0.0f,				1.0f / tan(fov / 2.0f), 0.0f,	0.0f,
		0.0f, 0.0f, -(f + n) / (f - n), -(2.0f * f * n) / (f - n),
		0.0f, 0.0f,	-1.0f, 0.0f
	};
}

float* Camera::getProjection()
{
	return projection.data();
}

Mesh::Mesh(const MeshData& data) : data(data)
{
	glGenBuffers(1, &coords_buf);
	glBindBuffer(GL_ARRAY_BUFFER, coords_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.coords.size(), data.coords.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normals_buf);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.normals.size(), data.normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colors_buf);
	glBindBuffer(GL_ARRAY_BUFFER, colors_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.colors.size(), data.colors.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	glGenVertexArrays(1, &arrays);
	glBindVertexArray(arrays);

	glBindBuffer(GL_ARRAY_BUFFER, coords_buf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normals_buf);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, colors_buf);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &indices_buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * data.indices.size(), data.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(arrays);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buf);
	glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Scene::Scene()
{
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction));

	std::string vssourse;
	std::ifstream vsfin("resources/VertexShader.txt");
	std::stringstream vssin;
	vssin << vsfin.rdbuf();
	vssourse = vssin.str();

	std::string fssourse;
	std::ifstream fsfin("resources/FragmentShader.txt");
	std::stringstream fssin;
	fssin << fsfin.rdbuf();
	fssourse = fssin.str();

	unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vss = vssourse.c_str();
	glShaderSource(vertex_shader, 1, &vss, 0);

	const char* fss = fssourse.c_str();
	glShaderSource(fragment_shader, 1, &fss, 0);

	glCompileShader(vertex_shader);
	/*int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}*/

	glCompileShader(fragment_shader);
	/*glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}*/

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	/*glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}*/

	glDetachShader(shader_program, vertex_shader);
	glDeleteShader(vertex_shader);

	glDetachShader(shader_program, fragment_shader);
	glDeleteShader(fragment_shader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Scene::draw(Camera& cam, Mesh& mesh)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader_program);

	unsigned loc_v_rot_psi = glGetUniformLocation(shader_program, "v_rot_psi");
	glUniformMatrix4fv(loc_v_rot_psi, 1, GL_TRUE, cam.view.getRotPsi());
	unsigned loc_v_rot_tetta = glGetUniformLocation(shader_program, "v_rot_tetta");
	glUniformMatrix4fv(loc_v_rot_tetta, 1, GL_TRUE, cam.view.getRotTetta());
	unsigned loc_v_rot_gamma = glGetUniformLocation(shader_program, "v_rot_gamma");
	glUniformMatrix4fv(loc_v_rot_gamma, 1, GL_TRUE, cam.view.getRotGamma());
	unsigned loc_v_scale = glGetUniformLocation(shader_program, "v_scale");
	glUniformMatrix4fv(loc_v_scale, 1, GL_TRUE, cam.view.getScale());
	unsigned loc_v_trans = glGetUniformLocation(shader_program, "v_trans");
	glUniformMatrix4fv(loc_v_trans, 1, GL_TRUE, cam.view.getTrans());

	unsigned loc_m_rot_psi = glGetUniformLocation(shader_program, "m_rot_psi");
	glUniformMatrix4fv(loc_m_rot_psi, 1, GL_TRUE, mesh.model.getRotPsi());
	unsigned loc_m_rot_tetta = glGetUniformLocation(shader_program, "m_rot_tetta");
	glUniformMatrix4fv(loc_m_rot_tetta, 1, GL_TRUE, mesh.model.getRotTetta());
	unsigned loc_m_rot_gamma = glGetUniformLocation(shader_program, "m_rot_gamma");
	glUniformMatrix4fv(loc_m_rot_gamma, 1, GL_TRUE, mesh.model.getRotGamma());
	unsigned loc_m_scale = glGetUniformLocation(shader_program, "m_scale");
	glUniformMatrix4fv(loc_m_scale, 1, GL_TRUE, mesh.model.getScale());
	unsigned loc_m_trans = glGetUniformLocation(shader_program, "m_trans");
	glUniformMatrix4fv(loc_m_trans, 1, GL_TRUE, mesh.model.getTrans());

	unsigned loc_projection = glGetUniformLocation(shader_program, "projection");
	glUniformMatrix4fv(loc_projection, 1, GL_TRUE, cam.getProjection());

	unsigned loc_light_pos = glGetUniformLocation(shader_program, "light_position");
	glUniform3fv(loc_light_pos, 1, light_pos.data());

	mesh.draw();
}