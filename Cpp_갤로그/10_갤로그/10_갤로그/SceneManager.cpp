#include "SceneManager.h"
#include "Scene.h"
void SceneManager::RegisterScene(const std::string& sceneName, Scene* scene)
{
	if (scene == nullptr || sceneName.compare("") == 0)
		return;

	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, Scene*>(sceneName, scene));
}

void SceneManager::reserveChangeScene(const std::string& sceneName)
{
	auto itor = m_SceneContainer.find(sceneName);

	if (itor != m_SceneContainer.end())
	{
		m_ReservedScene = itor->second;
	}
	else
	{
		m_ReservedScene = nullptr;
	}
}

void SceneManager::Update(float dt)
{
	if (m_ReservedScene != nullptr)
	{
		m_ReservedScene->Init(*this);
		m_CurrentScene = m_ReservedScene;

		m_ReservedScene = nullptr;
	}

	if (m_CurrentScene != nullptr)
		m_CurrentScene->Update(dt);
}

void SceneManager::Render(float dt)
{
	if (m_CurrentScene != nullptr)
		m_CurrentScene->Render(dt);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (auto it = m_SceneContainer.begin(); it != m_SceneContainer.end(); ++it)
	{
		it->second->Destroy();
		delete it->second;
	}
}
