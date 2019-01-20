import sys
import glob

# Ghetto but super simple parser for creating adapters quickly

targetClass = sys.argv[1]
fileRoot = sys.argv[2]

# targetClass = "IClientFriendsMap"
# fileRoot = "ISteamFriends"

for file in glob.iglob("../external/SteamStructs/" + fileRoot + "*.h"):
    adaptName = ""
    functionNames = []

    with open(file, "r") as f:
        lines = f.readlines()

        adaptName = lines[0].split(" ")[1][:-1]

        for l in lines[1:]:
            if "virtual unknown_ret" in l:
                functionNames.append(
                    l.split("    ")[1].split(" ")[2].split("(")[0])

    print("AdaptDeclare(%s);" % adaptName)
    print("AdaptDefine(%s) = {" % adaptName)
    for f in functionNames:
        print("    AdaptPassThrough(%s::%s)," % (targetClass, f))
    print("};")
