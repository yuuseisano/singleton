#include <iostream>

class GameManager {
private:
	/// <summary>
	/// オブジェクトを外部から生成するのを防ぐためのprivateコンストラクタ
	/// </summary>
	GameManager() {}

public:
	/// <summary>
	/// 別のオブジェクトを禁止するためのコピーコンストラクタ
	/// </summary>
	/// <param name=""></param>
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	/// <summary>
	/// スレッドセーフな、Gamemanagerの唯一のオブジェクトを返すことができる
	/// </summary>
	/// <returns></returns>
	static GameManager& Instance() {
		static GameManager instance;	// C++11以降のスレッドセーフなローカルstatic
		return instance;
	}

	void StartGame() {
		// Start the game logic here
		std::cout << "Game started!" << std::endl;
	}
};

int main() {
	GameManager::Instance().StartGame();

	//GameManager::Instance() = GameManager::Instance();

	//GameManager obj1;
}