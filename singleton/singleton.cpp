#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <random>
#include <cstdlib>

class SceneManager {
private:
	enum class Scene { Title, Game, GameOver, GameClear, Exit };

	Scene currentScene_;
	std::random_device rd_;
	std::mt19937 rng_;

	// private コンストラクタ（シングルトン）
	SceneManager() : currentScene_(Scene::Title), rng_(rd_()) {}

	// コピー禁止
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	void ClearScreen() {
		std::system("cls");
	}

	void ShowTitle() {
		ClearScreen();
		std::cout << "=== タイトル ===\n\n";
		std::cout << "何かキーを押すとゲームを開始します。\n";
		std::cout << "終了するには Esc を押してください。\n";
	}

	void ShowGame() {
		ClearScreen();
		std::cout << "=== ゲーム中 ===\n\n";
		std::cout << "何かキーを押すとアクションを行います（結果はランダム）。\n";
		std::cout << "Esc でタイトルに戻ります。\n";
	}

	void ShowGameOver() {
		ClearScreen();
		std::cout << "=== ゲームオーバー ===\n\n";
		std::cout << "何かキーを押すとタイトルに戻ります。\n";
	}

	void ShowGameClear() {
		ClearScreen();
		std::cout << "=== クリア ===\n\n";
		std::cout << "何かキーを押すとタイトルに戻ります。\n";
	}

	// タイトル画面の更新（キー待ち）
	void UpdateTitle() {
		ShowTitle();
		while (true) {
			if (_kbhit()) {
				int ch = _getch();
				if (ch == 27) { // Esc
					currentScene_ = Scene::Exit;
				} else {
					currentScene_ = Scene::Game;
				}
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}

	// ゲーム画面の更新（キーで処理 → 結果に応じて遷移）
	void UpdateGame() {
		ShowGame();
		while (true) {
			if (_kbhit()) {
				int ch = _getch();
				if (ch == 27) { // Esc -> タイトルへ戻す
					currentScene_ = Scene::Title;
					break;
				} else {
					// 簡易なゲーム処理のシミュレーション（ランダムでクリア/オーバー）
					std::uniform_int_distribution<int> dist(0, 1);
					int result = dist(rng_);
					if (result == 0) currentScene_ = Scene::GameOver;
					else currentScene_ = Scene::GameClear;
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}

	void UpdateGameOver() {
		ShowGameOver();
		WaitForKeyThen(Scene::Title);
	}

	void UpdateGameClear() {
		ShowGameClear();
		WaitForKeyThen(Scene::Title);
	}

	void WaitForKeyThen(Scene next) {
		while (true) {
			if (_kbhit()) {
				_getch(); // 押されたキーを消費
				currentScene_ = next;
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}

public:
	// シングルトン取得
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}

	// メインループ
	void Run() {
		while (currentScene_ != Scene::Exit) {
			switch (currentScene_) {
			case Scene::Title: UpdateTitle(); break;
			case Scene::Game: UpdateGame(); break;
			case Scene::GameOver: UpdateGameOver(); break;
			case Scene::GameClear: UpdateGameClear(); break;
			default: currentScene_ = Scene::Exit; break;
			}
		}
		ClearScreen();
	}
};

int main() {
	SceneManager::Instance().Run();
	std::cout << "アプリケーションを終了します。\n";
	return 0;
}
