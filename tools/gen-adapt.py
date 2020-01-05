import sys
import glob

# Ghetto but super simple parser for creating adapters quickly

targetClass = sys.argv[1]
fileRoot = sys.argv[2]
everything = sys.argv[3]

# targetClass = "IClientFriendsMap"
# fileRoot = "ISteamFriends"

newClass = targetClass[1:]
name = targetClass[len("IClient"):]

if everything == "t":
    print(
"""
#include <precompiled.hh>

#include "helpers.hh"
#include "steamplatform.hh"

using namespace Steam;

namespace Reference {
#include "SteamStructs/IClient%s.h"
}
""" % name,
f"""
template<bool isServer>
class {newClass} : public Reference::{targetClass} {{
public:
    UserHandle userHandle;
    {newClass}(UserHandle h) : userHandle(h) {{}}

}};

AdaptExposeClientServer({newClass}, "Steam{name}");

using {targetClass} = {newClass}<false>;

"""
)

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
    print("AdaptDefine(%s, %s, \"%s\") = {" % (adaptName, targetClass, adaptName[1:]))
    for f in functionNames:
        print("    AdaptPassThrough(%s::%s)," % (targetClass, f))
    print("};")
