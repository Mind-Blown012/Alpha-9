if [[ "$OSTYPE" == "linux-gnu" ]]; then
        deps/premake/premake5-linux gmake
elif [[ "$OSTYPE" == "darwin"* ]]; then
        deps/premake/premake5-macos xcode
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
        deps/premake/premake5.exe vs2017
fi
