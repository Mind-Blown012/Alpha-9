@ECHO OFF

IF "%1%"=="help" (
	call "docs/%2%/html/index.html"
) ELSE (
	call "Alpha-9/third-party/premake/premake5-windows" vs2017
	PAUSE
)