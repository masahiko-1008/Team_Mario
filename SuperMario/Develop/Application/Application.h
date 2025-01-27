/*/#pragma once



//マクロ定義
#define	D_SUCCESS		(0)		// 成功
#define	D_FAILURE		(-1)	// 失敗

#define D_WIN_MAX_X		(672)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		(864)	// スクリーンサイズ（高さ）
#define D_COLOR_BIT		(32)	// カラービット

class Application
{
public:
	Application();
	~Application();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void WakeUp();

	/// <summary>
	///  実行処理
	/// </summary>
	void Run();

	/// <summary>
	/// 終了時処理
	/// </summary>
	void Shutdown();

private:
	/// <summary>
	/// 描画処理
	/// </summary>
	void Graph() const;

};*/
	
