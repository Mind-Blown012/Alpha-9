@ECHO OFF

IF "%1%"=="help" (
	call "docs/%2%/html/index.html"
) ELSE (
	call "Alpha9/third-party/premake/premake5-windows" vs2019
	PAUSE
)