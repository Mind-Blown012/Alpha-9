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

			uniform mat4 u_viewProjectionMatrix;
			
			in vec3 vp;
			void main()
			{
				gl_Position = u_viewProjectionMatrix * vec4(aPos, 1.0);
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
		if (Input::GetKeyDown(KeyCode::W))
			A9_INFO("W was pressed!");
		if (Input::GetKeyDown(KeyCode::A))
			A9_INFO("A was pressed!");
		if (Input::GetKeyDown(KeyCode::S))
			A9_INFO("S was pressed!");
		if (Input::GetKeyDown(KeyCode::D))
			A9_INFO("D was pressed!");

		if (Input::GetKeyDown(KeyCode::T))
			A9_INFO(Time::getTime());
	}

	void Render() override
	{
		Renderer::Submit(m_shader, vertArray);
	}
private:
	std::shared_ptr<VertexArray> vertArray;
	std::shared_ptr<VertexBuffer> vertBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<Shader> m_shader;
};

Game* CreateGame()
{
	return (Game*)(new TestGame());
}