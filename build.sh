if [ $OSTYPE = "linux-gnu" ]
then
	"./Alpha9/third-party/premake/premake5-linux" gmake;
elif [ $OSTYPE = "darwin" ]
then
	"./Alpha9/third-party/premake/premake5-macos" xcode;
fi

# Pause the script
read -rsp $'Press any key to continue...' -n1 key
