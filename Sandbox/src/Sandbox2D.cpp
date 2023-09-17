#include "gkpch.h"
#include "Sandbox2D.h"
#include <Gonk.h>

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDDDDWWWWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDWDDDWDDDDDWWWWW"
"WWWWWDDDDWDWDWDDDDDWWWWW"
"WWWWWDDDDDWDWDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWWWDDDDDDDDWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;
const uint32_t s_MapWidth = 24;
const uint32_t s_MapHeight = strlen(s_MapTiles) / s_MapWidth;

void Sandbox2DLayer::OnAttach()
{
	GK_PROFILE_FUNCTION();

	// framebuffer
	Gonk::FramebufferSpec fbSpec;
	fbSpec.Width = 1280.0f;
	fbSpec.Height = 720.0f;
	m_Framebuffer = Gonk::Framebuffer::Create(fbSpec);

	// textures
	m_CheckerboardTexture = Gonk::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LogoTexture = Gonk::Texture2D::Create("assets/textures/ChernoLogo.png");
	m_Spritesheet = Gonk::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	// subtextures
	m_Barrel = Gonk::SubTexture2D::CreateFromCoords(m_Spritesheet, { 9, 2 }, { 128, 128 });
	m_Tree = Gonk::SubTexture2D::CreateFromCoords(m_Spritesheet, { 0, 1 }, { 128, 128 }, { 1, 2 });

	s_TextureMap['D'] = Gonk::SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = Gonk::SubTexture2D::CreateFromCoords(m_Spritesheet, {11, 11}, {128, 128});

	m_CameraController.SetZoomLevel(5.0f);

	Gonk::Shader::Create("assets/shaders/FlatColour.glsl");

	//Gonk::Application::Get().GetWindow().SetVSync(false);

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 2.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

}

void Sandbox2DLayer::OnDetach()
{
	GK_PROFILE_FUNCTION();

}

glm::vec3 redPos { 0.0f, 0.0f, -0.0f } ;
glm::vec3 greenPos { -1.0f, -1.0f, -0.2f };
float rotation = 0.0f;
float autoRotate = 0.0f;
float timestep = 0.0f;


void Sandbox2DLayer::OnUpdate(Gonk::Timestep ts)
{
	GK_PROFILE_FUNCTION();

	timestep = (float)ts.GetMilliSeconds();
	// update
	m_CameraController.OnUpdate(ts);
	m_ParticleSystem.OnUpdate(ts);
	// Render
	Gonk::Renderer2D::ResetStats();
	{
		GK_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		Gonk::RendererCommand::SetColour(glm::vec4{0.2f});
		Gonk::RendererCommand::Clear();
	}

	Gonk::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	for (int y = 0; y < s_MapHeight; y++)
	{
		for (int x = 0; x < s_MapWidth; x++)
		{
			char c = s_MapTiles[x + y * s_MapWidth];
			Gonk::Ref<Gonk::SubTexture2D> texture;
			if (s_TextureMap.find(c) != s_TextureMap.end())
				texture = s_TextureMap[c];
			else
				texture = m_Barrel;
			Gonk::Renderer2D::DrawQuad({ x, y, 0.0f }, { 1.0f, 1.0f }, texture);
		}
	}

	Gonk::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.9f }, { 1.0f, 1.0f }, m_Barrel);
	Gonk::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.9f }, { 1.0f, 2.0f }, m_Tree);

	Gonk::Renderer2D::EndScene();
	
#if 0
	autoRotate += rotation;
	static float width = 20, height = 20;
	Gonk::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Gonk::Renderer2D::DrawQuad(redPos, {1.0f, 1.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
	Gonk::Renderer2D::DrawQuad({ -0.25f,-0.25f, -0.1f }, { width / 2.0f + 2, height / 2.0f + 2}, m_CheckerboardTexture, 10.0f);
	Gonk::Renderer2D::DrawRotatedQuad({ 2.0f, 2.0f, 0.0f }, { 1.0f, 1.0f }, autoRotate, {0.0f, 1.0f, 1.0f, 1.0f});
	Gonk::Renderer2D::DrawQuad({1.0f, 1.0f, 0.1f}, {1.0f, 1.0f}, m_LogoTexture, 3.0f, { 0.5f, 1.0f, 0.5f, 1.0f });


	Gonk::Renderer2D::EndScene();

	Gonk::Renderer2D::BeginScene(m_CameraController.GetCamera());

	static auto testTexture = Gonk::Texture2D::Create("assets/textures/ez.png");
	for (float y = 0; y < height; y++)
	{
		for (float x = 0; x < width; x++)
		{
			glm::vec4 colour{x / width, 0.2f, y / height, 0.75f};
			Gonk::Renderer2D::DrawRotatedQuad({ (x - width / 2) * 0.5f, (y - height/2) * 0.5f, 0.0f }, { 0.45f, 0.45f }, autoRotate + (x + y) * 50.0f, testTexture, 1.0f, colour);
		}
	}

	Gonk::Renderer2D::EndScene();
#endif

	if (Gonk::Input::IsMouseButtonPressed(GK_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Gonk::Input::GetMousePosition();
		auto width = Gonk::Application::Get().GetWindow().GetWidth();
		auto height = Gonk::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}


	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	m_Framebuffer->UnBind();
}

void Sandbox2DLayer::OnEvent(Gonk::Event& e)
{
	m_CameraController.OnEvent(e);

	Gonk::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Gonk::KeyPressedEvent>([](Gonk::KeyPressedEvent& e) {
		if (e.GetKeyCode() == GK_KEY_ESCAPE)
			Gonk::Application::Get().Shutdown();
		return false;
	});
}

void Sandbox2DLayer::OnImGuiRender()
{
	GK_PROFILE_FUNCTION();


	static bool p_open = true;
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				Gonk::Application::Get().Close();

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");

	auto stats = Gonk::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	FrameTime: %0.2fms (%f fps)", timestep, 1000.0f / timestep);
	ImGui::Text("	Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("	Quads: %d", stats.QuadCount);
	ImGui::Text("	Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices: %d", stats.GetTotalIndexCount());

	ImGui::NewLine();
	ImGui::InputFloat3("Camera Info", (float*)&m_CameraController);
	ImGui::NewLine();


	ImGui::ColorEdit4("Col", &m_Col[0]);
	ImGui::DragFloat3("Red Pos", &redPos[0], 0.05f, -1.0f, 1.0f);
	ImGui::DragFloat3("Green Pos", &greenPos[0], 0.05f, -1.0f, 1.0f);
	ImGui::DragFloat("Rotation", &rotation, 0.5f, -360.0f, 360.0f);

	ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), { 1280, 720}, { 0, 1 }, {1, 0});

	ImGui::End();

	ImGui::End();

}
