#pragma once
#include "GameDefine.h"
using namespace std;

class Scene;
class SceneManager
{
public:
	void RegisterScene(const std::string& sceneName, Scene* scene); // ¾À µî·Ï
	void reserveChangeScene(const std::string& sceneName);			// ±³Ã¼ÇÑ ¾À ¼³Á¤


	void Update(float dt);
	void Render(float dt);

private:
	std::map<std::string, Scene*> m_SceneContainer;

	Scene* m_ReservedScene = nullptr;
	Scene* m_CurrentScene = nullptr;

public:
	SceneManager();
	~SceneManager();

};

