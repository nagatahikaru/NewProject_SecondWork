#pragma once
#include "sound/SoundSource.h"

//ファイルパスを追加する際は、
//cppのnamespaceと下記のenumを追加してください。
enum Sound{
	enSound_TitleBGM,   //タイトル　　　　　　0
	enSound_InGameBGM,  //ゲーム　　　　　　　1
	enSound_OverBGM,    //ゲームオーバー　　　2　
	enSound_ClearBGM,   //ゲームクリア　　　　3
	enSound_BulletSE,   //プレイヤ―の攻撃音　4　　
	enSound_DamageSE,   //敵の攻撃音　　　　　5
	enSound_ResultBGM,  //リザルト　　　　　　6
	enSound_ReloadSE,	//リロード音　　　　　7
	enSound_LoadBGM,    //ロード　　　　　　　8
	enSound_Num //このステータスは、サウンドの総数を表しているため、この下には追加しないでください。
};

class SoundManager :public IGameObject
{
public:
	SoundManager();
	~SoundManager() {};
	/// <summary>
	/// 指定したサウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	/// <param name="number">再生するサウンドを指定します。</param>
	/// <param name="isLoop">サウンドをループ再生するかどうかを指定します。デフォルトは true です。</param>
	/// <param name="volume">再生音量を指定します。デフォルトは 1.0f です。</param>
	/// <returns>再生中のサウンドソースへのポインタ。</returns>
	SoundSource* PlayingSound(Sound number, bool isLoop = true, float volume = 1.0f);
};


