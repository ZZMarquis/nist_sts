set curr_path=%~dp0
set build_dir=%curr_path%build

if exist %build_dir% (
	rd /s /q %build_dir%
)
md %build_dir%

cd %build_dir%

rem 测试程序中用到了OPENSSL，根据自己实际情况调整
cmake -G"Visual Studio 15" -DOPENSSL_HOME_PATH="c:/openssl" ..

pause
