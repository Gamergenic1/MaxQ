rem
echo Incrementally updating %1\Plugins\MaxQ\LICENSE
rem
xcopy %1\LICENSE %1\Plugins\MaxQ /f /r /d
rem
echo Incrementally updating %1\Plugins\MaxQ\*.md
rem
xcopy %1\PRINCIPLES.md %1\Plugins\MaxQ /f /r /d
