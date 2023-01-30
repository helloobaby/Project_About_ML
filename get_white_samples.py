# 2023.1.30
# 此脚本文件用来在System32路径下获取白样本，并且放在训练集下面
# 测试集的话，训练前把训练集的一部分移到测试集下面

import subprocess
import os
import pefile
import hashlib
import shutil

def CalcFileSha256(filname):
    ''' calculate file sha256 '''
    with open(filname, "rb") as f:
        sha256obj = hashlib.sha256()
        sha256obj.update(f.read())
        hash_value = sha256obj.hexdigest()
        return hash_value

system_path = 'C:\\Windows\\System32\\'

nfdc_path = 'nfd_win64_portable_0.09\\nfdc.exe'
# 测试exe路径是否正确
#subprocess.run(nfdc_path)

#
count = 0
# 收集的样本数,实际获得的会小于等于count
max_count = 100

fd = os.open('py_log.txt',os.O_RDWR|os.O_CREAT|os.O_TRUNC)

#https://github.com/sourabharvikar3/samplePrograms/blob/d78278a45fcd20d966d2e7da6db2888f3681e93b/python/remoDoubleSignFiles/digisign.py#L54
for root, dirs, files in os.walk(system_path, topdown=False):
    for name in files:#所有文件
        if count < max_count:
            try:
                pefile_handle = pefile.PE(os.path.join(root, name),True)
                #os.write(fd, os.path.join(root, name).encode())
                #os.write(fd, '\n'.encode())
                full_file_path = os.path.join(root, name)
                #print(full_file_path)
                hash256 = CalcFileSha256(full_file_path)

                print('dataset/train/'+hash256)
                shutil.copyfile(full_file_path,'dataset/White/train/'+hash256)
                count = count+1
                print('count = {}'.format(count))
            except:
                pass


os.close(fd)