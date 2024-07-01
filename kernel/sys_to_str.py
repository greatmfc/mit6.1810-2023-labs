import os
import sys

fd = open("./syscall.h", "r")
file = fd.readlines()
res = "static const char *syscall_str[] = {\n"
file.pop(0)
for line in file:
    sys_name = line.split(" ")[1]
    # line = line.strip()
    name = sys_name.split("_")[1]
    res += '[{}] "{}", '.format(sys_name, name)
res += "};"
fd1 = open("./res.txt", "+w")
for r in res:
    fd1.write(r)

fd.close()
fd1.close()
