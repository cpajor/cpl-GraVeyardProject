import sys
import struct
import os
 
class FileEntry:
    pass
 
rootdir = "rez"
pakfilename = 'REZ.Y1'
 
pakfile = open(pakfilename,"wb")
 
pakfile.write(struct.Struct("<4s2l").pack(b"CPL2",0,0))
 
offset = 12
fileentries = []
for root, subFolders, files in os.walk(rootdir):
    for file in files:
        entry = FileEntry()
        impfilename = os.path.join(root,file)  
        entry.filename = os.path.relpath(impfilename,rootdir).replace("\\","/")       
        with open(impfilename, "rb") as importfile:
            pakfile.write(importfile.read())
            entry.offset = offset
            entry.length = importfile.tell()
            offset = offset + entry.length
        fileentries.append(entry)
tablesize = 0
 
for entry in fileentries:
    pakfile.write(struct.Struct("<56s").pack(entry.filename.encode("ascii")))
    pakfile.write(struct.Struct("<l").pack(entry.offset))
    pakfile.write(struct.Struct("<l").pack(entry.length))
    tablesize = tablesize + 64
 
pakfile.seek(0)
pakfile.write(struct.Struct("<4s2l").pack(b"CPL2",offset,tablesize))