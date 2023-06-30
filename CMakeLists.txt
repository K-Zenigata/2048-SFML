cmake_minimum_required(VERSION 3.0.0)
project(CMake_2048)
set(CMAKE_CXX_STANDARD 17)

# 生成する実行ファイルの名前を指定
set( OUTPUT main )

# SFMLの設定
# SFMLのCMakeモジュールのディレクトリを指定 自身の環境にあわせてください
set(SFML_DIR "path/to/SFML-2.5.1/lib/cmake/SFML/")

set(SFML_STATIC_LIBRARIES TRUE)

# SFMLのコンポーネントを指定
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# ソースファイルのリストを自動的に取得
file(GLOB SOURCES "source/*.cpp")

# ヘッダーファイルのリストを自動的に取得
file(GLOB HEADERS "include/*.hpp")

# 実行可能ファイルのビルド
add_executable( ${OUTPUT} ${SOURCES} ${HEADERS})


# ヘッダーファイルの検索パスを設定
target_include_directories( ${OUTPUT} PRIVATE ${SFML_INCLUDE_DIRS})

# リンクするライブラリを指定
target_link_libraries( ${OUTPUT} PRIVATE sfml-graphics sfml-window sfml-system)

