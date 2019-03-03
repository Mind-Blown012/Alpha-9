if [[ "$OSTYPE" == "linux-gnu" ]]; then
        deps/premake/premake5-linux gmake
elif [[ "$OSTYPE" == "darwin"* ]]; then
        deps/premake/premake5-linux xcode
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
        deps/premake/premake5-linux vs2017
fi
