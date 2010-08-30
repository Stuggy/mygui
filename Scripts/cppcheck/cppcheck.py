# run from root sources directory: python Scripts/cppcheck/cppcheck.py
import os

ignoredEndings = ["is never used", "It is safe to deallocate a NULL pointer", "Throwing exception in destructor"]
ignoredContent = ["MyGUI_UString"]

def isIgnoredWarning(warning):
	for ignore in ignoredEndings:
		if warning.endswith(ignore):
			return True
	for ignore in ignoredContent:
		if warning.find(ignore) != -1:
			return True
	return False

def parseOutput():
	file = open("temp.cppcheck", 'r')
	
	line = file.readline()
	while line != "":
		line = line[0:len(line)-1]
		if (not isIgnoredWarning(line)):
			print line
		line = file.readline()
	file.close ()

def checkFolderSources(folder) :
	os.system("cppcheck --enable=all -I Scripts/cppcheck " + folder + " 2>temp.cppcheck")
	parseOutput()


#checkFolderSources('MyGUIEngine')
os.system("cppcheck --enable=all -I Scripts/cppcheck -I MyGUIEngine/include MyGUIEngine/src 2>temp.cppcheck")
parseOutput()

checkFolderSources('Demos')
checkFolderSources('Tools')
checkFolderSources('UnitTests')
checkFolderSources('Common')
#checkFolderSources('Platforms/OpenGL')
# temporary disabled due to cppcheck bug
#os.system("cppcheck --enable=all -I Scripts/cppcheck -I Platforms/OpenGL/OpenGLPlatform/include Platforms/OpenGL/OpenGLPlatform/src 2>temp.cppcheck")
parseOutput()
#checkFolderSources('Platforms/Ogre')
os.system("cppcheck --enable=all -I Scripts/cppcheck -I Platforms/Ogre/OgrePlatform/include Platforms/Ogre/OgrePlatform/src 2>temp.cppcheck")
parseOutput()
#checkFolderSources('Platforms/DirectX')
os.system("cppcheck --enable=all -I Scripts/cppcheck -I Platforms/DirectX/DirectXPlatform/include Platforms/DirectX/DirectXPlatform/src 2>temp.cppcheck")
parseOutput()
checkFolderSources('Platforms/OpenGL')
checkFolderSources('Platforms/Ogre')
checkFolderSources('Platforms/DirectX')
checkFolderSources('Plugins')
checkFolderSources('Wrapper')

