import os
from datetime import date
import re


mypath = os.path.dirname(os.path.abspath(__file__))
testpath = os.path.dirname(os.path.abspath(__file__))

files = [f for f in os.listdir(mypath) if os.path.isfile(os.path.join(mypath, f))]
testfiles = [f for f in os.listdir(testpath) if os.path.isfile(os.path.join(testpath, f))]

files = files + testfiles

exception = []

for file in files:
    if file[-1] != "c" and file[-1] != "h":
        exception.append(file)

for ex in exception:
    files.remove(ex)


for file in files:
    path = mypath + "/" + file
    if file[0:4] == "test":
        path = testpath + "/" + file
    myfile = open(path, 'r')
    if file[-1] == "c":
        describtion = file.replace('.cc','') + " implementation"
    elif file[-1] == "h":
        describtion = file.replace('.h','') + " interface"
    fline = "/******************************************************************************!\n* @file     "+file+"\n* @author   Léo Brückl, Linus Crugnola\n* @version  1.0"+"\n*******************************************************************************/"
    content = myfile.read()
    if content[0:10] != "/*********":
        new_content = fline + "\n \n" + content
        myfile.close()
        myfile = open(path, "w")
        myfile.write(new_content)
        myfile.close()
    else:
        myfile.close()
        with open(path, "w") as myfile:
            myregex = re.compile("\/\*{10,}[\s\S]*\*{10,}\/")
            myfile.write(myregex.sub(fline, content))

print("added headers for: ", end="")
for file in files:
    print(file, end="")
    print(", ", end="")