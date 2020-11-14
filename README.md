# AddTagsSoralet
SORACOM Airから送られるJSONデータにタグ情報を追加します。
FunkやHarvestにタグ情報をつけて送るのに便利です。

# 使い方
WASMをダウンロードします。
https://github.com/1stship/AddTagsSoralet/releases/download/0.0.1/addtags.wasm

以下のページの手順に従って、Soraletを作成し、WASMをアップロードします。
https://dev.soracom.io/jp/orbit/deployment/

以下のページの手順に従って、SIMグループを作成し、SORACOM Orbitを設定します。
https://dev.soracom.io/jp/orbit/running/

CODE SRNにはアップロードしたSoralet
CONTENT TYPEにはapplication/json
DIRECTIONはuplinkにチェック
メタデータはON

として保存します。

SORACOM Air for Cellular 設定にて、メタデータサービスをONにします。
必要に応じてバイナリパーサーもONにします。

対象となるSIMのタグに、
tagsという名前のタグを追加します。
値は、データに付与したいタグ名をカンマ区切りで繋いだ文字列をとします。

例えばLocation、Deviceというタグをデータに付与したい場合は以下のようにタグを設定します。

| タグ名 | タグ値 |
| --- | --- |
| tags | Location,Device |
| Location | Tokyo |
| Device | MyButton |
