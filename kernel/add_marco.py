import os

script_dir = os.path.dirname(os.path.abspath(__file__))

os.chdir(script_dir)

all_files=os.walk("./")

for root, dirs, files in all_files:
    for file in files:
        if(file.endswith('.h')):
            content=open(root+file,encoding='UTF-8',mode="rt")
            buf=content.read()
            upper_str=file.replace('.','_').upper()
            if(buf.startswith("#ifndef {}".format(upper_str))):
                continue
            head_str="#ifndef {0}\n#define {0}\n\n".format(upper_str)
            end_str="\n#endif"
            buf=head_str+buf+end_str
            content.close()
			
            content=open(root+file,encoding='UTF-8',mode="wt")
            content.write(buf)
            content.close()

