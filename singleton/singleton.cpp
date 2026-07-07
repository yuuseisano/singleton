class GameManager {
private:
	GameManager() {}

public:

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;


	static GameManager& Instance() {
				static GameManager instance;
				return instance;
	}

	void StartGame() {
		// Start the game logic here
	}
};

int main() {
	GameManager::Instance().StartGame();
}
