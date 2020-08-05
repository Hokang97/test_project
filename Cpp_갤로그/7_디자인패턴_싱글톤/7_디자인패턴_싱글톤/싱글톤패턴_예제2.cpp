#include <iostream>	
#include "CharacterInfo.h"
#include "Inventory.h"
#pragma warning(disable:4996)

using namespace std;

class SystemManager
{
private:
	static SystemManager* _instance;

	CharacterInfo* m_pChar = nullptr;
	Inventory* m_pInven = nullptr;

public:
	void Destroy()
	{
		if (m_pChar != nullptr) delete m_pChar;
		if (m_pInven != nullptr) delete m_pInven;
		if (_instance != nullptr) delete _instance;
	}

	static SystemManager* getInstance()
	{
		if (_instance == nullptr)
			_instance = new SystemManager;

		return _instance;
	}

	CharacterInfo* GetCharacterInfo()
	{
		if (m_pChar == nullptr)
			m_pChar = new CharacterInfo;

		return m_pChar;
	}

	Inventory* GetInventory()
	{
		if (m_pInven == nullptr)
			m_pInven = new Inventory;

		return m_pInven;
	}

	void Print()
	{
		cout << "name? " << m_pChar->name << endl;
		cout << "gold? " << m_pInven->Gold << endl;
	}
};

SystemManager* SystemManager::_instance = nullptr;

int main()
{
	strcpy(SystemManager::getInstance()->GetCharacterInfo()->name, "°­¾ÆÁö");
	SystemManager::getInstance()->GetInventory()->Gold = 1000;

	SystemManager::getInstance()->Print();

}