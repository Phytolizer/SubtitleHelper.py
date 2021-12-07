cmake_minimum_required(VERSION 3.12...3.22)

project(
	"SubtitleHelper"
	LANGUAGES "CXX"
	VERSION "0.1.0"
	DESCRIPTION "Subtitle writing tool"
	HOMEPAGE_URL "https://github.com/Phytolizer/SubtitleHelper.py"
)

find_package("SDL2" REQUIRED COMPONENTS "ttf")

add_executable("SubtitleHelper" "SubtitleHelper.cpp")
target_link_libraries("SubtitleHelper" PRIVATE "SDL2" "SDL2_ttf")
target_compile_features("SubtitleHelper" PUBLIC "cxx_std_20")
