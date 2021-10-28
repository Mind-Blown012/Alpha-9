#include <Alpha9>

using namespace Alpha9;

class TestGame : public Game
{
public:
	void Start() override
	{
		vertArray.reset(VertexArray::Create());

		float vertices[3 * 3] = {
			0.0f,  1.0f,  0.0f,
			1.0f, -1.0f,  0.0f,
		   -1.0f, -1.0f,  0.0f
		};

		vertBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertArray->AddVertexBuffer(vertBuffer);
		vertArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 400
			layout (location = 0) in vec3 aPos;
			
			out vec4 vertexColor;

			uniform mat4 u_MVPmatrix;
			
			in vec3 vp;
			void main()
			{
				gl_Position = u_MVPmatrix * vec4(aPos, 1.0);
				vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 400
			in vec4 vertexColor;
			
			out vec4 frag_color;
			void main()
			{
				frag_color = vertexColor;
			}
		)";

		m_shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	void Update() override
	{
		float speed = 0.5f;

		if (Input::GetKey(KeyCode::W))
			trianglePos.Translate(glm::vec3(0.0f, 1.0f, 0.0f) * speed * Time::GetDeltaTime());
		if (Input::GetKey(KeyCode::A))
			trianglePos.Translate(glm::vec3(-1.0f, 0.0f, 0.0f) * speed * Time::GetDeltaTime());
		if (Input::GetKey(KeyCode::S))
			trianglePos.Translate(glm::vec3(0.0f, -1.0f, 0.0f) * speed * Time::GetDeltaTime());
		if (Input::GetKey(KeyCode::D))
			trianglePos.Translate(glm::vec3(1.0f, 0.0f, 0.0f) * speed * Time::GetDeltaTime());

		if (Input::GetKeyDown(KeyCode::T))
			A9_INFO(Time::getTime());
	}

	void Render() override
	{
		//trianglePos.SetRotation(0.0f, 0.0f, sin(Time::getTime()) * 45);
		//A9_TRACE(sin(Time::getTime()) * 10.0f);
		Renderer::Submit(m_shader, vertArray, trianglePos);
	}
private:
	std::shared_ptr<VertexArray> vertArray;
	std::shared_ptr<VertexBuffer> vertBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<Shader> m_shader;
	Transform trianglePos = Transform();
};

Game* CreateGame()
{
	return (Game*)(new TestGame());
}